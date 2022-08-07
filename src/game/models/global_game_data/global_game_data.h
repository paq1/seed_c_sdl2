#ifndef __GLOBAL_GAME_DATA_H__
#define __GLOBAL_GAME_DATA_H__

#include <SDL_ttf.h>

#include "../window_group/window_group.h"
#include "../texts/text.h"
#include "../sprites/sprite.h"

typedef struct {
    window_group_t* window_group; // todo : sortir cette donnée (c'est une donnée pas vraiment liée au jeu)
    TTF_Font* font;
    text_t* fps_text;
    sprite_t* sprite_smiley;
} global_game_data_t; // todo : plutot l'appeler scene_principal_data_t (pour la scene principale)

#endif // __GLOBAL_GAME_DATA_H__