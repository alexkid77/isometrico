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

    vector<Vec2D> vec;
    Vec2D p0,p1,p2,p3;
    p0.x=(this->Pos.x)/32;
    p0.y=(this->Pos.y)/32;

    p1.x=(this->Pos.x+31)/32;
    p1.y=(this->Pos.y)/32;

    p2.x=(this->Pos.x)/32;
    p2.y=(this->Pos.y+31)/32;

    p3.x=(this->Pos.x+31)/32;
    p3.y=(this->Pos.y+31)/32;
    vec.push_back(p0);
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);

    vec.erase( unique( vec.begin(), vec.end() ), vec.end() );
    int tam=vec.size();
    return vec;
}
bool Entidad::OcupaTile(int x,int y)
{
    vector<Vec2D> v= this->getTilesOcupados();
    Vec2D Comp;
    Comp.x=x;
    Comp.y=y;
    for(int i=0; i<v.size(); i++)
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
