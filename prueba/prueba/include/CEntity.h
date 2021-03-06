#ifndef CENTITY_H
#define CENTITY_H

#include <comun.h>
class CEntity
{
public:

    int id;
    TiposSprite Tipo;
    //Posicion del objeto
    Vec3D Pos;
    //Posicion Anterior del objeto
    Vec3D PosAnt;
    //tamaño del bouding box del objeto
    Vec3D Size;

    Vec2D PosProj;
    CEntity();
    virtual ~CEntity();
    virtual void onCollision(CEntity *ent)=0;
protected:

private:
};

#endif // CENTITY_H
