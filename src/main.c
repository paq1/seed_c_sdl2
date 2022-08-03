#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void SDL_ExitWithError(const char *message);
void affiche_version_sdl();
SDL_Window * create_default_window();

int main(int argc, char* argv[]) {
    affiche_version_sdl();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_ExitWithError("Initialisation SDL");
    }

    SDL_Window *window = create_default_window();
    if (window == NULL) {
        SDL_ExitWithError("Initialisation fenêtre");
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Initialisation renderer");
    }

    /***************************************************/
    SDL_bool program_launched = SDL_TRUE;

    while (program_launched) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        program_launched = SDL_FALSE;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderPresent(renderer);
        if (SDL_RenderClear(renderer) != 0) SDL_ExitWithError("Effacement renderer");
    }
    /***************************************************/

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void affiche_version_sdl() {
    SDL_version version;
    SDL_VERSION(&version);
    printf("version SDL : %d.%d.%d\n", version.major, version.minor, version.patch);
}

SDL_Window* create_default_window() {
    SDL_Window *window = SDL_CreateWindow(
        "seed c sdl2 -- windows version", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600,
        600,
        SDL_WINDOW_SHOWN
    );

    return window;
}