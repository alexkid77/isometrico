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

    switch(ent->Tipo)
    {
    case PLAYER:
        if(vColisiones.size()==0)
        {

            this->PosAnt=this->Pos;
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
            /*if(dx==0 && dy==0 && ent->Pos.z<=(this->Pos.z+this->Size.z))
            {
                ent->Pos.z=this->Pos.z+this->Size.z;
            }*/
        }
        else
        {
            this->Pos= this->PosAnt;
            ent->Pos=ent->PosAnt;
            printf("double colision\n");
        }

        break;
    case TILE:
        this->Pos= this->PosAnt;
        printf("colision tile\n");
        break;
    case SPRITE:
        break;
    }

}

bool CSprite::hasCollision(CEntity *ent)
{
    int temp=0;

    if(this->Pos.x<(ent->Pos.x+ent->Size.x+temp) &&
            (this->Pos.x+this->Size.x+temp)>(ent->Pos.x) &&
            this->Pos.y<(ent->Pos.y+ent->Size.y+temp) &&
            (this->Pos.y+this->Size.y+temp)>(ent->Pos.y) && (this->Pos.z+this->Size.z+temp)>ent->Pos.z)
        return true;
    else
        return false;
}

