#include "window_group_factory.h"

#include "window_factory.h"
#include "../../services/error/exit_with_error_message.h"

window_group_t* create_window_group() {
    window_group_t* window_group = (window_group_t*) malloc(sizeof(window_group_t));
    if (window_group == NULL) {
        exitWithError("window group creation");
    }
    window_group->window = create_default_window();
    if (window_group->window == NULL) {
        free(window_group);
        exitWithError("window group creation");
    }

    window_group->renderer = SDL_CreateRenderer(window_group->window, -1, SDL_RENDERER_ACCELERATED);

    if (window_group->renderer == NULL) {
        SDL_DestroyWindow(window_group->window);
        free(window_group);
        exitWithError("window group creation");
    }

    return window_group;
}

void free_window_group(window_group_t** window_group) {
    SDL_DestroyRenderer((*window_group)->renderer);
    SDL_DestroyWindow((*window_group)->window);
    free(*window_group);
    *window_group = NULL;
}
