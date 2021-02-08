#include "cEngine.h"

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

    this->player.pos.x=0;
    this->player.pos.y=0;
    //ctor
}

cEngine::~cEngine()
{
    //dtor
}
void cEngine::Update()
{
    if(key[KEY_UP])
        this->player.pos.y-=1;
    if(key[KEY_DOWN])
        this->player.pos.y+=1;

    if(key[KEY_LEFT])
        this->player.pos.x-=1;
    if(key[KEY_RIGHT])
        this->player.pos.x+=1;
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
    mousePos.x=mouse_x-orig.x-this->tileGridW/2;
    mousePos.y=mouse_y-orig.y-this->tileGridH;

    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            int x = (j-i) *(tileGridW/2);
            int y = (i+j )* (tileGridH/2);
            /*   int sx = (Tile->x - Tile->y) * (32); //64 is our width, multiply by half
            int sy = (Tile->x + Tile->y) * (16); //32 is our height, multiply by half*/
            Vec2D v;
            v.x=x;
            v.y=y;
            Vec2D vdest=v;

            Vec2D val=this->GetTileWithPos(mousePos.x,mousePos.y);

            if(mapa[j][i])
            {
                if(val.x==j && val.y==i)
                {
                    mapa[j][i]=0;
                }
                //   masked_blit(tiles[2], buffer, 0, 0, vdest.x+this->orig.x, vdest.y+this->orig.y, tileW,tileH);
                //else
                masked_blit(tiles[mapa[j][i]+1], buffer, 0, 0, vdest.x+this->orig.x, vdest.y+this->orig.y, tileW,tileH);
            }

        }
    }

    char tempStr [100];

Vec2D val;



    if( this->player.pos.x<=0)
        this->player.pos.x=0;
    if( this->player.pos.y<=0)
        this->player.pos.y=0;
         Vec2D v1;

    v1.x=this->player.pos.x;
    v1.y=this->player.pos.y;
    v1=this->twoDToIso(&v1);
     val=this->GetTileWithPos(v1.x,  v1.y);
    Vec2D orig_proj=this->twoDToIso(&this->orig);
    v1.x=v1.x;
    v1.y=v1.y;
    masked_blit(tiles[9], buffer, 0, 0, v1.x+this->orig.x, v1.y+this->orig.y, tileW,tileH);


 snprintf ( tempStr, 100, "player x:%d player y:%d tile:%d,%d", this->player.pos.x,  this->player.pos.y,val.y,val.x );


    //snprintf ( tempStr, 100, "player x:%d player y:%d tile:%d,%d", this->player.pos.x,  this->player.pos.y,val.y,val.x );

    // masked_blit(tiles[2], buffer, 0, 0,  mousePos.x+this->orig.x-this->tileGridW/2,  mousePos.y+this->orig.y-this->tileGridH/2, tileW,tileH);

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
