#ifndef CENTITY_H
#define CENTITY_H

#include <comun.h>
class CEntity
{
public:

    int id;
    TiposSprite Tipo;
    Vec2D Pos;
    Vec2D PosAnt;
    Vec2D PosProj;
    CEntity();
    virtual ~CEntity();
    virtual void onCollision(CEntity *ent)=0;
protected:

private:
};

#endif // CENTITY_H
