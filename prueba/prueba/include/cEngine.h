#ifndef CENGINE_H
#define CENGINE_H
#include "comun.h"
#include "cVideo.h"
#include <IVideoSystem.h>
#include <ITimer.h>
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
    CEngine(IVideoSystem *vidSystem,ITimer *timer);
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
    ITimer *timer;
    friend class CWorld;
    friend class CSprite;
    CWorld *mapa;

    CPlayer *player;
    bool debug;
    int tileH;/**< tamaño del bitmap Alto */
    int tileW;/**< tamaño del bitmap Ancho */
    int tileGridH;/**< tamaño grid alto sera normalmente 32 */
    int tileGridW;/**< tamaño grid ancho sera normalmente 32 */
    int tileSize;
    Vec2D orig;/**< origen de coordenadas*/

    int fpsCount;
    double tFpsAnt;





};

#endif // CENGINE_H
