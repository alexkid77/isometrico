#include <CPlayer.h>

CPlayer::CPlayer(int tileGridW,int tileGridH,int tileSize,Vec3D boxSize):CSprite(tileGridW,tileGridH,tileSize,boxSize)
{
    //ctor
    this->Tipo=PLAYER;
}

CPlayer::~CPlayer()
{
    //dtor
}
void CPlayer::onCollision(CEntity *ent)
{


}
