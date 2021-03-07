#include <CTile.h>

CTile::CTile(int tileGridW,int tileGridH,int tileSize,Vec3D boxSize):CSprite(tileGridW,tileGridH,tileSize,boxSize)
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
