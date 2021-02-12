#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "structures.h"

class Entidad
{
    public:
        Entidad();
        virtual ~Entidad();
        Vec2D Pos;
        Vec2D PosAnt;
    protected:

    private:
};

#endif // ENTIDAD_H
