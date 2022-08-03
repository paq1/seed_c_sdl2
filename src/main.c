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

    SDL_Surface *surface = SDL_LoadBMP("assets/sprites/facture_gaz_face.bmp");
    if (surface == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Chargement image");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Creer texture");
    }

    SDL_Rect rect = {200, 200, 100, 100};

    if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) != 0) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Charger texture");
    }

    if (SDL_RenderCopy(renderer, texture, NULL, &rect) != 0) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Afficher texture");
    }

    SDL_RenderPresent(renderer);

    // if (SDL_RenderClear(renderer) != 0) SDL_ExitWithError("Effacement renderer");
    

    SDL_Delay(3000); // todo delete this line

    SDL_DestroyTexture(texture);
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