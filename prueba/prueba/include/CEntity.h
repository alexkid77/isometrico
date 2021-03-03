#ifndef CENTITY_H
#define CENTITY_H

#include <comun.h>
class CEntity
{
public:

    int id;
    TiposSprite Tipo;
    CEntity();
    virtual ~CEntity();
    void(*onCollision)(CEntity *ent);
protected:

private:
};

#endif // CENTITY_H
