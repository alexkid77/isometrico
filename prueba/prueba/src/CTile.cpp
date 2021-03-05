#include "CTile.h"

CTile::CTile(int tileGridW,int tileGridH,int tileSize):CSprite(tileGridW,tileGridH,tileSize)
{
    this->indiceTile=0;
    this->Tipo=TILE;
    //ctor
}

CTile::~CTile()
{
    int x=0;
    x++;
    //dtor
}
void CTile::onCollision(CEntity *ent)
{

}
