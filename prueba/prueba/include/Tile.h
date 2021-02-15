#ifndef TILE_H
#define TILE_H

#include <Entidad.h>


class Tile : public Entidad
{
    public:
        int indiceTile;
        int i;
        int j;
        Tile(int tileGridW,int tileGridH);
        virtual ~Tile();

    protected:

    private:
};

#endif // TILE_H
