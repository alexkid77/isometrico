

#ifndef CMAP_H
#define CMAP_H

#include <comun.h>
#include <CEngine.h>
#include <CTile.h>
#include <CTileMap.h>
#include <vector>
using namespace std;
class CWorld
{
public:
    CWorld(CEngine* engine);
    virtual ~CWorld();
    void Update(double deltaTime);
    void Render();
    CTileMap * LoadTmx(string file);
protected:

private:
    CSprite *objeto;

    int tileGridH;
    int tileGridW;
    Vec2D orig;

    CEngine* engine;
    CTileMap *tilemap;

    //todos los objetos del mundo
    vector<CSprite*> childs;

    //todos los objeto que se ven
    vector<CSprite*> vVisible;

    //todos los objeto dinamicos
    vector<CSprite*> vDinamicos;

    void VisitNode(CSprite *ent,int *sortDepth);
    void InitSprites();
    void ProcesaDepthSprites();
    void ProcesaCollisiones();
    void PreSortByXY(vector<CSprite*> &v);
    ViewPort  GetViewPort(int width,int height);
    void OrdenaTopologicamente();
    void OrdenaTopologicamente2();

};

#endif // CMAP_H
