#ifndef IVIDEOSYSTEM_H
#define IVIDEOSYSTEM_H

#include <comun.h>
class IVideoSystem
{
public:

    IVideoSystem();


    virtual int getWidth()=0;
    virtual int getHeight()=0;
    virtual void Blit(int indexTile,Rect Orig,Rect Dest)=0;
    virtual void ToScreen()=0;
    virtual void ClearToColor(sRGB color)=0;
    virtual void TextOut(int x,int y,char *text,sRGB color)=0;
    virtual void TextOutCenter(int x,int y,char *text,sRGB color)=0;
    virtual ~IVideoSystem();
protected:

private:
};

#endif // IVIDEOSYSTEM_H
