CPPC = g++
CFLAGS = -std=c++11 -Wall
TARGET = generate.cc
OUTPUT = generate
OUTPUT_PRE = pre.cc

.PHONY: generate pre clean

generate:
	@ $(CPPC) $(CFLAGS) $(TARGET) -o $(OUTPUT)

pre:
	@ $(CPPC) $(CFLAGS) -E $(TARGET) > $(OUTPUT_PRE) && $(CPPC) $(CFLAGS) $(OUTPUT_PRE) -o $(OUTPUT)

clean:
	@ rm -f $(OUTPUT) $(OUTPUT).exe $(OUTPUT_PRE)

