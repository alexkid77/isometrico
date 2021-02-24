#include "CTile.h"

CTile::CTile(int tileGridW,int tileGridH,int tileSize):CSprite(tileGridW,tileGridH,tileSize)
{
    this->indiceTile=0;
    //ctor
}

CTile::~CTile()
{
    int x=0;
    x++;
    //dtor
}
