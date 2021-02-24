#include "CLayer.h"

CLayer::CLayer()
{
    //ctor
}

CLayer::~CLayer()
{
    //dtor
}
CTile *CLayer::GetTile(int x,int y)
{
    CLayer *capa=this;
    return capa->tiles[x+y*capa->width];
}
