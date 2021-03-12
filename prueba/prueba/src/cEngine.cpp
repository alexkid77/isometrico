#include <CEngine.h>
#include <CWorld.h>
#include "allegro.h"
CEngine::CEngine(IVideoSystem *vidSystem,ITimer *timer)
{

    this->vidSys=vidSystem;
    this->timer=timer;

    this->tileH=80;
    this->tileW=64;
    this->tileSize=32;
    this->tileGridH= this->tileH/2;
    this->tileGridW=this->tileW;
    this->orig.x= this->vidSys->getWidth()/2-tileW/2;
    this->orig.y= this->vidSys->getHeight()/2-tileH/2;


    Vec3D playerBox(32,32,100);
    this->player= new CPlayer(this->tileGridW,this->tileGridH,this->tileSize,playerBox);

    this->player->Pos.x=67;
    this->player->Pos.y=100;
    this->player->Pos.z=70;


    this->mapa=new CWorld(this);

    this->fpsCount=0;
    this->tFpsAnt=this->timer->GetTicks();

}

CEngine::~CEngine()
{
    //dtor
}
void CEngine::onPlayerCollision(CEntity *ent)
{
    int x=0;
    x++;
//   printf("Colision\n");
}
void CEngine::Update()
{


    this->mapa->Update(this->timer->GetTicks());
    //this->player->PosAnt=this->player->Pos;




}

void CEngine::Render()
{
    if(fabs(this->tFpsAnt-this->timer->GetTicks())>1000)
    {
        this->tFpsAnt=this->timer->GetTicks();
        this->fps=this->fpsCount;
        this->fpsCount=0;
    }
    this->mapa->Render();

    this->fpsCount++;



}







