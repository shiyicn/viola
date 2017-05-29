all: main

main: image.o feature.o loader.o main.cpp
	mpic++ main.cpp image.o feature.o loader.o -L/usr/X11R6/lib -lm -lpthread -lX11 -o main

feature.o: feature.cpp util.hpp feature.hpp
	mpic++ -c feature.cpp

image.o: image.cpp image.hpp util.hpp
	mpic++ -c image.cpp