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
        SDL_ExitWithError("Initialisation renderer");
    }

    if (SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0) {
        SDL_ExitWithError("Initialisation couleur");
    }

    if (SDL_RenderDrawPoint(renderer, 100, 100) != 0) {
        SDL_ExitWithError("Dessin point");
    }

    if (SDL_RenderDrawLine(renderer, 200, 200, 500, 500) != 0) {
        SDL_ExitWithError("Dessin ligne");
    }

    if (SDL_RenderDrawRect(renderer, &(SDL_Rect){100, 100, 100, 100}) != 0) {
        SDL_ExitWithError("Dessin rectangle");
    }

    SDL_RenderPresent(renderer);

    // if (SDL_RenderClear(renderer) != 0) SDL_ExitWithError("Effacement renderer");
    

    SDL_Delay(3000); // todo delete this line

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