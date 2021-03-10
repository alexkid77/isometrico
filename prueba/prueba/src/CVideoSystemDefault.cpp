#include "CVideoSystemDefault.h"

CVideoSystemDefault::CVideoSystemDefault(int width,int height)
{
    this->width=width;
    this->height=height;
    if (allegro_init() == 0)
    {

        set_color_depth(32);
        /* set a graphics mode sized 320x200 */
        set_gfx_mode(GFX_SAFE, 800, 600,0, 0);
        this->buffer=create_bitmap( this->width,this->height);
    }

}
int CVideoSystemDefault::getWidth()
{
    return  this->width;
}

int CVideoSystemDefault::getHeight()
{
    return  this->height;
}

void CVideoSystemDefault::Blit(int indexTile,Rect Src,Rect Dest)
{
    masked_blit(this->tiles[indexTile], this->buffer, Src.orig.x, Src.orig.y,  Dest.orig.x, Dest.orig.y, Dest.sizes.x,Dest.sizes.y);
}

void CVideoSystemDefault::TextOut(int x,int y,char *text,sRGB color)
{
    textout_ex(this->buffer, font, text, x, y, makecol(color.r, color.g, color.b), -1);
}
void CVideoSystemDefault::ToScreen()
{
    acquire_screen();
    blit(this->buffer,screen,0,0,0,0,this->width,this->height);

    release_screen();
}
void CVideoSystemDefault::LoadTiles(int tileW,int tileH)
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
void CVideoSystemDefault::ClearToColor(sRGB color)
{
    clear_to_color(this->buffer, makecol(color.r, color.g, color.b));
}
void CVideoSystemDefault::TextOutCenter(int x,int y,char *text,sRGB color)
{
    textout_centre_ex(this->buffer, font, text, x, y, makecol(color.r, color.g, color.b), -1);
}

CVideoSystemDefault::~CVideoSystemDefault()
{
    //dtor
}
