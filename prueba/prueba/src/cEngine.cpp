#include "cEngine.h"
#include "CWorld.h";
cEngine::cEngine()
{
    this->buffer=create_bitmap(SCREEN_W,SCREEN_H);
    this->tileH=80;
    this->tileW=64;
    this->tileSize=32;
    this->tileGridH= this->tileH/2;
    this->tileGridW=this->tileW;
    this->orig.x=SCREEN_W/2-tileW/2;
    this->orig.y=SCREEN_H/4-tileH/4;
    BITMAP *tilesRaw=load_bmp("tile2.bmp", 0);
    tiles=ExtraeTiles(tilesRaw,tileW,tileH);

    this->player= new CSprite(this->tileGridW,this->tileGridH,this->tileSize);
    //this->player->Pos.x=213;
    //this->player->Pos.y=142;
    this->player->Pos.x=0;
    this->player->Pos.y=0;
    this->player->onCollision=this->onPlayerCollision;
    this->mapa=new CWorld(this);
    //ctor
}

cEngine::~cEngine()
{
    //dtor
}
void cEngine::onPlayerCollision()
{
//   printf("Colision\n");
}
void cEngine::Update()
{

    int inc=1;
    this->player->PosAnt=this->player->Pos;
    if(key[KEY_UP])
        this->player->Pos.y-=inc;
    if(key[KEY_DOWN])
        this->player->Pos.y+=inc;

    if(key[KEY_LEFT])
        this->player->Pos.x-=inc;
    if(key[KEY_RIGHT])
        this->player->Pos.x+=inc;

    if(key[KEY_SPACE])
        this->debug=!this->debug;


    this->mapa->Update();

}

void cEngine::Render()
{


    this->mapa->Render();


}


BITMAP **cEngine::ExtraeTiles(BITMAP *tilesRaw,int tileW,int tileH)
{
    BITMAP **tiles=new BITMAP*[5];
    int c=0;
    for( int y=0; y<1; y++)
    {
        for(int x=0; x<5; x++)
        {
            tiles[c]= create_bitmap(tileW, tileH);
            BITMAP *tile=tiles[c];
            blit(tilesRaw, tile, x*tileW, y*tileH, 0, 0, tileW,tileH);
            c++;
        }
    }


    return tiles;
}



Vec2D cEngine::setAltura(Vec2D *pos,int tileSizeH,int altura,int tileHeight)
{
    Vec2D val;
    val.y= pos->y-(altura*tileHeight);
    val.x=pos->x;
    return val;
}
