#ifndef CENGINE_H
#define CENGINE_H
#include "comun.h"
#include "cVideo.h"
#include "IVideoSystem.h"
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
    CEngine(IVideoSystem *vidSystem);
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
    IVideoSystem *vidSys;
    friend class CWorld;
    friend class CSprite;
    CWorld *mapa;

    CPlayer *player;
    bool debug;
    int tileH;
    int tileW;
    int tileGridH;
    int tileGridW;
    int tileSize;
    Vec2D orig;







};

#endif // CENGINE_H
