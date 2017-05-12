all: main

main: image.o feature.o main.o
	g++ -g -Wall -o main main.o image.o feature.o

main.o: main.cpp
	g++ -c main.cpp

feature.o: feature.cpp util.hpp feature.hpp
	g++ -c feature.cpp

image.o: image.cpp image.hpp
	g++ -c image.cpp

clean:
	rm main *.o