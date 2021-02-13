#ifndef CENGINE_H
#define CENGINE_H
#include "structures.h"
#include "cVideo.h"
#include <allegro.h>
#include <string>
#include "math.h"
#include "Entidad.h"
#include "utils.h"
class cMap;
using namespace std;
class cEngine
{
public:
    cEngine();
    void Update();
    void Render();
    virtual ~cEngine();
    void setDebug(bool n)
    {
        this->debug=n;
    }
protected:

private:
    friend class cMap;
    friend class Entidad;
    cMap *mapa;
    BITMAP *buffer;


    BITMAP **tiles;
    Entidad player;
    bool debug;
    int tileH;
    int tileW;
    int tileGridH;
    int tileGridW;
    Vec2D orig;

    BITMAP ** ExtraeTiles(BITMAP *tilesRaw,int tileW,int tileH);


    Vec2D setAltura(Vec2D *pos,int tileSizeH,int altura,int tileHeight);

    Vec2D GetTileWithPos(int x,int y);
};

#endif // CENGINE_H
