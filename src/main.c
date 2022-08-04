#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct position_t {
    double x;
    double y;
} position_t;

void SDL_ExitWithError(const char *message);
void affiche_version_sdl();
SDL_Window * create_default_window();

int main(int argc, char* argv[]) {
    affiche_version_sdl();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_ExitWithError("Initialisation SDL");
    }

    if (TTF_Init() != 0) {
        SDL_ExitWithError("Initialisation TTF");
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

    unsigned int old_ticks = SDL_GetTicks();
    double dt = 0.0;

    TTF_Font * font = TTF_OpenFont("assets/fonts/dpcomic.ttf", 25);
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface * surface_text = TTF_RenderText_Solid(font, "fps : ???", color);
    SDL_Texture * texture_text = SDL_CreateTextureFromSurface(renderer, surface_text);
    SDL_FreeSurface(surface_text);

    SDL_Surface *surfaceSmiley = SDL_LoadBMP("assets/sprites/smiley_sdl_seed.bmp");
    if (surfaceSmiley == NULL) {
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Chargement image");
    }

    SDL_Texture *textureSmiley = SDL_CreateTextureFromSurface(renderer, surfaceSmiley);
    SDL_FreeSurface(surfaceSmiley);

    if (textureSmiley == NULL) {
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Creer texture");
    }

    position_t position = {0, 0};

    while (program_launched) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_LEAVE) {
                        SDL_Log("La souris est sortie de la fenêtre.\n");
                    }
                    if (event.window.event == SDL_WINDOWEVENT_ENTER) {
                        SDL_Log("La souris est entrée dans la fenêtre.\n");
                    }
                    if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                        SDL_Log("La fenêtre a le focus.\n");
                    }
                    if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                        SDL_Log("La fenêtre n'a plus le focus.\n");
                    }
                    break;
                case SDL_MOUSEMOTION:
                    // SDL_Log("Mouse moved to %d,%d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // SDL_Log("Mouse moved to %d,%d\n", event.motion.x, event.motion.y);
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_Log("Left mouse button down\n");
                    } else if (event.button.button == SDL_BUTTON_RIGHT) {
                        SDL_Log("Right mouse button down\n");
                    } else if (event.button.button == SDL_BUTTON_MIDDLE) {
                        SDL_Log("Middle mouse button down\n");
                    }
                    SDL_Log("Mouse clicked to %d,%d\n", event.motion.x, event.motion.y);
                    break;
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

        unsigned int new_ticks = SDL_GetTicks();
        dt = (new_ticks - old_ticks) / 1000.0;
        old_ticks = new_ticks;

        position.x += dt * 200.0;
        position.y += dt * 100.0;

        
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);


        if (SDL_RenderCopy(renderer, textureSmiley, NULL, &(SDL_Rect){position.x, position.y, 64, 64}) != 0) {
            TTF_CloseFont(font);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Afficher texture");
        }

        SDL_Rect rect = {0, 0, 0, 0};

        if (SDL_QueryTexture(texture_text, NULL, NULL, &rect.w, &rect.h) != 0) {
            TTF_CloseFont(font);
            SDL_DestroyTexture(texture_text);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Charger texture");
        }

        if (SDL_RenderCopy(renderer, texture_text, NULL, &rect) != 0) {
            TTF_CloseFont(font);
            SDL_DestroyTexture(texture_text);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Afficher texture texte");
        }


        SDL_RenderPresent(renderer);
        if (SDL_RenderClear(renderer) != 0) SDL_ExitWithError("Effacement renderer");
    }
    /***************************************************/
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture_text);
    SDL_DestroyTexture(textureSmiley);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    TTF_Quit();
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