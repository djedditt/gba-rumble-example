#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>

#include "rumble.h"

void handleInput()
{
    scanKeys();

    int keysPressed = keysDown();
    int keysDepressed = keysUp();

    switch(keysPressed)
    {
        case KEY_A:
            rumbleSetTimer(15);
            break;

        case KEY_B:
            rumbleStart();
            break;

        case KEY_SELECT:
            rumbleToggle();
            break;
    }

    if(keysDepressed == KEY_B)
    {
        rumbleStop();
    }
}

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------


    // the vblank interrupt must be enabled for VBlankIntrWait() to work
    // since the default dispatcher handles the bios flags no vblank handler
    // is required
    irqInit();
    irqEnable(IRQ_VBLANK);

    consoleInit(0, 4, 0, NULL, 0, 0);
    BG_COLORS[1]=RGB5(31,31,31);
    SetMode(MODE_0 | BG0_ON);

    rumbleInit();

    // ansi escape sequence to set print co-ordinates
    // /x1b[line;columnH
    iprintf("\x1b[1;0H   GBA rumble example v0.1    \n");
    iprintf("\x1b[2;0H     github.com/djedditt      \n");
    iprintf("\x1b[3;0H ---------------------------- \n");
    iprintf("\x1b[4;0H                              \n");
    iprintf("\x1b[5;0H Controls:                    \n");
    iprintf("\x1b[6;0H                              \n");
    iprintf("\x1b[7;0H   A    - Rumble 0.25 seconds \n");
    iprintf("\x1b[8;0H   B    - Hold to rumble      \n");
    iprintf("\x1b[9;0H SELECT - Toggle rumble       \n");

    while (1)
    {
        VBlankIntrWait();
        handleInput();
        rumble();

        if(rumbleIsActive())
        {
            iprintf("\x1b[14;0H        RUMBLE ACTIVE!        \n");
        }
        else
        {
            iprintf("\x1b[14;0H                              \n");
        }
    }
}
