#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "comun.h"
#include <vector>
#include <utils.h>
#include <algorithm>
#include <CEntity.h>
using namespace std;
class CSprite:public CEntity
{
public:

    Vec2D Pos;
    Vec2D PosAnt;
    Vec2D PosProj;
    int Depth;
    vector<CSprite*> entidadesDebajo;
    bool visitado;

    int i,j;

    vector<Vec2D> getTilesOcupados();
    Vec2D getPosProj();
    bool OcupaTile(int x,int y);

    bool SolapaEntidad(CSprite *b);
    CSprite();
    CSprite(int tileGridW,int tileGridH,int tileSize);

    void ClearDepth();

    virtual ~CSprite();

    int getDepth()
    {
        return this->Depth;
    }

protected:
    int tileSize;
private:
    int tileGridW,tileGridH;

};

#endif // ENTIDAD_H
