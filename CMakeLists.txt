cmake_minimum_required(VERSION 3.17)

set(NOM_PROJET seed_c_sdl2)
set(BIN bin)
project(${NOM_PROJET})

set(CMAKE_C_STANDARD 11)

# lib sfml
include_directories(include)
link_directories(lib)

add_executable(
        ${NOM_PROJET} 
        src/main.c
        src/game/models/sprites/sprite.c
        src/game/models/texts/text.c
        src/game/services/draw_version_sdl.c
        src/game/services/sprites/draw_sprite_service.c
        src/game/services/error/exit_with_error_message.c
        src/game/services/sdl_init/sdl_init.c
        src/game/factories/window/window_factory.c
        src/game/factories/window/window_group_factory.c
        src/game/factories/fonts/font_factory.c
        src/game/factories/sprites/sprites_factory.c
        src/game/factories/texts/text_factory.c
)

# linkage librairie
target_link_libraries(
        ${NOM_PROJET}
        -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
)