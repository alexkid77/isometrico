#include "CWorld.h"
#include <algorithm>
CWorld::CWorld(cEngine *engine)
{
    this->tileGridH= engine->tileGridH;
    this->tileGridW= engine->tileGridW;
    this->orig=engine->orig;
    this->engine=engine;
    this->InitSprites();

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






    if( this->engine->player->Pos.x<=0)
        this->engine->player->Pos.x=0;
    if( this->engine->player->Pos.y<=0)
        this->engine->player->Pos.y=0;

    if( this->engine->player->Pos.x>((12*32)-32))
        this->engine->player->Pos.x=12*32-32;
    if( this->engine->player->Pos.y>((12*32)-32))
        this->engine->player->Pos.y=12*32-32;
    //mirar que tiles pisa
    vector<Vec2D> tilesOcupados=this->engine->player->getTilesOcupados();
    for(uint16_t i=0; i<tilesOcupados.size(); i++)
    {
        Vec2D tile=tilesOcupados[i];
        if(mapa[tile.x][tile.y]!=3)
        {
            this->engine->player->Pos=this->engine->player->PosAnt;
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



    vector<CSprite*> vOrder =this->ProcesaDepthSprites();

    clear_to_color(this->engine->buffer, makecol(0, 0, 0));
    acquire_screen();


    /* you must always release bitmaps before calling any input functions */
    Vec2D mousePos;
    mousePos.x=mouse_x-orig.x-this->tileGridW/2;
    mousePos.y=mouse_y-orig.y-this->tileGridH;


    for(uint16_t  i=0; i<vOrder.size(); i++)
    {
        Tile *t=dynamic_cast<Tile*>(vOrder[i]);
        CSprite * e=dynamic_cast<CSprite*>(vOrder[i]);
        int sortTam=e->Depth;
        if(t== nullptr)
        {

            masked_blit(this->engine->tiles[9], this->engine->buffer, 0, 0,  e->PosProj.x+this->orig.x,  e->PosProj.y+this->orig.y, this->engine->tileW,this->engine->tileH);

        }
        else
        {
            masked_blit(this->engine->tiles[t->indiceTile], this->engine->buffer, 0, 0, t->PosProj.x+this->orig.x, t->PosProj.y+this->orig.y, this->engine->tileW,this->engine->tileH);
            char tempStr2 [100];
            // snprintf ( tempStr2, 100, "(%d,%d)", t->j,  t->i );
            snprintf ( tempStr2, 100, "(%d)", e->Depth );
            textout_centre_ex(this->engine->buffer, font, tempStr2, e->PosProj.x+this->orig.x+32,e->PosProj.y+this->orig.y+32, makecol(255,255,255), -1);

        }


    }



    char tempStr [100];






    snprintf ( tempStr, 100, "player x:%d px:%d player y:%d py:%d tile:%d,%d val:%d", this->engine->player->Pos.x,this->engine->player->PosProj.x,  this->engine->player->Pos.y,this->engine->player->PosProj.y,val2.x,val2.y,mapa[val2.x][val2.y] );




    textout_centre_ex(this->engine->buffer, font, tempStr, SCREEN_W/2, 20, makecol(255,255,255), -1);

    //tres posiciones
    /*   putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+64,playerProj.y+this->engine->orig.y+32+16,makecol(255,255,255));
       putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x,playerProj.y+this->engine->orig.y+32+16,makecol(0,255,0));
       putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+64,makecol(255,0,0));
       putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+32,makecol(255,0,0));*/

    blit(this->engine->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);


    release_screen();
}

void CWorld::VisitNode(CSprite *ent,int *sortDepth)
{

    if(ent->id==777)
    {
        int kk=0;
        kk++;
    }
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

    for(int j=0; j<12; j++)
    {
        for(int i=0; i<12; i++)
        {
            //la i es Y
            //la j es X
            int x = (j-i) *(tileGridW/2);
            int y = (i+j )* (tileGridH/2);
            Tile *t=new Tile(this->engine->tileSize,this->engine->tileSize,this->engine->tileSize);
            t->indiceTile=mapa[j][i];
            t->Pos.x=j*this->engine->tileSize;
            t->Pos.y=i*this->engine->tileSize;
            t->i=i;
            t->j=j;
            t->PosProj.x=x;
            t->PosProj.y=y;

            this->vSprites.push_back(t);


        }

    }
}

vector<CSprite*> CWorld::ProcesaDepthSprites()
{
    //  for(int i=0; i<vTiles.size(); i++)
    // {
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
    {
        this->VisitNode(this->vSprites[i],&sortDepth);
    }
    vector<CSprite*> vOrder=vector<CSprite*>(this->vSprites);
    sort( vOrder.begin( ), vOrder.end( ), [ ]( const CSprite* lhs, const CSprite* rhs )
    {
        return lhs->Depth < rhs->Depth;
    });
    return vOrder;
}
