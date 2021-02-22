

#ifndef CMAP_H
#define CMAP_H

#include "structures.h"
#include "cEngine.h"
#include "Tile.h"
#include <vector>
using namespace std;
class CWorld
{
public:
    CWorld(cEngine* engine);
    virtual ~CWorld();
    void Update();
    void Render();

protected:

private:
    int tileGridH;
    int tileGridW;
    Vec2D orig;

    cEngine* engine;


    vector<CSprite*> vSprites;
    void VisitNode(CSprite *ent,int *sortDepth);
    void InitSprites();
    vector<CSprite*> ProcesaDepthSprites();

    unsigned char mapa[12][12]=
    {
        {3,1,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,1,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,1,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3},
        {3,1,3,3,3,3,3,3,3,3,1,3},
        {3,3,3,3,3,3,3,3,3,3,3,3}

    };
};

#endif // CMAP_H
