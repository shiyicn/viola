all: main

main: image.o feature.o loader.o main.cpp
	mpic++ main.cpp image.o feature.o loader.o -02 -L/usr/X11R6/lib -lm -lpthread -lX11 -o main

loader.o: loader.cpp loader.hpp image.cpp image.hpp
	mpic++ -c -02 -L/usr/X11R6/lib -lm -lpthread -lX11 loader.cpp

feature.o: feature.cpp util.hpp feature.hpp
	mpic++ -c feature.cpp

image.o: image.cpp image.hpp util.hpp
	mpic++ -c image.cpp