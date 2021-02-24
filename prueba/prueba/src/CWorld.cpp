#include "CWorld.h"
#include <algorithm>
#include <cstdio>

CWorld::CWorld(cEngine *engine)
{

    this->tilemap=this->LoadTmx("mapa2.tmx");
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
    vector<CSprite*> vOrder =this->ProcesaDepthSprites();


    clear_to_color(this->engine->buffer, makecol(0, 0, 0));
    acquire_screen();


    for(uint16_t  i=0; i<vOrder.size(); i++)
    {
        CTile *t=dynamic_cast<CTile*>(vOrder[i]);
        CSprite * e=dynamic_cast<CSprite*>(vOrder[i]);

        if(t== 0)
        {

            masked_blit(this->engine->tiles[0], this->engine->buffer, 0, 0,  e->PosProj.x+this->orig.x,  e->PosProj.y+this->orig.y, this->engine->tileW,this->engine->tileH);

        }
        else
        {
            masked_blit(this->engine->tiles[t->indiceTile], this->engine->buffer, 0, 0, t->PosProj.x+this->orig.x, t->PosProj.y+this->orig.y, this->engine->tileW,this->engine->tileH);
            char tempStr2 [100];
            // snprintf ( tempStr2, 100, "(%d,%d)", t->j,  t->i );
            sprintf ( tempStr2,  "(%d)", e->Depth );
            //  textout_centre_ex(this->engine->buffer, font, tempStr2, e->PosProj.x+this->orig.x+32,e->PosProj.y+this->orig.y+32, makecol(255,255,255), -1);

        }


    }



    char tempStr [100];


    CLayer *capa=this->tilemap->Layers[0];
    CTile *t=capa->tiles[val2.x+val2.y*capa->width];


    snprintf ( tempStr, 100, "player x:%d px:%d player y:%d py:%d tile:%d,%d val:%d", this->engine->player->Pos.x,this->engine->player->PosProj.x,  this->engine->player->Pos.y,this->engine->player->PosProj.y,val2.x,val2.y,t->indiceTile );




    textout_centre_ex(this->engine->buffer, font, tempStr, SCREEN_W/2, 20, makecol(255,255,255), -1);



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

    this->engine->player->Depth=0;
    this->engine->player->visitado=false;
    this->engine->player->entidadesDebajo.clear();
    this->vSprites.clear();
    this->vSprites.push_back(this->engine->player);

    CLayer *capa=this->tilemap->Layers[0];
    for(int j=0; j<capa->height; j++)
        for(int i=0; i<capa->width; i++)
        {
            //la i es Y
            //la j es X
            CTile *t= capa->GetTile(i,j);
            this->vSprites.push_back(t);
        }

}

vector<CSprite*> CWorld::ProcesaDepthSprites()
{
     // for(int i=0; i<this->vSprites.size(); i++)
     //{
    CSprite *a=this->engine->player;
    for(uint16_t j=0; j<this->vSprites.size(); j++)
    {
        /* if(i==j)
             continue;*/

        CSprite *b=this->vSprites[j];
        if( a->SolapaEntidad(b))
        {
            a->entidadesDebajo.push_back(b);
        }
    }
    a->visitado=false;
    // }


    int sortDepth=0;
    for(uint16_t  i=0; i<this->vSprites.size(); i++)
        this->VisitNode(this->vSprites[i],&sortDepth);


    vector<CSprite*> vOrder=vector<CSprite*>(this->vSprites);
    sort( vOrder.begin( ), vOrder.end( ), [ ]( const CSprite* lhs, const CSprite* rhs )
    {
        return lhs->Depth < rhs->Depth;
    });


    return vOrder;
}

