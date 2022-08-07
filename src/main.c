#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "models/position.h"

#include "game/services/global_game_data/global_game_data_service.h"
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

int main(int argc, char* argv[]) {
    
    init_sdl();

    global_game_data_t global_game_data = {NULL, NULL, NULL, NULL};
    global_game_data.window_group = create_window_group();
    SDL_bool program_launched = SDL_TRUE;

    unsigned int old_ticks = SDL_GetTicks();
    double dt = 0.0;
    
    global_game_data.font = create_comic_font(25);

    global_game_data.fps_text = create_fps_text(global_game_data.window_group->renderer, global_game_data.font);
    if (global_game_data.fps_text == NULL) {
        safe_free_of_fields_global_game_data(&global_game_data);
        exitWithError("Error when creating fps text");
    }

    global_game_data.sprite_smiley = createSpriteSmileySdlSeed(global_game_data.window_group->renderer);
    if (global_game_data.sprite_smiley == NULL) {
        safe_free_of_fields_global_game_data(&global_game_data);
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
            global_game_data.fps_text = update_fps_text(
                global_game_data.window_group->renderer,
                global_game_data.fps_text,
                frames,
                global_game_data.font
            );
            frames = 0;
        }

        if (position.x < 500 && position.y < 500) {
            position.x += dt * 100;
            position.y += dt * 100;
            global_game_data.sprite_smiley->x = position.x;
            global_game_data.sprite_smiley->y = position.y;
        } 
        
        
        SDL_SetRenderDrawColor(global_game_data.window_group->renderer, 255, 100, 100, 255);

        if (draw_sprite_with_scale(global_game_data.sprite_smiley, global_game_data.window_group->renderer, 2., 2.) != 0) {
            safe_free_of_fields_global_game_data(&global_game_data);
            exitWithError("erreur lors de l'affichage du sprite");
        }

        if (draw_text(global_game_data.fps_text, global_game_data.window_group->renderer, 0, 0) != 0) {
            safe_free_of_fields_global_game_data(&global_game_data);
            exitWithError("erreur lors de l'affichage du texte");
        }

        SDL_RenderPresent(global_game_data.window_group->renderer);
        if (SDL_RenderClear(global_game_data.window_group->renderer) != 0) exitWithError("Effacement renderer");
    }
    /***************************************************/
    safe_free_of_fields_global_game_data(&global_game_data);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
