#include "draw_version_sdl.h"

#include <stdio.h>
#include <SDL.h>

void print_version_sdl() {
    SDL_version version;
    SDL_VERSION(&version);
    printf("version SDL : %d.%d.%d\n", version.major, version.minor, version.patch);
}
