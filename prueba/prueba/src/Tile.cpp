#include "Tile.h"

Tile::Tile(int tileGridW,int tileGridH,int tileSize):CSprite(tileGridW,tileGridH,tileSize)
{
    this->indiceTile=0;
    //ctor
}

Tile::~Tile()
{
    int x=0;
    x++;
    //dtor
}
