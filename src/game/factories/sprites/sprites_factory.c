#include "sprites_factory.h"

sprite_t * createSpriteSmileySdlSeed(SDL_Renderer * renderer) {
    return create_sprite_bmp("assets/sprites/smiley_sdl_seed.bmp", renderer);
}
