#include <allegro.h>
#include "cEngine.h"

BITMAP **ExtraeTiles(BITMAP *tileRaw,int tileW,int tileH);
Vec2D isoTo2D(Vec2D *vec);
Vec2D twoDToIso(Vec2D *vec);
Vec2D setAltura(Vec2D *pos,int tileSizeH,int altura,int tileHeight);
int main(void)
{
    /* you should always do this at the start of Allegro programs */
    if (allegro_init() != 0)
        return 1;
    install_timer();
    /* set up the keyboard handler */
    install_keyboard();
    set_color_depth(24);
    /* set a graphics mode sized 320x200 */
    set_gfx_mode(GFX_SAFE, 640, 480,0, 0);
  cEngine *engine=new cEngine();
    while (!keypressed())
    {

        engine->Update();
        engine->Render();
    }


    /* wait for a keypress */


    return 0;
}

END_OF_MAIN();
