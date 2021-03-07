#ifndef ENTIDAD_H
#define ENTIDAD_H
#include <comun.h>
#include <vector>
#include <utils.h>
#include <algorithm>
#include <CEntity.h>
using namespace std;
class CSprite:public CEntity
{
public:
    //colisiones
    vector<CSprite*> vColisiones;

    //profundida de dibujado
    int Depth;
    vector<CSprite*> entidadesDebajo;
    bool visitado;

    //posicion tile
    // int i,j;

    vector<Vec2D> getTilesOcupados();
    Vec2D getPosProj();
    bool OcupaTile(int x,int y);

    bool SolapaEntidad(CSprite *b);
    CSprite();
    CSprite(int tileGridW,int tileGridH,int tileSize,Vec3D BoxSize);



    virtual ~CSprite();
    virtual void onCollision(CEntity *ent);
    virtual bool hasCollision(CEntity *ent);

    void ClearDepth();
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
