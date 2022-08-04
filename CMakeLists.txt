cmake_minimum_required(VERSION 3.17)

set(NOM_PROJET seed_c_sdl2)
set(BIN bin)
project(${NOM_PROJET})

set(CMAKE_C_STANDARD 11)

# lib sfml
include_directories(include)
link_directories(lib)

add_executable(${NOM_PROJET} src/main.c)

# linkage librairie
target_link_libraries(
        ${NOM_PROJET}
        -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
)