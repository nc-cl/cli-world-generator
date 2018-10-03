CC = g++
CFLAGS = -std=c++17 -Werror -Wpedantic
GLFLAGS = -lSDL2 -lGLEW -lGL

DEPENDENCIES = generate.o world_map.o world_map_section.o noise_generator.o sdl_window.o
EXECUTABLE = generate

DEPENDENCIES_NO_GUI = generate.o world_map.o world_map_section.o noise_generator.o
EXECUTABLE_NO_GUI  = generate_ngui

.PHONY: all
all: $(EXECUTABLE)

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
	rm -fv $(EXECUTABLE) *\.exe *\.o
