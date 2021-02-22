#ifndef CENGINE_H
#define CENGINE_H
#include "structures.h"
#include "cVideo.h"
#include <allegro.h>
#include <string>
#include "math.h"
#include "CSprite.h"
#include "utils.h"
class CWorld;
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
    friend class CWorld;
    friend class CSprite;
    CWorld *mapa;
    BITMAP *buffer;


    BITMAP **tiles;
    CSprite *player;
    bool debug;
    int tileH;
    int tileW;
    int tileGridH;
    int tileGridW;
    int tileSize;
    Vec2D orig;

    BITMAP ** ExtraeTiles(BITMAP *tilesRaw,int tileW,int tileH);


    Vec2D setAltura(Vec2D *pos,int tileSizeH,int altura,int tileHeight);


};

#endif // CENGINE_H
