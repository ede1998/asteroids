## MAKEFILE c_template_v1

CC=g++
CFLAGS=-W -Wall -Wextra -O0 -g -fdiagnostics-color #-I include (suche in diesem ordner nach c files)

SDL_FLAGS := $(shell sdl2-config --cflags --libs) $(shell pkg-config gl --libs)

PROJ_OBJ = main.cpp GL-Window.cpp AS-spaceship.cpp AS-environment.cpp

PROJ_LDFLAGS=-ldl #dynamic linking

all: project1
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
project1: $(PROJ_OBJ)
	$(CC) -o project1 $(PROJ_OBJ) $(PROJ_LDFLAGS) $(CFLAGS) $(SDL_FLAGS)

clean:
	rm -f *.o
	rm -f project1


