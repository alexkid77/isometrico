#include <CSprite.h>
#include <stdio.h>
CSprite::CSprite()
{
    //ctor
}
CSprite::CSprite(int tileGridW,int tileGridH,int tileSize,Vec3D BoxSize)
{
    this->tileGridW=tileGridW;
    this->tileGridH=tileGridH;
    this->Depth=0;
    this->tileSize=tileSize;
    this->entidadesDebajo=vector<CSprite*>(128);
    this->Tipo=SPRITE;
    this->Size=BoxSize;
    //ctor
}

CSprite::~CSprite()
{
    //dtor
}
vector<Vec2D> CSprite::getTilesOcupados()
{

    vector<Vec2D> vec;
    Vec2D p0,p1,p2,p3;
    int tileSizeAnt=(this->tileSize-1);
    p0.x=(this->Pos.x)/this->tileSize;
    p0.y=(this->Pos.y)/this->tileSize;

    p1.x=(this->Pos.x+  tileSizeAnt)/this->tileSize;
    p1.y=(this->Pos.y)/this->tileSize;

    p2.x=(this->Pos.x)/this->tileSize;
    p2.y=(this->Pos.y+tileSizeAnt)/this->tileSize;

    p3.x=(this->Pos.x+tileSizeAnt)/this->tileSize;
    p3.y=(this->Pos.y+tileSizeAnt)/this->tileSize;
    vec.push_back(p0);
    vec.push_back(p1);
    vec.push_back(p2);
    vec.push_back(p3);

    vec.erase( unique( vec.begin(), vec.end() ), vec.end() );

    return vec;
}
bool CSprite::OcupaTile(int x,int y)
{
    vector<Vec2D> v= this->getTilesOcupados();
    Vec2D Comp;
    Comp.x=x;
    Comp.y=y;
    for(unsigned int i=0; i<v.size(); i++)
        if(Comp==v[i])
            return true;

    return false;
}
Vec2D CSprite::getPosProj()
{
    Vec3D playerProj;
    playerProj.x=this->Pos.x;
    playerProj.y=this->Pos.y;
    playerProj.z=this->Pos.z;
    Vec2D res=utils::IsoTo2D(&playerProj);
    return res;
}

bool CSprite::SolapaEntidad(CSprite *b)
{
    if((b->Pos.x<(this->Pos.x+this->Size.x)) && (b->Pos.y<(this->Pos.y+this->Size.y)) && (b->Pos.z <(this->Pos.z+this->Size.z)))
        return true;
    return false;
}

void CSprite::ClearDepth()
{
    this->Depth=0;
    this->entidadesDebajo.clear();
    this->visitado=false;

}

void CSprite::onCollision(CEntity *ent)
{



}

/** \brief indica si dos sprites colisionan comparando sus boundingbox
 *
 * \param ent CEntity*
 * \return bool
 *
 */
bool CSprite::hasCollision(CEntity *ent)
{


    if(this->Pos.x<(ent->Pos.x+ent->Size.x) &&
            (this->Pos.x+this->Size.x)>(ent->Pos.x) &&
            this->Pos.y<(ent->Pos.y+ent->Size.y) &&
            (this->Pos.y+this->Size.y)>(ent->Pos.y) && (this->Pos.z+this->Size.z)>ent->Pos.z)
        return true;
    else
        return false;
}
Vec3D CSprite::getIntersection(CEntity *ent)
{
    Vec3D dir=Vec3D(0,0,0);
    dir.x=ent->Pos.x-ent->PosAnt.x;
    dir.y=ent->Pos.y-ent->PosAnt.y;
    dir.z=ent->Pos.z-ent->PosAnt.z;

    return dir;
}
void  CSprite::Update(double deltaTime)
{

}
