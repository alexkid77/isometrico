#include "Entidad.h"
Entidad::Entidad()
{
    //ctor
}
Entidad::Entidad(int tileGridW,int tileGridH)
{
    this->tileGridW=tileGridW;
    this->tileGridH=tileGridH;
    //ctor
}

Entidad::~Entidad()
{
    //dtor
}
vector<Vec2D> Entidad::getTilesOcupados()
{

    vector<Vec2D> res;
    Vec2D p0;
    p0.x=this->Pos.x/32;
    p0.y=this->Pos.y/32;

    Vec2D p1;
    p1.x=p0.x+this->Pos.x%32;
    p1.y=p0.x+this->Pos.y%32;

    if(p1.x==p1.y)
    {
     Vec2D p2;
     p2.x=p0.x;
     p2.y=p1.y;

      Vec2D p3;
     p3.x=p1.x;
     p3.y=p0.y;
    }

  //  Vec2D v3=utils::GetTileWithPos(this->tileGridW,this->tileGridH,playerProj.x+32,playerProj.y+64);
   // Vec2D v4=utils::GetTileWithPos(this->tileGridW,this->tileGridH,playerProj.x+32,playerProj.y+32);
    /*  putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+64,playerProj.y+this->engine->orig.y+32+16,makecol(255,255,255));
     putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x,playerProj.y+this->engine->orig.y+32+16,makecol(0,255,0));
     putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+64,makecol(255,0,0));
    putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+32,makecol(255,0,0));*/

    return res;

}

Vec2D Entidad::getPosProj()
{
    Vec2D playerProj;
    playerProj.x=this->Pos.x;
    playerProj.y=this->Pos.y;
    playerProj=utils::twoDToIso(&playerProj);
    return playerProj;
}
