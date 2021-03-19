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

    Vec3D operator+(const Vec3D op1)
    {
        Vec3D temp= Vec3D(this->x,this->y,this->z);
        temp.x+=op1.x;
        temp.y+=op1.y;
        temp.z+=op1.z;
        return temp;
    }

    Vec3D operator-(const Vec3D op1)
    {
        Vec3D temp= Vec3D(this->x,this->y,this->z);
        temp.x-=op1.x;
        temp.y-=op1.y;
        temp.z-=op1.z;
        return temp;
    }

    Vec3D operator*(const int val)
    {
        Vec3D temp= Vec3D(this->x,this->y,this->z);
        temp.x*=val;
        temp.y*=val;
        temp.z*=val;
        return temp;
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
    /*  Vec3Df(Vec3D &v)
      {
          this->x=v.x;
          this->y=v.y;
          this->z=v.z;
      }*/
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

    Vec3Df operator+(const Vec3Df op1)
    {
        Vec3Df temp= Vec3Df(this->x,this->y,this->z);
        temp.x+=op1.x;
        temp.y+=op1.y;
        temp.z+=op1.z;
        return temp;
    }

    Vec3Df operator-(const Vec3Df op1)
    {
        Vec3Df temp= Vec3Df(this->x,this->y,this->z);
        temp.x-=op1.x;
        temp.y-=op1.y;
        temp.z-=op1.z;
        return temp;
    }


    /* Vec3Df  operator*(int s)
     {
         return Vec3Df(x*s, y*s, z*s);
     }*/

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
