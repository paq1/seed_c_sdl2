#include "fps_text_service.h"

#include "../../../core/services/string/string_commun_service.h"

text_t* update_fps_text(
    SDL_Renderer* renderer,
    text_t* fps_text,
    int fps,
    TTF_Font* font
) {
    char* fps_text_value = int_to_string(fps);
    char* text_content = string_concat("fps : ", fps_text_value);
    free(fps_text_value);

    fps_text = get_updated_text_with_value(
        renderer,
        fps_text,
        text_content,
        font
    );

    free(text_content);

    return fps_text;
}