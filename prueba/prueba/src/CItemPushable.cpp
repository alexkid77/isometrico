#include "CItemPushable.h"

CItemPushable::CItemPushable(int tileGridW,int tileGridH,int tileSize,Vec3D BoxSize):CSprite(tileGridW,tileGridH,tileSize,BoxSize)
{
    //ctor
    this->acel=Vec3Df(0,0,0);
    time=0;
}

CItemPushable::~CItemPushable()
{
    //dtor
}
void CItemPushable::Update(double deltaTime)
{
    if(abs(time-deltaTime)>20)
    {
        float decay=0.02;
        time=deltaTime;
        if( this->acel.x>0)
        {
            this->acel.x=  this->acel.x-this->acel.x*(decay);
            this->Pos.x+=this->acel.x;
        }
        if( this->acel.y>0)
        {
            this->acel.y=this->acel.y-this->acel.y*(decay);
            this->Pos.y+=this->acel.y;
        }
    }
}
void CItemPushable::onCollision(CEntity *ent)
{
  this->PosAnt=this->Pos;
    switch(ent->Tipo)
    {
    case PLAYER:
        if(vColisiones.size()==0)
        {

            int dx= ent->Pos.x-ent->PosAnt.x;
            int dy= ent->Pos.y-ent->PosAnt.y;
            int dz= ent->Pos.z-ent->PosAnt.z;
            this->Pos.x+=dx;
            this->Pos.y+=dy;
            if(this->Pos.x<0)
                this->Pos.x=0;
            if(this->Pos.y<0)
                this->Pos.y=0;

                ent->PosAnt=ent->Pos;
                ent->Pos.x-=dx;
                ent->Pos.y-=dy;
                ent->Pos.z-=dz;
            this->acel.x=dx*20;
            this->acel.y=dy*20;



        }
        else
        {

            ent->Pos=ent->PosAnt;
            //   printf("double colision\n");
        }

        break;
    case TILE:

        // printf("colision tile\n");
        break;
    case SPRITE:
        break;
    }

}
