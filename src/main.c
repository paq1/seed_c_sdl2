#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "models/position.h"

#include "game/services/sprites/draw_sprite_service.h"
#include "game/services/texts/fps_text_service.h"
#include "game/services/texts/draw_text_service.h"
#include "game/services/draw_version_sdl.h"
#include "game/services/sdl_init/sdl_init.h"
#include "game/services/error/exit_with_error_message.h"

#include "game/factories/window/window_group_factory.h"
#include "game/factories/fonts/font_factory.h"
#include "game/factories/sprites/sprites_factory.h"
#include "game/factories/texts/text_factory.h"

void safe_free(
    window_group_t** window_group,
    TTF_Font** font,
    text_t** fps_text,
    sprite_t** sprite_smiley
);

int main(int argc, char* argv[]) {
    
    init_sdl();
    window_group_t* window_group = create_window_group();
    SDL_bool program_launched = SDL_TRUE;

    unsigned int old_ticks = SDL_GetTicks();
    double dt = 0.0;
    
    TTF_Font* font = create_comic_font(25);

    text_t* fps_text = create_fps_text(window_group->renderer, font);
    if (fps_text == NULL) {
        safe_free(&window_group, &font, NULL, NULL);
        exitWithError("Error when creating fps text");
    }

    sprite_t* spriteSmiley = createSpriteSmileySdlSeed(window_group->renderer);
    if (spriteSmiley == NULL) {
        safe_free(&window_group, &font, &fps_text, NULL);
        exitWithError("sprite smiley loading error");
    }

    position_t position = {0.0, 0.0};

    double timer = 0.0;
    int frames = 0;

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

        timer += dt;
        frames++;
        if (timer > 1.0) {
            timer = 0.0;
            fps_text = update_fps_text(
                window_group->renderer,
                fps_text,
                frames,
                font
            );
            frames = 0;
        }

        position.x += dt * 200.0;
        position.y += dt * 100.0;
        spriteSmiley->x = position.x;
        spriteSmiley->y = position.y;
        
        SDL_SetRenderDrawColor(window_group->renderer, 255, 100, 100, 255);

        if (draw_sprite_with_scale(spriteSmiley, window_group->renderer, 2., 2.) != 0) {
            safe_free(&window_group, &font, &fps_text, &spriteSmiley);
            exitWithError("erreur lors de l'affichage du sprite");
        }

        if (draw_text(fps_text, window_group->renderer, 0, 0) != 0) {
            safe_free(&window_group, &font, &fps_text, &spriteSmiley);
            exitWithError("erreur lors de l'affichage du texte");
        }

        SDL_RenderPresent(window_group->renderer);
        if (SDL_RenderClear(window_group->renderer) != 0) exitWithError("Effacement renderer");
    }
    /***************************************************/
    safe_free(&window_group, &font, &fps_text, &spriteSmiley);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

void safe_free(
    window_group_t** window_group,
    TTF_Font** font,
    text_t** fps_text,
    sprite_t** sprite_smiley
) {
    if (fps_text != NULL) free_text(fps_text);
    if (sprite_smiley != NULL) free_sprite(sprite_smiley);
    if (*font != NULL) {
        TTF_CloseFont(*font);
        *font = NULL;
    }
    if (window_group != NULL) free_window_group(window_group);
    
    if (*fps_text == NULL) {
        printf("suppression fps_text : OK\n");
    }
    if (*sprite_smiley == NULL) {
        printf("suppression sprite_smiley : OK\n");
    }
    if (*font == NULL) {
        printf("suppression font : OK\n");
    }
    if (*window_group == NULL) {
        printf("suppression window_group : OK\n");
    }

    printf("suppression des ressources : Completed\n");
}
