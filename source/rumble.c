#include <stdbool.h>
#include "rumble.h"

int rumbleTimer = 0;
bool rumbleActive = false;
bool rumbleTimerActive = false;

void rumbleInit()
{
    GPIO_PORT_DIRECTION = (1 << 3);
    GPIO_PORT_CONTROL = 1;
}

bool rumbleIsActive()
{
    return rumbleActive;
}

void rumbleStart()
{
    GPIO_PORT_DATA |= (1 << 3);
    rumbleActive = true;
}

void rumbleStop()
{
    GPIO_PORT_DATA &= ~(1 << 3);
    rumbleActive = false;
    rumbleTimerActive = false;
    rumbleTimer = 0;
}

void rumbleToggle()
{
    if(rumbleIsActive())
    {
        rumbleStop();
    }
    else
    {
        rumbleStart();
    }
}

void rumbleSetTimer(int frames)
{
    rumbleStart();
    rumbleTimer = frames;
    rumbleTimerActive = true;
}

// Should be called every frame
void rumbleUpdateTimer()
{
    if(rumbleTimerActive)
    {
        if(rumbleTimer > 0)
        {
            rumbleTimer--;
        }
        else
        {
            rumbleStop();
        }
    }
}
