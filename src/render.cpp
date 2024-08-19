#include <switch.h>
#include <dirent.h>
#include <vector>
#include <string>
#include "render.h"
#include "input.h"

extern int selectedOption;
std::vector<std::string> gameList;

void loadGameList() {
    DIR* dir;
    struct dirent* ent;
    gameList.clear();

    if ((dir = opendir("/3DS")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string fileName(ent->d_name);
            if (fileName.find(".3ds") != std::string::npos || fileName.find(".cia") != std::string::npos) {
                gameList.push_back(fileName);
            }
        }
        closedir(dir);
    } else {
        printf("Could not open 3DS directory\n");
    }
}

void renderMenu() {
    consoleClear();
    printf("\x1b[1;1H=============================");
    printf("\x1b[2;1H  3DS Emulator Main Menu  ");
    printf("\x1b[3;1H=============================");

    printf("\x1b[5;1H%s1. Boot 3DS Firmware Menu", selectedOption == 1 ? ">" : " ");
    printf("\x1b[6;1H%s2. Select Game", selectedOption == 2 ? ">" : " ");
    printf("\x1b[7;1H%s3. Exit", selectedOption == 3 ? ">" : " ");

    printf("\x1b[9;1H=============================");
    printf("\x1b[10;1H   Available 3DS Games:");
    printf("\x1b[11;1H=============================");

    for (size_t i = 0; i < gameList.size() && i < 10; ++i) { // Display up to 10 games
        printf("\x1b[%lu;1H%s %s", 12 + i, selectedOption == 4 + i ? ">" : " ", gameList[i].c_str());
    }

    printf("\x1b[23;1HUse D-Pad to navigate, A to select");

    gfxFlushBuffers();
    gfxSwapBuffers();
    gfxWaitForVsync();
}

void renderGameList() {
    if (selectedOption >= 4 && selectedOption < 4 + gameList.size()) {
        printf("\x1b[1;1HLoading %s...\n", gameList[selectedOption - 4].c_str());
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();

        // Here you would add code to load and run the selected game.
    }
}