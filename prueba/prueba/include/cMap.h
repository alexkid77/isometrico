

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
    Vec2D GetTileWithPos(int x,int y);
    cEngine* engine;

};

#endif // CMAP_H
