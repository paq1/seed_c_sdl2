#include "window_factory.h"

SDL_Window* create_default_window() {
    return SDL_CreateWindow(
        "seed c sdl2 -- windows version", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        SDL_WINDOW_SHOWN
    );
}
