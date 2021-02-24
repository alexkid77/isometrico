

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
    int tileGridH;
    int tileGridW;
    Vec2D orig;

    cEngine* engine;
    CTileMap *tilemap;

    vector<CSprite*> vSprites;
    void VisitNode(CSprite *ent,int *sortDepth);
    void InitSprites();
    vector<CSprite*> ProcesaDepthSprites();


};

#endif // CMAP_H
