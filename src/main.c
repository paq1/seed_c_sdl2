#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "models/position.h"

#include "game/services/draw_version_sdl.h"
#include "game/services/sdl_init/sdl_init.h"
#include "game/services/error/exit_with_error_message.h"

#include "game/factories/window/window_group_factory.h"
#include "game/factories/fonts/font_factory.h"

int main(int argc, char* argv[]) {
    
    init_sdl();
    window_group_t* window_group = create_window_group();
    SDL_Window *window = window_group->window;
    SDL_Renderer *renderer = window_group->renderer;
    
    /***************************************************/
    SDL_bool program_launched = SDL_TRUE;

    unsigned int old_ticks = SDL_GetTicks();
    double dt = 0.0;

    TTF_Font * font = create_comic_font(25);
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface * surface_text = TTF_RenderText_Solid(font, "fps : ???", color);
    SDL_Texture * texture_text = SDL_CreateTextureFromSurface(renderer, surface_text);
    SDL_FreeSurface(surface_text);

    SDL_Surface *surfaceSmiley = SDL_LoadBMP("assets/sprites/smiley_sdl_seed.bmp");
    if (surfaceSmiley == NULL) {
        TTF_CloseFont(font);
        free_window_group(window_group);
        exitWithError("Chargement image");
    }

    SDL_Texture *textureSmiley = SDL_CreateTextureFromSurface(renderer, surfaceSmiley);
    SDL_FreeSurface(surfaceSmiley);

    if (textureSmiley == NULL) {
        TTF_CloseFont(font);
        free_window_group(window_group);
        exitWithError("Creer texture");
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
            free_window_group(window_group);
            exitWithError("Afficher texture");
        }

        SDL_Rect rect = {0, 0, 0, 0};

        if (SDL_QueryTexture(texture_text, NULL, NULL, &rect.w, &rect.h) != 0) {
            TTF_CloseFont(font);
            SDL_DestroyTexture(texture_text);
            free_window_group(window_group);
            exitWithError("Charger texture");
        }

        if (SDL_RenderCopy(renderer, texture_text, NULL, &rect) != 0) {
            TTF_CloseFont(font);
            SDL_DestroyTexture(texture_text);
            free_window_group(window_group);
            exitWithError("Afficher texture texte");
        }


        SDL_RenderPresent(renderer);
        if (SDL_RenderClear(renderer) != 0) exitWithError("Effacement renderer");
    }
    /***************************************************/
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture_text);
    SDL_DestroyTexture(textureSmiley);
    free_window_group(window_group);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
