#include "cMap.h"

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




    Vec2D val;


    /*if(mapa[j][i]!=3)
        this->engine->player.Pos=this->engine->player.PosAnt;*/

    if( this->engine->player.Pos.x<=0)
        this->engine->player.Pos.x=0;
    if( this->engine->player.Pos.y<=0)
        this->engine->player.Pos.y=0;

    if( this->engine->player.Pos.x>((12*32)-32))
        this->engine->player.Pos.x=12*32-32;
    if( this->engine->player.Pos.y>((12*32)-32))
        this->engine->player.Pos.y=12*32-32;
    Vec2D playerProj;

    playerProj.x=this->engine->player.Pos.x;
    playerProj.y=this->engine->player.Pos.y;
    playerProj=this->engine->twoDToIso(&playerProj);
    val=this->engine->GetTileWithPos(playerProj.x,  playerProj.y);
    Vec2D tilePlayer=this->GetTileWithPos(playerProj.x,playerProj.y);
//obtener si pisa tile

    Vec2D tilePlayer2=this->GetTileWithPos(playerProj.x+64,playerProj.y);
    Vec2D tilePlayer3=this->GetTileWithPos(playerProj.x,playerProj.y+32);
    clear_to_color(this->engine->buffer, makecol(0, 0, 0));
    acquire_screen();
    for(int i=0; i<2; i++)
        /* write some text to the screen with black letters and transparent background */
        textout_centre_ex(this->engine->buffer, font, "Hello, world!", SCREEN_W/2, SCREEN_H/2+i*4, makecol(255,255,255), -1);

    /* you must always release bitmaps before calling any input functions */
    Vec2D mousePos;
    mousePos.x=mouse_x-orig.x-this->tileGridW/2;
    mousePos.y=mouse_y-orig.y-this->tileGridH;

    mapa[0][1]=8;
    mapa[0][8]=8;
    for(int j=0; j<12; j++)
    {
        for(int i=0; i<12; i++)
        {
            //la i es Y
            //la j es X
            int x = (j-i) *(tileGridW/2);
            int y = (i+j )* (tileGridH/2);
            /*   int sx = (Tile->x - Tile->y) * (32); //64 is our width, multiply by half
            int sy = (Tile->x + Tile->y) * (16); //32 is our height, multiply by half*/
            Vec2D v;
            v.x=x;
            v.y=y;
            Vec2D vdest=v;

            // Vec2D val=this->GetTileWithPos(mousePos.x,mousePos.y);


            if(mapa[j][i])
            {

                masked_blit(this->engine->tiles[(mapa[j][i])], this->engine->buffer, 0, 0, vdest.x+this->orig.x, vdest.y+this->orig.y, this->engine->tileW,this->engine->tileH);
            }

            if((tilePlayer.y==i && tilePlayer.x==j)
                    /* || ((tilePlayer.y+1)==(i) && tilePlayer.x==j)
                     || ((tilePlayer.y-1)==(i) && tilePlayer.x==j)
                     || (tilePlayer.y==i && (tilePlayer.x-1)==(j))
                     ||(tilePlayer.y==i && (tilePlayer.x+1)==(j))*/

              )
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
    }

    char tempStr [100];






    snprintf ( tempStr, 100, "player x:%d px:%d player y:%d py:%d tile:%d,%d val:%d", this->engine->player.Pos.x,playerProj.x,  this->engine->player.Pos.y,playerProj.y,tilePlayer.x,tilePlayer.y,mapa[val.x][val.y] );




    textout_centre_ex(this->engine->buffer, font, tempStr, SCREEN_W/2, 20, makecol(255,255,255), -1);

    //tres posiciones
    putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+64,playerProj.y+this->engine->orig.y+32+16,makecol(255,255,255));
    putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x,playerProj.y+this->engine->orig.y+32+16,makecol(0,255,0));
    putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+64,makecol(255,0,0));
  putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+32,makecol(255,0,0));

    blit(this->engine->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);


    release_screen();
}

Vec2D cMap::GetTileWithPos(int x,int y)
{

    Vec2D res;
    int pixel_x=x;
    int pixel_y=y;
    int tile_w=this->tileGridW;
    int tile_h=this->tileGridH;
    int tile_x = (pixel_x/(tile_w/2) + pixel_y/(tile_h/2)) / 2;
    int tile_y = (pixel_y/(tile_h/2) - pixel_x/(tile_w/2)) / 2;
    //convert back to integer
    res.x =tile_x;
    res.y =tile_y;
    return res;
}
