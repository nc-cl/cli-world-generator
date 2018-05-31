CC = g++
CFLAGS = -std=c++11 -Wall
GLFLAGS = -lSDL2 -lGLEW -lGL
DEPENDENCIES = generate.o world_map.o world_map_section.o noise_generator.o gl_window.o
EXECUTABLE = generate

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(DEPENDENCIES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(DEPENDENCIES) $(GLFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $^

.PHONY: clean 
clean:
	rm -fv $(EXECUTABLE) *\.exe *\.o
