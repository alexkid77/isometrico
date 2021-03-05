#ifndef CPLAYER_H
#define CPLAYER_H

#include <CSprite.h>


class CPlayer : public CSprite
{
public:
    CPlayer();
    CPlayer(int tileGridW,int tileGridH,int tileSize);
    virtual ~CPlayer();
    virtual void onCollision(CEntity *ent);
protected:

private:
};

#endif // CPLAYER_H
