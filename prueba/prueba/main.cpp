#include <allegro.h>
#include "CEngine.h"
#include "CVideoSystemDefault.h"
#include "ITimerWindows.h"


int main(void)
{




    CVideoSystemDefault *aa=new CVideoSystemDefault(800,600);

    /* set up the keyboard handler */
    install_keyboard();
    install_mouse();

    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    aa->LoadTiles(64,128);
    IVideoSystem *vid=static_cast<IVideoSystem *>(aa);
    ITimer *timer=new ITimerWindows();
    CEngine *engine=new CEngine(vid,timer);
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
