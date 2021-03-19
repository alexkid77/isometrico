#include <CPlayer.h>

CPlayer::CPlayer(int tileGridW,int tileGridH,int tileSize,Vec3D boxSize):CSprite(tileGridW,tileGridH,tileSize,boxSize)
{
    //ctor
    this->estado=IDLE;
    this->Tipo=PLAYER;
    this->acel=Vec3Df(0,0,0);
}
void CPlayer::Update(double deta)
{
    float decay=0.01f;
    this->PosAnt=this->Pos;
    switch(this->estado)
    {
    case JUMP_UP:

        this->Pos.z=+this->Pos.z+this->acel.z*decay;
        if(this->Pos.z>=this->acel.z)
            this->estado=JUMP_DOWN;
    break;
    case JUMP_DOWN:
     //  this->Pos.z--;
        if(this->Pos.z<=0){
            this->estado=IDLE;
            this->Pos.z=0;
        }
        break;
    case IDLE:

        break;
    }
}
CPlayer::~CPlayer()
{
    //dtor
}
void CPlayer::onCollision(CEntity *ent)
{
  this->estado=IDLE;
}
void CPlayer::Jump()
{
    if(this->estado!=JUMP_UP ){
    this->estado=JUMP_UP;
    this->acel.z=70*4;
    }
}
