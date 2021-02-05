#include "cEngine.h"

cEngine::cEngine()
{
    this->buffer=create_bitmap(SCREEN_W,SCREEN_H);
    this->tileH=64;
    this->tileW=64;
    this->tileGridH=32;
    this->tileGridW=32;

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



    unsigned char mapa[8][8]=
    {
        {0,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1}

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

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            int x = j * tileGridW;
            int y = i * tileGridH;
            Vec2D v;
            v.x=x;
            v.y=y;
            Vec2D vdest=twoDToIso(&v);
            vdest=setAltura(&vdest,20,0,32);
            if(mapa[j][i])
                masked_blit(tiles[0], buffer, 0, 0, vdest.x+SCREEN_W/2-tileW/2, vdest.y+SCREEN_H/2-tileH/2, tileW,tileH);
        }
    }
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            int x = j * tileGridW;
            int y = i * tileGridH;
            Vec2D v;
            v.x=x;
            v.y=y;
            Vec2D vdest=this->twoDToIso(&v);
            vdest=setAltura(&vdest,32,1,32);
            if(layer[j][i])
                masked_blit(tiles[0], buffer, 0, 0,  vdest.x+SCREEN_W/2-tileW/2, vdest.y+SCREEN_H/2-tileH/2, tileW,tileH);
        }
    }


    for(int k=0; k<9; k++)
        for(int i=0; i<8; i++)
        {
            for(int j=0; j<8; j++)
            {
                int x = j * tileGridW;
                int y = i * tileGridH;
                Vec2D v;
                v.x=x;
                v.y=y;
                Vec2D vdest=this->twoDToIso(&v);
                vdest=setAltura(&vdest,32,2+k,32);
                if(layer2[i][j])
                    masked_blit(tiles[0], buffer, 0, 0,  vdest.x+SCREEN_W/2-tileW/2, vdest.y+SCREEN_H/2-tileH/2, tileW,tileH);
            }
        }

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
}

Vec2D cEngine::setAltura(Vec2D *pos,int tileSizeH,int altura,int tileHeight)
{
    Vec2D val;
    val.y= pos->y-(altura*tileHeight);
    val.x=pos->x;
    return val;
}
