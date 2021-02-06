#include "cEngine.h"

cEngine::cEngine()
{
    this->buffer=create_bitmap(SCREEN_W,SCREEN_H);
    this->tileH=64;
    this->tileW=64;
    this->tileGridH= this->tileH/2;
    this->tileGridW=this->tileW/2;
    this->orig.x=SCREEN_W/2-tileW/2;
    this->orig.y=SCREEN_H/4-tileH/4;
    BITMAP *tilesRaw=load_bmp("tiles.bmp", 0);
    tiles=ExtraeTiles(tilesRaw,tileW,tileH);
    //ctor
}

cEngine::~cEngine()
{
    //dtor
}
void cEngine::Update()
{
}
void cEngine::Render()
{



    unsigned char mapa[12][12]=
    {
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1},
          {1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1},
              {1,1,1,1,1,1,1,1,1,1,1,1},
                {1,1,1,1,1,1,1,1,1,1,1,1}

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




    clear_to_color(buffer, makecol(0, 0, 0));
    acquire_screen();
    for(int i=0; i<2; i++)
        /* write some text to the screen with black letters and transparent background */
        textout_centre_ex(buffer, font, "Hello, world!", SCREEN_W/2, SCREEN_H/2+i*4, makecol(255,255,255), -1);

    /* you must always release bitmaps before calling any input functions */
    Vec2D mousePos;
    mousePos.x=mouse_x-orig.x;
    mousePos.y=mouse_y-orig.y;
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            int x = j * tileGridH;
            int y = i * tileGridW;
            Vec2D v;
            v.x=x;
            v.y=y;
            Vec2D vdest=twoDToIso(&v);
            // vdest=setAltura(&vdest,20,0,32);
            Vec2D val=this->GetTileWithPos(mousePos.x,mousePos.y);

            if(mapa[j][i])
            {
                if(val.x==j && val.y==i)
                {
                 mapa[j][i]=2;
                }
                 //   masked_blit(tiles[2], buffer, 0, 0, vdest.x+this->orig.x, vdest.y+this->orig.y, tileW,tileH);
                //else
                    masked_blit(tiles[mapa[j][i]], buffer, 0, 0, vdest.x+this->orig.x, vdest.y+this->orig.y, tileW,tileH);
            }

        }
    }

    char tempStr [100];


    //mousePos=this->twoDToIso(&mousePos);


    Vec2D val=this->GetTileWithPos(mousePos.x,mousePos.y);

    snprintf ( tempStr, 100, "mouse x:%d mouse y:%d tile:%d,%d", mousePos.x,  mousePos.y,val.y,val.x );

    masked_blit(tiles[2], buffer, 0, 0,  mousePos.x+this->orig.x,  mousePos.y+this->orig.y, tileW,tileH);

    textout_centre_ex(buffer, font, tempStr, SCREEN_W/2, 20, makecol(255,255,255), -1);

    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);


    release_screen();

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
    int tileHeight=32;
    int ScrollY=0;
    int ScrollX=0;
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
