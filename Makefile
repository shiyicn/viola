all: main

main: image.o feature.o
	gcc -g -Wall -o main image.o feature.o

feature.o: feature.cpp util.hpp feature.hpp
	gcc -c feature.cpp

image.o: image.cpp image.hpp
	gcc -c image.cpp

clean:
	rm main *.o
	


