#include <allegro.h>
#include "cEngine.h"


int main(void)
{
    /* you should always do this at the start of Allegro programs */
    if (allegro_init() != 0)
        return 1;
    install_timer();
    /* set up the keyboard handler */
    install_keyboard();
    install_mouse();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    set_color_depth(32);
    /* set a graphics mode sized 320x200 */
    set_gfx_mode(GFX_SAFE, 1024, 780,0, 0);
    cEngine *engine=new cEngine();
    while (!key[KEY_ESC])
    {


        engine->Update();
        engine->Render();
        show_mouse(screen);


    }


    /* wait for a keypress */


    return 0;
}

END_OF_MAIN();
