#ifndef RENDER_H
#define RENDER_H

#include <switch/runtime/devices/console.h>  // For gfxInitDefault and gfxExit

void renderMenu();
void loadGameList();
void drawText(int x, int y, const char* text);

#endif // RENDER_H