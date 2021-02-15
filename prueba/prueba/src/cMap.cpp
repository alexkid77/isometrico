#include "cMap.h"
#include <algorithm>
cMap::cMap(cEngine *engine)
{
    this->tileGridH= engine->tileGridH;
    this->tileGridW= engine->tileGridW;
    this->orig=engine->orig;
    this->engine=engine;
}

cMap::~cMap()
{
    //dtor
}
void cMap::Update()
{

}
void cMap::Render()
{
    unsigned char mapa[12][12]=
    {
        {3,1,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,1,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3}

    };

    unsigned char layer[8][8]=
    {
        {1,1,1,0,1,1,1,1},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},

    };

    unsigned char layer2[8][8]=
    {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},

    };




    Vec2D val2;


    /*if(mapa[j][i]!=3)
        this->engine->player.Pos=this->engine->player.PosAnt;*/

    if( this->engine->player->Pos.x<=0)
        this->engine->player->Pos.x=0;
    if( this->engine->player->Pos.y<=0)
        this->engine->player->Pos.y=0;

    if( this->engine->player->Pos.x>((12*32)-32))
        this->engine->player->Pos.x=12*32-32;
    if( this->engine->player->Pos.y>((12*32)-32))
        this->engine->player->Pos.y=12*32-32;
    Vec2D playerProj=this->engine->player->getPosProj();

    vector<Vec2D> tilesOcupados=this->engine->player->getTilesOcupados();
      playerProj.x=this->engine->player->Pos.x;
       playerProj.y=this->engine->player->Pos.y;
       playerProj=utils::twoDToIso(&playerProj);
this->engine->player->PosProj=playerProj;
    // val=this->engine->GetTileWithPos(playerProj.x,  playerProj.y);
    val2.x=this->engine->player->Pos.x/32;
    val2.y=this->engine->player->Pos.y/32;
    Vec2D tilePlayer=utils::GetTileWithPos(this->tileGridW,this->tileGridH,playerProj.x,playerProj.y);
//obtener si pisa tile


    clear_to_color(this->engine->buffer, makecol(0, 0, 0));
    acquire_screen();
    for(int i=0; i<2; i++)
        /* write some text to the screen with black letters and transparent background */
        textout_centre_ex(this->engine->buffer, font, "Hello, world!", SCREEN_W/2, SCREEN_H/2+i*4, makecol(255,255,255), -1);

    /* you must always release bitmaps before calling any input functions */
    Vec2D mousePos;
    mousePos.x=mouse_x-orig.x-this->tileGridW/2;
    mousePos.y=mouse_y-orig.y-this->tileGridH;

    vector<Entidad*> vTiles;
    this->engine->player->getDepth();
    vTiles.push_back(this->engine->player);
    for(int j=0; j<12; j++)
        for(int i=0; i<12; i++)
        {
            //la i es Y
            //la j es X
            int x = (j-i) *(tileGridW/2);
            int y = (i+j )* (tileGridH/2);
            Tile *t=new Tile(32,32);
            t->indiceTile=mapa[j][i];
            t->Pos.x=i*32;
            t->Pos.y=j*32;
            t->getDepth();
            t->PosProj.x=x;
            t->PosProj.y=y;
            vTiles.push_back(t);
        }
    sort( vTiles.begin( ), vTiles.end( ), [ ]( const Entidad* lhs, const Entidad* rhs )
    {
        return lhs->Depth < rhs->Depth;
    });

    for(int i=0; i<vTiles.size(); i++)
    {
        Tile *t=dynamic_cast<Tile*>(vTiles[i]);
        if(t== nullptr)
        {
            Entidad * e=dynamic_cast<Entidad*>(vTiles[i]);
            masked_blit(this->engine->tiles[9], this->engine->buffer, 0, 0,  e->PosProj.x+this->orig.x,  e->PosProj.y+this->orig.y, this->engine->tileW,this->engine->tileH);

        }
        else
            masked_blit(this->engine->tiles[t->indiceTile], this->engine->buffer, 0, 0, t->PosProj.x+this->orig.x, t->PosProj.y+this->orig.y, this->engine->tileW,this->engine->tileH);

    }

    /*
    mapa[0][1]=1;
    mapa[0][8]=1;
    vector<Vec2D> vTiles;
    for(int j=0; j<12; j++)
    {
    for(int i=0; i<12; i++)
    {
        //la i es Y
        //la j es X
        int x = (j-i) *(tileGridW/2);
        int y = (i+j )* (tileGridH/2);
        int depth=x+y;
        Vec2D v;
        v.x=x;
        v.y=y;
        Vec2D vdest=v;




        if(mapa[j][i])
        {

            masked_blit(this->engine->tiles[(mapa[j][i])], this->engine->buffer, 0, 0, vdest.x+this->orig.x, vdest.y+this->orig.y, this->engine->tileW,this->engine->tileH);
        }

        if(this->engine->player.OcupaTile(j,i))
        {
            masked_blit(this->engine->tiles[9], this->engine->buffer, 0, 0, playerProj.x+this->orig.x, playerProj.y+this->orig.y, this->engine->tileW,this->engine->tileH);
        }
        if(this->engine->debug)
        {
            char tempStr2 [100];
            snprintf ( tempStr2, 100, "(%d,%d)", j,  i );
            textout_centre_ex(this->engine->buffer, font, tempStr2, vdest.x+this->orig.x+32,vdest.y+this->orig.y+32, makecol(255,255,255), -1);
        }
    }
    }*/

    char tempStr [100];






    snprintf ( tempStr, 100, "player x:%d px:%d player y:%d py:%d tile:%d,%d val:%d", this->engine->player->Pos.x,playerProj.x,  this->engine->player->Pos.y,playerProj.y,val2.x,val2.y,mapa[val2.x][val2.y] );




    textout_centre_ex(this->engine->buffer, font, tempStr, SCREEN_W/2, 20, makecol(255,255,255), -1);

    //tres posiciones
    putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+64,playerProj.y+this->engine->orig.y+32+16,makecol(255,255,255));
    putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x,playerProj.y+this->engine->orig.y+32+16,makecol(0,255,0));
    putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+64,makecol(255,0,0));
    putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+32,makecol(255,0,0));

    blit(this->engine->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);


    release_screen();
}

