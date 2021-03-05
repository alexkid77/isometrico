

#ifndef CMAP_H
#define CMAP_H

#include "comun.h"
#include "cEngine.h"
#include "CTile.h"
#include "CTileMap.h"
#include <vector>
using namespace std;
class CWorld
{
public:
    CWorld(cEngine* engine);
    virtual ~CWorld();
    void Update();
    void Render();
    CTileMap * LoadTmx(string file);
protected:

private:
    CSprite *objeto;

    int tileGridH;
    int tileGridW;
    Vec2D orig;

    cEngine* engine;
    CTileMap *tilemap;

    //todos los objetos del mundo
    vector<CSprite*> vSprites;

    //todos los objeto que se ven
    vector<CSprite*> vVisible;

    //todos los objeto dinamicos
    vector<CSprite*> vDinamicos;

    void VisitNode(CSprite *ent,int *sortDepth);
    void InitSprites();
    void ProcesaDepthSprites();
    void PreSortByXY(vector<CSprite*> &v);
    ViewPort  GetViewPort(int width,int height);
    void OrdenaTopologicamente();
    void OrdenaTopologicamente2();

};

#endif // CMAP_H
