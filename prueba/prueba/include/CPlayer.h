#ifndef CPLAYER_H
#define CPLAYER_H

#include <CSprite.h>


class CPlayer : public CSprite
{
public:
    enum State {IDLE,JUMP_UP,JUMP_DOWN};

    CPlayer();
    CPlayer(int tileGridW,int tileGridH,int tileSize,Vec3D boxSize);
    virtual ~CPlayer();
    virtual void onCollision(CEntity *ent);
    void Update(double deltaTime);
    void Jump();
    State estado;
protected:

private:
    Vec3Df acel;

};

#endif // CPLAYER_H
