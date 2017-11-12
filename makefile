
default:
	@ g++ -std=c++11 -Wall -o gen gen.cc
	
clean:
	@ rm -f gen gen.exe

