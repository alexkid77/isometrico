#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <chrono>
struct Vec3D
{
    int x;
    int y;
    int z;
    Vec3D()
    {
        this->x=0;
        this->y=0;
        this->z=0;
    }
    Vec3D(int x,int y,int z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
    }
    const bool operator==(const Vec3D &vec) const
    {
        return ((this->x == vec.x) && (this->y == vec.y) && this->z==vec.z);
    }

    const bool operator!=(const Vec3D &vec) const
    {
        return !(*this == vec);
    }


};

struct Vec3Df
{
    float x;
    float y;
    float z;
    Vec3Df()
    {
        this->x=0;
        this->y=0;
        this->z=0;
    }
    Vec3Df(int x,int y,int z)
    {
        this->x=x;
        this->y=y;
        this->z=z;
    }
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

struct Rect
{
    Rect()
    {

    }
    Rect(int x,int y,int w,int h)
    {
        this->orig.x=x;
        this->orig.y=y;

        this->sizes.x=w;
        this->sizes.y=h;
    }
    Vec2D orig;
    Vec2D sizes;
};

struct sRGB
{
    int r,g,b;
    sRGB(int r,int g,int b)
    {
        this->r=r;
        this->g=g;
        this->b=b;
    }
};

enum TiposSprite {SPRITE,TILE,PLAYER};






#endif // STRUCTURES_H_INCLUDED
