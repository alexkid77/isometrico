#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED


typedef struct Vec2D
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

#endif // STRUCTURES_H_INCLUDED
