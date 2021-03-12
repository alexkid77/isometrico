#ifndef CPLAYER_H
#define CPLAYER_H

#include <CSprite.h>


class CPlayer : public CSprite
{
public:
    CPlayer();
    CPlayer(int tileGridW,int tileGridH,int tileSize,Vec3D boxSize);
    virtual ~CPlayer();
    virtual void onCollision(CEntity *ent);
    void Update(double deltaTime);
protected:

private:
};

#endif // CPLAYER_H
