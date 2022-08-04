CC = gcc
OBJ = obj
BIN = bin
LIB = lib
SRC = src
CC = gcc
CFLAGS = -Wall -std=c11 $(INCLUDE_SFML) $(INCLUDE_JSONCPP)
EXEC = seed_c_sdl2
POINT_C = $(wildcard $(SRC)/*.c)
POINT_O = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(POINT_C))

# recette: ingredient(s)
# $< prend le premier ingrédient de la recette
# $@ prend le nom de la recette
# $^ prent tout les ingredients
# @commande ... masque la commande

all: $(EXEC)

$(EXEC): $(OBJ)/main.o $(POINT_O) 
	$(CC) $^ -o $(BIN)/$(EXEC) -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) -c $(CFLAGS) $< -o $@ -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

run: all
	./$(BIN)/$(EXEC)