

#ifndef CMAP_H
#define CMAP_H

#include "structures.h"
#include "cEngine.h"
#include "Tile.h"
#include <vector>
using namespace std;
class cMap
{
public:
    cMap(cEngine* engine);
    virtual ~cMap();
    void Update();
    void Render();

protected:

private:
    int tileGridH;
    int tileGridW;
    Vec2D orig;

    cEngine* engine;
    void VisitNode(Entidad *ent,int *sortDepth);
};

#endif // CMAP_H
