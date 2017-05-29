all: main convertor

main: image.o feature.o loader.o main.cpp
	mpic++ main.cpp image.o feature.o loader.o main

feature.o: feature.cpp util.hpp feature.hpp
	g++ -c feature.cpp

image.o: image.cpp image.hpp util.hpp
	g++ -c image.cpp

convertor: convertor.cpp convertor.hpp Makefile
	g++ convertor.cpp -L/usr/X11R6/lib -lm -lpthread -lX11 -o convertor

clean:
	rm -rf main convertor *.o *~