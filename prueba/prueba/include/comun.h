#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
struct Vec3D
{
    int x;
    int y;
    int z;
    const bool operator==(const Vec3D &vec) const
    {
        return ((this->x == vec.x) && (this->y == vec.y) && this->z==vec.z);
    }

    const bool operator!=(const Vec3D &vec) const
    {
        return !(*this == vec);
    }


};

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
    void operator=(const Vec3D &vec)
    {
        this->x=vec.x;
        this->y=vec.y;
    }
};



struct ViewPort
{
    Vec2D p1;
    Vec2D p2;

};
enum TiposSprite {SPRITE,TILE,PLAYER};
#endif // STRUCTURES_H_INCLUDED
