#ifndef TILE_H
#define TILE_H

#include <CSprite.h>


class CTile : public CSprite
{
public:
    int indiceTile;
    int i;
    int j;

    CTile(int tileGridW,int tileGridH,int tileSize);
    virtual ~CTile();

protected:

private:
};

#endif // TILE_H
