#include "CVideoSystemAllegro.h"

CVideoSystemAllegro::CVideoSystemAllegro(int width,int height):IVideoSystem(width,height)
{
    this->width=width;
    this->height=height;
    this->buffer=create_bitmap( this->width,this->height);

}
int CVideoSystemAllegro::getWidth()
{
    this->width;
}

int CVideoSystemAllegro::getHeight()
{
    this->height;
}

void CVideoSystemAllegro::Blit(int indexTile,Rect Src,Rect Dest)
{
   masked_blit(this->tiles[indexTile], this->buffer, Src.orig.x, Src.orig.y,  Dest.orig.x, Dest.orig.y, Src.sizes.x,Src.sizes.y);
}

void CVideoSystemAllegro::TextOut(int x,int y,char *text,int color)
{
  textout_centre_ex(this->buffer, font, text, x, y, makecol(255,0,0), -1);
}
void CVideoSystemAllegro::ToScreen()
{
    acquire_screen();
    blit(this->buffer,screen,0,0,0,0,this->width,this->height);

    release_screen();
}
void CVideoSystemAllegro::LoadTiles(int tileW,int tileH)
{
    this->tiles=new BITMAP*[5];
    BITMAP *tilesRaw=load_bmp("tile2.bmp", 0);
    int c=0;
    for( int y=0; y<1; y++)
        for(int x=0; x<5; x++)
        {
            tiles[c]= create_bitmap(tileW, tileH);
            BITMAP *tile=tiles[c];
            blit(tilesRaw, tile, x*tileW, y*tileH, 0, 0, tileW,tileH);
            c++;
        }
}

CVideoSystemAllegro::~CVideoSystemAllegro()
{
    //dtor
}
