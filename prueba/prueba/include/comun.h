#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED


struct Vec2D
{
    int x;
    int y;

    const bool operator==(const Vec2D &vec) const
    {
        return ((this->x == vec.x) && (this->y == vec.y));
    }

    const bool operator!=(const Vec2D &vec) const
    {
        return !(*this == vec);
    }
};

struct ViewPort
{
    Vec2D p1;
    Vec2D p2;

};
enum TiposSprite {SPRITE,TILE};
#endif // STRUCTURES_H_INCLUDED
