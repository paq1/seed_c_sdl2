#include "global_game_data_service.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "../../models/global_game_data/global_game_data.h"
#include "../../factories/window/window_group_factory.h"

void safe_free_of_fields_global_game_data(global_game_data_t* data) {
    if (data->fps_text != NULL) free_text(&data->fps_text);
    if (data->sprite_smiley != NULL) free_sprite(&data->sprite_smiley);
    if (data->font != NULL) {
        TTF_CloseFont(data->font);
        data->font = NULL;
    }
    if (data->window_group != NULL) free_window_group(&data->window_group);
    
    if (data->fps_text == NULL) {
        printf("suppression fps_text : OK\n");
    }
    if (data->sprite_smiley == NULL) {
        printf("suppression sprite_smiley : OK\n");
    }
    if (data->font == NULL) {
        printf("suppression font : OK\n");
    }
    if (data->window_group == NULL) {
        printf("suppression window_group : OK\n");
    }
}
