#include "cEngine.h"
#include "cMap.h";
cEngine::cEngine()
{
    this->buffer=create_bitmap(SCREEN_W,SCREEN_H);
    this->tileH=64;
    this->tileW=64;
    this->tileGridH= this->tileH/2;
    this->tileGridW=this->tileW;
    this->orig.x=SCREEN_W/2-tileW/2;
    this->orig.y=SCREEN_H/4-tileH/4;
    BITMAP *tilesRaw=load_bmp("tiles.bmp", 0);
    tiles=ExtraeTiles(tilesRaw,tileW,tileH);

    this->player.Pos.x=3;
    this->player.Pos.y=18;
    this->mapa=new cMap(this);
    //ctor
}

cEngine::~cEngine()
{
    //dtor
}
void cEngine::Update()
{
    int inc=1;
    this->player.PosAnt=this->player.Pos;
    if(key[KEY_UP])
        this->player.Pos.y-=inc;
    if(key[KEY_DOWN])
        this->player.Pos.y+=inc;

    if(key[KEY_LEFT])
        this->player.Pos.x-=inc;
    if(key[KEY_RIGHT])
        this->player.Pos.x+=inc;

    if(key[KEY_SPACE])
        this->debug=!this->debug;


}
void cEngine::Render()
{


    this->mapa->Render();


}


BITMAP **cEngine::ExtraeTiles(BITMAP *tilesRaw,int tileW,int tileH)
{
    BITMAP **tiles=new BITMAP*[8*10];
    int c=0;
    for( int y=0; y<8; y++)
    {
        for(int x=0; x<10; x++)
        {
            tiles[c]= create_bitmap(tileW, tileH);
            BITMAP *tile=tiles[c];
            blit(tilesRaw, tile, x*tileW, y*tileH, 0, 0, tileW,tileH);
            c++;
        }
    }


    return tiles;
}

Vec2D cEngine::isoTo2D(Vec2D *vec)
{
    Vec2D val;
    val.x = (2 * vec->y + vec->x) / 2;
    val.y = (2 * vec->y - vec->x) / 2;
    return val;
}

Vec2D cEngine::twoDToIso(Vec2D *vec)
{

    Vec2D val;
    val.x=vec->x-vec->y;
    val.y=(vec->x+vec->y)/2;
    return val;

    //int  isoX = ( ((ScreenY + scrollY) / tileHeight) + ((screenX + scrollX) - (isoMapMaxY * tileWidth/2)) / tileWidth )
//int isoY = ( ((screenY + scrollY) / tileHeight) - ((screenX + scrollX) - (isoMapMaxY * tileWidth/2)) / tileWidth )
}
Vec2D cEngine::GetTileWithPos(int x,int y)
{

    Vec2D res;
    int pixel_x=x;
    int pixel_y=y;
    int tile_w=64;
    int tile_h=32;
    int tile_x = (pixel_x/(tile_w/2) + pixel_y/(tile_h/2)) / 2;
    int tile_y = (pixel_y/(tile_h/2) - pixel_x/(tile_w/2)) / 2;
    //convert back to integer
    res.x =tile_x;
    res.y =tile_y;
    return res;
}
Vec2D cEngine::setAltura(Vec2D *pos,int tileSizeH,int altura,int tileHeight)
{
    Vec2D val;
    val.y= pos->y-(altura*tileHeight);
    val.x=pos->x;
    return val;
}
