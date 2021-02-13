#ifndef PLAYER_H
#define PLAYER_H

#include <Entidad.h>
#include <utils.h>
#include <vector>

using namespace std;
class Player : public Entidad
{
    public:
        Player();
        virtual ~Player();

    protected:

    private:
        vector<Vec2D> tilesOcupados;
};

#endif // PLAYER_H
