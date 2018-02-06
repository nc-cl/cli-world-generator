CPPC = g++
CFLAGS = -std=c++11 -Wall
TARGET = gen.cc
OUTPUT = gen
OUTPUT_PRE = pre.cc

default:
	@ $(CPPC) $(CFLAGS) $(TARGET) -o $(OUTPUT)

pre:
	@ $(CPPC) $(CFLAGS) -E $(TARGET) > $(OUTPUT_PRE) && $(CPPC) $(CFLAGS) $(OUTPUT_PRE) -o $(OUTPUT)

clean:
	@ rm -f $(OUTPUT) $(OUTPUT).exe $(OUTPUT_PRE)

