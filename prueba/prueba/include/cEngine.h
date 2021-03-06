#ifndef CENGINE_H
#define CENGINE_H
#include "comun.h"
#include "cVideo.h"
#include <allegro.h>
#include <string>
#include <math.h>
#include <CSprite.h>
#include <CPlayer.h>
#include <utils.h>

class CWorld;
using namespace std;

class CEngine
{
public:
    CEngine();
    void Update();
    void Render();
    virtual ~CEngine();
    void setDebug(bool n)
    {
        this->debug=n;
    }
    static void onPlayerCollision(CEntity *ent);
    int fps;
protected:

private:
    friend class CWorld;
    friend class CSprite;
    CWorld *mapa;
    BITMAP *buffer;


    BITMAP **tiles;
    CPlayer *player;
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
