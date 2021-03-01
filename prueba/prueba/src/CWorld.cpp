#include "CWorld.h"
#include <algorithm>
#include <cstdio>

CWorld::CWorld(cEngine *engine)
{

    this->tilemap=this->LoadTmx("mapa3.tmx");
    this->tileGridH= engine->tileGridH;
    this->tileGridW= engine->tileGridW;
    this->orig=engine->orig;
    this->engine=engine;
    this->InitSprites();

}
CTileMap * CWorld::LoadTmx(string file)
{
    CTileMap *tilemap=new CTileMap(file);
    return tilemap;
    // map.layerCollection
}
CWorld::~CWorld()
{
    //dtor
}
void CWorld::Update()
{
    this->engine->player->ClearDepth();

    for(uint16_t  i=0; i<this->vSprites.size(); i++)
        this->vSprites[i]->ClearDepth();


    /*  sort(  this->vSprites.begin( ),  this->vSprites.end( ), [ ]( const CSprite* lhs, const CSprite* rhs )
      {
          return ((lhs->Pos.x+lhs->Pos.y) < (rhs->Pos.x+rhs->Pos.y));
      });*/

    CLayer *capa=this->tilemap->Layers[0];

    if( this->engine->player->Pos.x<=0)
        this->engine->player->Pos.x=0;
    if( this->engine->player->Pos.y<=0)
        this->engine->player->Pos.y=0;

    if( this->engine->player->Pos.x>((capa->width*32)-32))
        this->engine->player->Pos.x=capa->width*32-32;
    if( this->engine->player->Pos.y>((capa->height*32)-32))
        this->engine->player->Pos.y=capa->height*32-32;

    //mirar que tiles pisa
    vector<Vec2D> tilesOcupados=this->engine->player->getTilesOcupados();

    for(uint16_t i=0; i<tilesOcupados.size(); i++)
    {
        Vec2D tile=tilesOcupados[i];
        CTile *t=capa->GetTile(tile.x,tile.y);
        if(t->indiceTile==2)
        {
            this->engine->player->Pos=this->engine->player->PosAnt;
            this->engine->player->onCollision();
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
    this->ProcesaDepthSprites();


    clear_to_color(this->engine->buffer, makecol(0, 0, 0));
    acquire_screen();

    int offsetx=this->engine->player->PosProj.x;
    int offsety=this->engine->player->PosProj.y;
    for(uint16_t  i=0; i<this->vVisible.size(); i++)
    {
        CTile *t=dynamic_cast<CTile*>(this->vVisible[i]);
        CSprite * e=dynamic_cast<CSprite*>(this->vVisible[i]);

        if(t== 0)
        {

            masked_blit(this->engine->tiles[0], this->engine->buffer, 0, 0,  e->PosProj.x+this->orig.x-offsetx,  e->PosProj.y+this->orig.y-offsety, this->engine->tileW,this->engine->tileH);

        }
        else
        {
            masked_blit(this->engine->tiles[t->indiceTile], this->engine->buffer, 0, 0, t->PosProj.x+this->orig.x-offsetx, t->PosProj.y+this->orig.y-offsety, this->engine->tileW,this->engine->tileH);
            char tempStr2 [100];
            snprintf ( tempStr2, 100, "(%d,%d)", t->j,  t->i );
            //sprintf ( tempStr2,  "(%d)", e->Depth );
            // textout_centre_ex(this->engine->buffer, font, tempStr2, e->PosProj.x+this->orig.x-offsetx+32, e->PosProj.y+this->orig.y-offsety+32, makecol(255,255,255), -1);

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

    Vec2D pos1;
    pos1.x=SCREEN_W;
    pos1.y=SCREEN_H;
    pos1=utils::twoDToIso(&pos1);
    putpixel(this->engine->buffer,pos1.x,pos1.y,makecol(255,0,0));

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

    this->engine->player->Depth=0;
    this->engine->player->visitado=false;
    this->engine->player->entidadesDebajo.clear();

    this->vSprites.push_back(this->engine->player);

}

void CWorld::ProcesaDepthSprites()
{


    int ntiles=32;

    this->vVisible.clear();

    CLayer *capa=this->tilemap->Layers[0];
    int offsety=(this->engine->player->PosProj.y);
    int offsetx=(this->engine->player->PosProj.x);

    Vec2D pos0;
    pos0.x=SCREEN_W-orig.x-80+offsetx;
    pos0.y=SCREEN_H-orig.y-32+offsety;
    pos0=utils::isoTo2D(&pos0); //hay que corregir el nombre esta mal

    pos0.y=pos0.y/32+1;
    pos0.x=pos0.x/32+1;

    if(pos0.x>capa->width)
        pos0.x=capa->width;



    Vec2D pos1;
    pos1.x=0-orig.x+offsetx;
    pos1.y=SCREEN_H-orig.y-32+offsety;
    pos1=utils::isoTo2D(&pos1);
    pos1.y=pos1.y/32+1;
    pos1.x=pos1.x/32+1;

    if(pos1.y>capa->width)
        pos1.y=capa->width;

    Vec2D pos2;
    pos2.x=0-orig.x+offsetx;
    pos2.y=0-orig.y+offsety;
    pos2=utils::isoTo2D(&pos2);
    pos2.y=pos2.y/32-2;
    pos2.x=pos2.x/32-2;
    if(pos2.x<0)
        pos2.x=0;
    if(pos2.y<0)
        pos2.y=0;


    Vec2D pos3;
    pos3.x=SCREEN_W-orig.x+offsetx;
    pos3.y=0-orig.y+offsety;
    pos3=utils::isoTo2D(&pos3);
    pos3.y=pos3.y/32-1;
    pos3.x=pos3.x/32-1;
    if(pos3.x<0)
        pos3.x=0;
    if(pos3.y<0)
        pos3.y=0;
    // pos0= utils::GetTileWithPos(32,32,pos0.x,pos0.y);


    for(int y=pos3.y; y<pos1.y ; y++)
        for(int x=pos2.x; x<pos0.x; x++)
        {
            CSprite *s=  capa->tiles[x+y*capa->width];

            vVisible.push_back(s);
        }

    vVisible.push_back(this->engine->player);
    int tam=vVisible.size();
    this->PreSortByXY(vVisible);

    // for(int i=0; i<this->vSprites.size(); i++)
    //{
    CSprite *a=this->engine->player;
    for(uint16_t j=0; j<vVisible.size(); j++)
    {
        /* if(i==j)
             continue;*/

        CSprite *b=vVisible[j];
        if( a->SolapaEntidad(b))
        {
            a->entidadesDebajo.push_back(b);
        }
    }
    a->visitado=false;
    // }


    int sortDepth=0;
    for(uint16_t  i=0; i<vVisible.size(); i++)
        this->VisitNode(vVisible[i],&sortDepth);



    sort( vVisible.begin( ), vVisible.end( ), [ ]( const CSprite* lhs, const CSprite* rhs )
    {
        return lhs->Depth < rhs->Depth;
    });


    return ;
}

void CWorld::PreSortByXY(vector<CSprite*> &v)
{
    sort(  v.begin( ),  v.end( ), [ ]( const CSprite* lhs, const CSprite* rhs )
    {
        return ((lhs->Pos.x+lhs->Pos.y) < (rhs->Pos.x+rhs->Pos.y));
    });
}
