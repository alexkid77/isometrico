#include <allegro.h>
#include "CEngine.h"
#include "CVideoSystemDefault.h"
volatile unsigned int ticks=0;
volatile unsigned int fps=0;
void inc_contador_tiempo_juego()
{
    fps=ticks;
    ticks=0;
}
END_OF_FUNCTION(inc_contador_tiempo_juego)

int main(void)
{

    /* you should always do this at the start of Allegro programs */
    if (allegro_init() != 0)
        return 1;




    install_timer();
    /* set up the keyboard handler */
    install_keyboard();
    install_mouse();
    install_int_ex(inc_contador_tiempo_juego,  SECS_TO_TIMER(1));
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    set_color_depth(32);
    /* set a graphics mode sized 320x200 */
    set_gfx_mode(GFX_SAFE, 800, 600,0, 0);
   CVideoSystemDefault *aa=new CVideoSystemDefault(800,600);
      aa->LoadTiles(64,80);
    IVideoSystem *vid=static_cast<IVideoSystem *>(aa);

    CEngine *engine=new CEngine(vid);
    while (!key[KEY_ESC])
    {

        engine->fps=fps;
        engine->Update();
        engine->Render();
        show_mouse(screen);
        ticks++;

    }


    /* wait for a keypress */


    return 0;
}

END_OF_MAIN();
