CC = g++
CFLAGS = -std=c++11 -Wall
DEPENDENCIES = generate.o world_map.o world_map_section.o noise_generator.o
EXECUTABLE = generate

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(DEPENDENCIES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(DEPENDENCIES)

%.o: %.cc
	$(CC) $(CFLAGS) -c $^

.PHONY: clean 
clean:
	rm -fv $(EXECUTABLE) *\.exe *\.o
