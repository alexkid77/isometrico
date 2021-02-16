#include "Entidad.h"
Entidad::Entidad()
{
    //ctor
}
Entidad::Entidad(int tileGridW,int tileGridH)
{
    this->tileGridW=tileGridW;
    this->tileGridH=tileGridH;
    this->Depth=0;
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
    p0.x=(this->Pos.x)/32;
    p0.y=(this->Pos.y)/32;

    Vec2D p1;
    p1.x=p0.x+((this->Pos.x%32)>0?1:0);
    p1.y=p0.y+((this->Pos.y%32)>0?1:0);

    res.push_back(p0);

    if(p1!=p0)
    {
        res.push_back(p1);

        if(p1.x==p1.y)
        {
            Vec2D p2;
            p2.x=p0.x;
            p2.y=p1.y;

            Vec2D p3;
            p3.x=p1.x;
            p3.y=p0.y;
            res.push_back(p2);
            res.push_back(p3);
        }

    }
    return res;
}
bool Entidad::OcupaTile(int x,int y)
{
   vector<Vec2D> v= this->getTilesOcupados();
   Vec2D Comp;
   Comp.x=x;
   Comp.y=y;
   for(int i=0;i<v.size();i++)
    if(Comp==v[i])
        return true;

   return false;
}
Vec2D Entidad::getPosProj()
{
    Vec2D playerProj;
    playerProj.x=this->Pos.x;
    playerProj.y=this->Pos.y;
    playerProj=utils::twoDToIso(&playerProj);
    return playerProj;
}

bool Entidad::SolapaEntidad(Entidad *b)
{
    int offset=32;
    int xa=this->Pos.x;
    int ya=this->Pos.y;
    int xb=b->Pos.x;
    int yb=b->Pos.y;
    if((b->Pos.x<(this->Pos.x+32)) && (b->Pos.y<(this->Pos.y+32)))
        return true;
    return false;
}
