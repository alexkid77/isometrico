#ifndef CENGINE_H
#define CENGINE_H
#include "structures.h"
#include "cVideo.h"
#include <allegro.h>
#include <string>
#include "math.h"
using namespace std;
class cEngine
{
public:
    cEngine();
    void Update();
    void Render();
    virtual ~cEngine();

protected:

private:
    BITMAP *buffer;
    int tileH;
    int tileW;
    int tileGridH;
    int tileGridW;
    Vec2D orig;
    BITMAP **tiles;
   Entidad player;
    BITMAP ** ExtraeTiles(BITMAP *tilesRaw,int tileW,int tileH);
    Vec2D isoTo2D(Vec2D *vec);
    Vec2D twoDToIso(Vec2D *vec);
    Vec2D setAltura(Vec2D *pos,int tileSizeH,int altura,int tileHeight);

    Vec2D GetTileWithPos(int x,int y);
};

#endif // CENGINE_H
