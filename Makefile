all: main

main: image.o feature.o loader.o main.cpp
	mpic++ main.cpp image.o feature.o loader.o -o main -O2 -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lm -lpthread -lX11

loader.o: loader.cpp loader.hpp image.cpp image.hpp
	g++ -c loader.cpp 

feature.o: feature.cpp util.hpp feature.hpp
	g++ -c feature.cpp

image.o: image.cpp image.hpp util.hpp
	g++ -c image.cpp

clean:
	rm main *.o