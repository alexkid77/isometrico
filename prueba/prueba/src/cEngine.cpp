#include <CEngine.h>
#include <CWorld.h>
CEngine::CEngine()
{
    this->buffer=create_bitmap(SCREEN_W,SCREEN_H);
    this->tileH=80;
    this->tileW=64;
    this->tileSize=32;
    this->tileGridH= this->tileH/2;
    this->tileGridW=this->tileW;
    this->orig.x=SCREEN_W/2-tileW/2;
    this->orig.y=SCREEN_H/2-tileH/2;
    BITMAP *tilesRaw=load_bmp("tile2.bmp", 0);
    tiles=ExtraeTiles(tilesRaw,tileW,tileH);

    this->player= new CPlayer(this->tileGridW,this->tileGridH,this->tileSize);

    this->player->Pos.x=67;
    this->player->Pos.y=100;
    this->player->Pos.z=70;

    this->player->Size.x=32;
    this->player->Size.y=32;
    this->player->Size.z=80;
    this->mapa=new CWorld(this);

}

CEngine::~CEngine()
{
    //dtor
}
void CEngine::onPlayerCollision(CEntity *ent)
{
    int x=0;
    x++;
//   printf("Colision\n");
}
void CEngine::Update()
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

    if(key[KEY_C])
        if(this->player->Pos.z>1)
            this->player->Pos.z-=inc;
    if(key[KEY_D])
        this->player->Pos.z+=inc;

    if(key[KEY_SPACE])
        this->debug=!this->debug;


    this->mapa->Update();
}

void CEngine::Render()
{
    this->mapa->Render();
}


BITMAP **CEngine::ExtraeTiles(BITMAP *tilesRaw,int tileW,int tileH)
{
    BITMAP **tiles=new BITMAP*[5];
    int c=0;
    for( int y=0; y<1; y++)
        for(int x=0; x<5; x++)
        {
            tiles[c]= create_bitmap(tileW, tileH);
            BITMAP *tile=tiles[c];
            blit(tilesRaw, tile, x*tileW, y*tileH, 0, 0, tileW,tileH);
            c++;
        }



    return tiles;
}



Vec2D CEngine::setAltura(Vec2D *pos,int tileSizeH,int altura,int tileHeight)
{
    Vec2D val;
    val.y= pos->y-(altura*tileHeight);
    val.x=pos->x;
    return val;
}
