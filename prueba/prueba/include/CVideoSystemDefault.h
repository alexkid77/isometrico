#ifndef CVIDEOSYSTEMALLEGRO_H
#define CVIDEOSYSTEMALLEGRO_H
#include <allegro.h>
#include <IVideoSystem.h>
#include <comun.h>

/** \brief Implementacion del sistema de video para allegro 4
 */
class CVideoSystemDefault:public IVideoSystem
{
public:

    CVideoSystemDefault (int width,int heigth);



    inline void Blit(int indexTile,Rect Orig,Rect Dest) ;
    void TextOut(int x,int y,char *text,sRGB color);
    void TextOutCenter(int x,int y,char *text,sRGB color);
    void LoadTiles(int tileW,int tileH);
    void ToScreen();
    void ClearToColor(sRGB color);
    int getWidth();
    int getHeight();
    virtual ~CVideoSystemDefault();

protected:

private:
    int width,height;
    BITMAP *buffer;
    BITMAP **tiles;
};

#endif // CVIDEOSYSTEMALLEGRO_H
