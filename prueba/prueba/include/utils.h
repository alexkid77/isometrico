#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <comun.h>
#include <CSprite.h>
#include <chrono>
#define REJILLA 32

class utils
{
public:

    /** \brief convierte coordenadas isometricas a coordenadas de pantalla
     *
     * \param vec Vec2D*
     * \return Vec2D
     *
     */
    static Vec2D IsoTo2D(Vec2D *vec)
    {

        Vec2D val;
        val.x=vec->x-vec->y;
        val.y=(vec->x+vec->y)/2;
        return val;

    }

    /** \brief convierte coordenadas isometricas a coordenadas de pantalla
     *
     * \param vec Vec3D*
     * \return Vec2D
     *
     */
    static Vec2D IsoTo2D(Vec3D *vec)
    {

        Vec2D val;
        val.x=vec->x-vec->y;
        val.y=(vec->x+vec->y-vec->z)/2;
        return val;
    }

    /** \brief convierte coordenadas de de panatalla a isometricas
     *
     * \param vec Vec2D*
     * \return Vec2D
     *
     */
    static Vec2D twoDToIso(Vec2D *vec)
    {
        Vec2D val;
        val.x = (2 * vec->y + vec->x) / 2;
        val.y = (2 * vec->y - vec->x) / 2;
        return val;
    }


    /** \brief obtiene el tile desde una coordenada projectada
     *
     * \param tileGridW int
     * \param tileGridH int
     * \param x int
     * \param y int
     * \return Vec2D
     *
     */
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

//snippets
/* you must always release bitmaps before calling any input functions */
/*    Vec2D mousePos;
    mousePos.x=mouse_x-orig.x-this->tileGridW/2;
    mousePos.y=mouse_y-orig.y-this->tileGridH;*/
//tres posiciones


/*   putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+64,playerProj.y+this->engine->orig.y+32+16,makecol(255,255,255));
   putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x,playerProj.y+this->engine->orig.y+32+16,makecol(0,255,0));
   putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+64,makecol(255,0,0));
   putpixel(this->engine->buffer,playerProj.x+this->engine->orig.x+32,playerProj.y+this->engine->orig.y+32,makecol(255,0,0));*/


//int  isoX = ( ((ScreenY + scrollY) / tileHeight) + ((screenX + scrollX) - (isoMapMaxY * tileWidth/2)) / tileWidth )
//int isoY = ( ((screenY + scrollY) / tileHeight) - ((screenX + scrollX) - (isoMapMaxY * tileWidth/2)) / tileWidth )
#endif // UTILS_H
