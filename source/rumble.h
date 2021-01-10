#ifndef RUMBLE_H_
#define RUMBLE_H_

#define GPIO_PORT_DATA      (*(volatile unsigned short*)0x80000C4)
#define GPIO_PORT_DIRECTION (*(volatile unsigned short*)0x80000C6)
#define GPIO_PORT_CONTROL   (*(volatile unsigned short*)0x80000C8)

int rumbleTimer;
bool rumbleActive;
bool rumbleTimerActive;

void rumbleInit();
bool rumbleIsActive();
void rumbleStart();
void rumbleStop();
void rumbleToggle();
void rumbleSetTimer(int frames);
void rumble();

#endif