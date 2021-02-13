

#ifndef CMAP_H
#define CMAP_H

#include "structures.h"
#include "cEngine.h"
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

};

#endif // CMAP_H
