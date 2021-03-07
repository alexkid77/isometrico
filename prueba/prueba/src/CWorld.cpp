#include <CWorld.h>
#include <algorithm>
#include <cstdio>

CWorld::CWorld(CEngine *engine)
{

    this->tilemap=this->LoadTmx("mapa3.tmx");
    this->tileGridH= engine->tileGridH;
    this->tileGridW= engine->tileGridW;
    this->orig=engine->orig;
    this->engine=engine;
    this->vSprites=vector<CSprite *>(2048);

    this->objeto=new CSprite(this->engine->tileGridW,this->engine->tileGridH,this->engine->tileSize,Vec3D(32,32,80));
    this->objeto->Pos.x=60;
    this->objeto->Pos.y=60;
    this->objeto->Pos.z=0;
    this->objeto->Size.x=32;
    this->objeto->Size.y=32;
    this->objeto->Size.z=80;
    this->objeto->ClearDepth();

    this->InitSprites();



}
CTileMap * CWorld::LoadTmx(string file)
{
    CTileMap *tilemap=new CTileMap(file);
    return tilemap;

}
CWorld::~CWorld()
{
    //dtor
}
void CWorld::Update()
{

    this->ProcesaCollisiones();
    this->ProcesaDepthSprites();


}
void CWorld::ProcesaCollisiones()
{

    CLayer *capa=this->tilemap->Layers[0];
    /*Mirar colisiones entre objeto dinamicos*/
    for(uint32_t i=0; i<this->vDinamicos.size(); i++)
    {
        CSprite *obj1=vDinamicos[i];
        for(uint32_t j=0; j<this->vDinamicos.size(); j++)
        {
            CSprite *obj2=vDinamicos[j];
            if(obj1!=obj2 &&  obj1->hasCollision(obj2))
                obj1->onCollision(obj2);
        }
    }

    /*Mirar colisiones con los tiles*/
    for(unsigned int i=0; i<this->vDinamicos.size(); i++)
    {

        CSprite *s=vDinamicos[i];

        /*que no se salga del mapa*/
        if( s->Pos.x<0)
            s->Pos.x=0;
        if( s->Pos.y<0)
            s->Pos.y=0;

        if( s->Pos.x>((capa->width*32)-32))
            s->Pos.x=capa->width*32-32;
        if( s->Pos.y>((capa->height*32)-32))
            s->Pos.y=capa->height*32-32;

        s->vColisiones.clear();
        vector<Vec2D> tilesOcupados=s->getTilesOcupados();


        for(uint16_t i=0; i<tilesOcupados.size() ; i++)
        {
            Vec2D tile=tilesOcupados[i];
            CTile *t=capa->GetTile(tile.x,tile.y);
            if(t->indiceTile==2 && ((t->Pos.z+1)>= s->Pos.z ))
            {
                s->Pos=s->PosAnt;
                s->vColisiones.push_back(t);
                s->onCollision(t);
                break;
            }
        }
    }
}

void CWorld::Render()
{

    Vec2D val2;

    Vec2D playerProj=this->engine->player->getPosProj();

    this->engine->player->PosProj=playerProj;
    val2.x=this->engine->player->Pos.x/32;
    val2.y=this->engine->player->Pos.y/32;


    /*Se procesa los sprites para establecer el orden de renderizado */


    clear_to_color(this->engine->buffer, makecol(0, 0, 0));


    int offsetx=this->engine->player->PosProj.x;
    int offsety=this->engine->player->PosProj.y;
    int tamVisible=this->vVisible.size();
    for(uint16_t  i=0; i<tamVisible; i++)
    {
        CSprite * e=(this->vVisible[i]);

        if(e->Tipo==TILE)
        {
            CTile *t=static_cast<CTile*>(this->vVisible[i]);
            masked_blit(this->engine->tiles[t->indiceTile], this->engine->buffer, 0, 0, t->PosProj.x+this->orig.x-offsetx, t->PosProj.y+this->orig.y-offsety, this->engine->tileW,this->engine->tileH);
            char tempStr2 [100];
            //snprintf ( tempStr2, 100, "(%d,%d)", t->j,  t->i );
            sprintf ( tempStr2,  "(%d)", e->Depth );
            //    textout_centre_ex(this->engine->buffer, font, tempStr2, e->PosProj.x+this->orig.x-offsetx+32, e->PosProj.y+this->orig.y-offsety+32, makecol(255,255,255), -1);

        }
        else
        {
            e->PosProj=e->getPosProj();
            masked_blit(this->engine->tiles[0], this->engine->buffer, 0, 0,  e->PosProj.x+this->orig.x-offsetx,  e->PosProj.y+this->orig.y-offsety, this->engine->tileW,this->engine->tileH);
            char tempStr2 [100];
            //snprintf ( tempStr2, 100, "(%d,%d)", t->j,  t->i );
            sprintf ( tempStr2,  "(%d)", e->Depth );
            textout_centre_ex(this->engine->buffer, font, tempStr2, e->PosProj.x+this->orig.x-offsetx+32, e->PosProj.y+this->orig.y-offsety+32, makecol(255,0,0), -1);

        }

    }



    char tempStr [100];


    CLayer *capa=this->tilemap->Layers[0];
    CTile *t=capa->tiles[val2.x+val2.y*capa->width];


    snprintf ( tempStr, 100, "player x:%d px:%d player y:%d py:%d tile:%d,%d val:%d tam%d", this->engine->player->Pos.x,this->engine->player->PosProj.x,  this->engine->player->Pos.y,this->engine->player->PosProj.y,val2.x,val2.y,t->indiceTile,this->vVisible.size() );




    textout_centre_ex(this->engine->buffer, font, tempStr, SCREEN_W/2, 20, makecol(255,255,255), -1);
    char fpsStr [100];
    snprintf ( fpsStr, 100, "fps:%d", this->engine->fps );
    textout_ex(this->engine->buffer, font, fpsStr, 0, 20, makecol(255,255,255), -1);


    acquire_screen();
    blit(this->engine->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);


    release_screen();
}

void CWorld::VisitNode(CSprite *ent,int *sortDepth)
{
    if(!ent->visitado)
    {
        ent->visitado=true;
        int hijos=ent->entidadesDebajo.size();
        for(int i=0; i<hijos; i++)
        {
            if(ent->entidadesDebajo[i]==0)
                break;
            else
            {
                VisitNode(ent->entidadesDebajo[i],sortDepth);
                ent->entidadesDebajo[i]=0;
            }
        }
        (*sortDepth)++;
        ent->Depth=(*sortDepth);
    }
}

void CWorld::InitSprites()
{
    this->vSprites.clear();


    CLayer *capa=this->tilemap->Layers[0];
    for(int j=0; j<capa->height; j++)
        for(int i=0; i<capa->width; i++)
        {
            //la i es Y
            //la j es X
            CTile *t= capa->GetTile(i,j);
            this->vSprites.push_back(t);
        }




    this->vDinamicos.push_back(this->engine->player);
    this->vDinamicos.push_back(this->objeto);
    this->vSprites.push_back(this->objeto);
    this->vSprites.push_back(this->engine->player);

}

void CWorld::ProcesaDepthSprites()
{



    this->vVisible.clear();

    CLayer *capa=this->tilemap->Layers[0];
    for(unsigned int i=0; i<this->vDinamicos.size(); i++)
        vVisible.push_back(this->vDinamicos[i]);




    /*solo se dibuja lo que se ve en la pantalla*/
    ViewPort viewport=GetViewPort(capa->width,capa->height);
    for(int y= viewport.p1.y; y<viewport.p2.y ; y++)
        for(int x= viewport.p1.x; x<viewport.p2.x; x++)
        {
            CSprite *s=  capa->tiles[x+y*capa->width];
            int offsety=(this->engine->player->PosProj.y);
            int offsetx=(this->engine->player->PosProj.x);
            if((s->PosProj.x+this->orig.x-offsetx)<=SCREEN_W
                    && (s->PosProj.y+this->orig.y-offsety)<=SCREEN_H
                    && (s->PosProj.x+this->orig.x-offsetx+64)>=0
                    && (s->PosProj.y+this->orig.y-offsety+80)>=0
              )

                this->vVisible.push_back(s);

        }

    /*se limpia la profundidad*/
    for(uint16_t  i=0; i<vVisible.size(); i++)
        vVisible[i]->ClearDepth();

    /*ordena topologicamente los sprites*/
    this->OrdenaTopologicamente();

}

void CWorld::OrdenaTopologicamente()
{
    int tam=this->vVisible.size();
    // this->PreSortByXY(vVisible);

    for(uint32_t i=0; i<this->vDinamicos.size(); i++)
    {
        CSprite *a=this->vDinamicos[i];
        for(uint16_t j=0; j<tam; j++)
        {
            CSprite *b=vVisible[j];
            if(a==b)
                continue;
            if( a->SolapaEntidad(b))
                a->entidadesDebajo.push_back(b);

        }
        a->visitado=false;
    }



    int sortDepth=0;
    for(uint16_t  i=0; i<tam; i++)
        this->VisitNode(vVisible[i],&sortDepth);



    sort( vVisible.begin( ), vVisible.end( ), [ ]( const CSprite* lhs, const CSprite* rhs )
    {
        return lhs->Depth <rhs->Depth;
    });

}

void CWorld::OrdenaTopologicamente2()
{
    int tam=vVisible.size();
    this->PreSortByXY(vVisible);

    for(int i=0; i<tam; i++)
    {
        CSprite *a=this->vVisible[i];

        for(uint16_t j=0; j<tam; j++)
        {
            if(i==j)
                continue;

            CSprite *b=vVisible[j];
            if( a->SolapaEntidad(b))
                a->entidadesDebajo.push_back(b);

        }
        a->visitado=false;
    }


    int sortDepth=0;
    for(uint16_t  i=0; i<tam; i++)
        this->VisitNode(vVisible[i],&sortDepth);



    sort( vVisible.begin( ), vVisible.end( ), [ ]( const CSprite* lhs, const CSprite* rhs )
    {
        return lhs->Depth < rhs->Depth;
    });

}
void CWorld::PreSortByXY(vector<CSprite*> &v)
{
    sort(  v.begin( ),  v.end( ), [ ]( const CSprite* lhs, const CSprite* rhs )
    {
        return ((lhs->Pos.x+lhs->Pos.y) < (rhs->Pos.x+rhs->Pos.y));
    });
}

ViewPort  CWorld::GetViewPort(int width,int height)
{
    ViewPort viewport;

    int offsety=(this->engine->player->PosProj.y);
    int offsetx=(this->engine->player->PosProj.x);
    Vec2D pos0;
    pos0.x=SCREEN_W-orig.x-80+offsetx;
    pos0.y=SCREEN_H-orig.y-32+offsety;
    pos0=utils::twoDToIso(&pos0); //hay que corregir el nombre esta mal

    pos0.y=pos0.y/32+1;
    pos0.x=pos0.x/32+1;

    if(pos0.x>width)
        pos0.x=width;



    Vec2D pos1;
    pos1.x=0-orig.x+offsetx;
    pos1.y=SCREEN_H-orig.y-32+offsety;
    pos1=utils::twoDToIso(&pos1);
    pos1.y=pos1.y/32+1;
    pos1.x=pos1.x/32+1;

    if(pos1.y>height)
        pos1.y=height;

    Vec2D pos2;
    pos2.x=0-orig.x+offsetx;
    pos2.y=0-orig.y+offsety;
    pos2=utils::twoDToIso(&pos2);
    pos2.y=pos2.y/32-2;
    pos2.x=pos2.x/32-2;
    if(pos2.x<0)
        pos2.x=0;
    if(pos2.y<0)
        pos2.y=0;


    Vec2D pos3;
    pos3.x=SCREEN_W-orig.x+offsetx;
    pos3.y=0-orig.y+offsety;
    pos3=utils::twoDToIso(&pos3);
    pos3.y=pos3.y/32-1;
    pos3.x=pos3.x/32-1;
    if(pos3.x<0)
        pos3.x=0;
    if(pos3.y<0)
        pos3.y=0;

    viewport.p1.y=pos3.y;
    viewport.p2.y=pos1.y;

    viewport.p1.x=pos2.x;
    viewport.p2.x=pos0.x;

    return viewport;
}
