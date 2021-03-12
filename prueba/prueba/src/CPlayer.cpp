#include <CPlayer.h>

CPlayer::CPlayer(int tileGridW,int tileGridH,int tileSize,Vec3D boxSize):CSprite(tileGridW,tileGridH,tileSize,boxSize)
{
    //ctor
    this->Tipo=PLAYER;
}
void CPlayer::Update(double deta)
{
    this->PosAnt=this->Pos;
}
CPlayer::~CPlayer()
{
    //dtor
}
void CPlayer::onCollision(CEntity *ent)
{


}
