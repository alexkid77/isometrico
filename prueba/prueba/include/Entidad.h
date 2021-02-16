#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "structures.h"
#include <vector>
#include <utils.h>
using namespace std;
class Entidad
{
public:
    Entidad();
    Entidad(int tileGridW,int tileGridH);
    virtual ~Entidad();
    Vec2D Pos;

    Vec2D PosProj;
    int Depth;
    vector<Vec2D> getTilesOcupados();
    Vec2D getPosProj();
    bool OcupaTile(int x,int y);

    bool SolapaEntidad(Entidad *b);
    vector<Entidad*> entidadesDebajo;
    bool visitado;
    int id;
    int getDepth()
    {
        return this->Depth;
    }
protected:

private:
    int tileGridW,tileGridH;

};

#endif // ENTIDAD_H
