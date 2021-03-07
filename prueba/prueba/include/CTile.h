#ifndef TILE_H
#define TILE_H

#include <CSprite.h>


class CTile : public CSprite
{
public:
    int indiceTile;
    int i;
    int j;

    CTile(int tileGridW,int tileGridH,int tileSize,Vec3D boxSize);

    virtual ~CTile();

protected:
    virtual void onCollision(CEntity *ent);
private:
};

#endif // TILE_H
