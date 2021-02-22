#ifndef TILE_H
#define TILE_H

#include <CSprite.h>


class Tile : public CSprite
{
public:
    int indiceTile;
    int i;
    int j;

    Tile(int tileGridW,int tileGridH,int tileSize);
    virtual ~Tile();

protected:

private:
};

#endif // TILE_H
