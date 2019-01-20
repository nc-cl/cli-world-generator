CC = g++
CFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -Wold-style-cast -Wuseless-cast -Werror
GLFLAGS = -lSDL2 -lGLEW -lGL

DEPENDENCIES = main.o height_map.o shader_handler.o height_map_mesh.o height_map_settings_mask.o
EXECUTABLE = main

DEPENDENCIES_NO_GUI = main.o height_map.o height_map_settings_mask.o
EXECUTABLE_NO_GUI  = main_nogui

.PHONY: all
all: $(EXECUTABLE)

.PHONY: debug
debug: CFLAGS += -ggdb3
debug: $(EXECUTABLE)

$(EXECUTABLE): $(DEPENDENCIES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(DEPENDENCIES) $(GLFLAGS)

.PHONY: no_gui
no_gui: $(EXECUTABLE_NO_GUI)

$(EXECUTABLE_NO_GUI): $(DEPENDENCIES_NO_GUI)
	$(CC) $(CFLAGS) -o $(EXECUTABLE_NO_GUI) $(DEPENDENCIES_NO_GUI)

%.o: %.cc
	$(CC) $(CFLAGS) -c $^

.PHONY: clean 
clean:
	rm -fv $(EXECUTABLE) $(EXECUTABLE_NO_GUI)  *\.exe *\.o
