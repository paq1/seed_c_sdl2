#include "sdl_init.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "../draw_version_sdl.h"
#include "../error/exit_with_error_message.h"

void init_sdl() {
    print_version_sdl();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        exitWithError("SDL_Init");
    }

    if (TTF_Init() != 0) {
        exitWithError("TTF_Init");
    }
}