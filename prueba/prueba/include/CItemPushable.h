#ifndef CITEMPUSHABLE_H
#define CITEMPUSHABLE_H

#include <CSprite.h>


class CItemPushable : public CSprite
{
public:
    CItemPushable(int tileGridW,int tileGridH,int tileSize,Vec3D BoxSize);
    virtual ~CItemPushable();
    void onCollision(CEntity *ent);
    void Update(double deltaTime);
protected:

private:
    double time;
    Vec3Df acel;
    float decay;
};

#endif // CITEMPUSHABLE_H
