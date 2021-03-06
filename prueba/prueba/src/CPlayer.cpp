#include <CPlayer.h>

CPlayer::CPlayer(int tileGridW,int tileGridH,int tileSize):CSprite(tileGridW,tileGridH,tileSize)
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
