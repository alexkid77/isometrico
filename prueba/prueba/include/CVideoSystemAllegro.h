#ifndef CVIDEOSYSTEMALLEGRO_H
#define CVIDEOSYSTEMALLEGRO_H

#include <IVideoSystem.h>

#include <allegro.h>
class CVideoSystemAllegro : public IVideoSystem
{
public:
    CVideoSystemAllegro (int width,int heigth);


    int getWidth();
    int getHeight();
    void Blit(int indexTile,Rect Orig,Rect Dest);
    void TextOut(int x,int y,char *text,int color);
    void LoadTiles(int tileW,int tileH);
     void ToScreen();
    virtual ~CVideoSystemAllegro();

protected:

private:
    int width,height;
    BITMAP *buffer;
      BITMAP **tiles;
};

#endif // CVIDEOSYSTEMALLEGRO_H
