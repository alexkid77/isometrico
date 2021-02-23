#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include "comun.h"
#include "CSprite.h"
#define REJILLA 32
class utils
{
public:
    static Vec2D twoDToIso(Vec2D *vec)
    {

        Vec2D val;
        val.x=vec->x-vec->y;
        val.y=(vec->x+vec->y)/2;
        return val;

        //int  isoX = ( ((ScreenY + scrollY) / tileHeight) + ((screenX + scrollX) - (isoMapMaxY * tileWidth/2)) / tileWidth )
//int isoY = ( ((screenY + scrollY) / tileHeight) - ((screenX + scrollX) - (isoMapMaxY * tileWidth/2)) / tileWidth )
    }

    static Vec2D isoTo2D(Vec2D *vec)
    {
        Vec2D val;
        val.x = (2 * vec->y + vec->x) / 2;
        val.y = (2 * vec->y - vec->x) / 2;
        return val;
    }

    /*obtiene el tile desde una coordenada projectada */
    static Vec2D GetTileWithPos(int tileGridW,int tileGridH,int x,int y)
    {

        Vec2D res;
        int pixel_x=x;
        int pixel_y=y;
        int tile_w=tileGridW;
        int tile_h=tileGridH;
        int tile_x = (pixel_x/(tile_w/2) + pixel_y/(tile_h/2)) / 2;
        int tile_y = (pixel_y/(tile_h/2) - pixel_x/(tile_w/2)) / 2;
        //convert back to integer
        res.x =tile_x;
        res.y =tile_y;
        return res;
    }



};

#endif // UTILS_H
