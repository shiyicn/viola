all: main convertor

main: image.o feature.o loader.o main.cpp
	mpic++ main.cpp image.o feature.o loader.o main

feature.o: feature.cpp util.hpp feature.hpp
	c++ -c feature.cpp

image.o: image.cpp image.hpp util.hpp
	c++ -c image.cpp

convertor: convertor.cpp convertor.hpp Makefile
	c++ -c convertor.cpp -L/usr/X11R6/lib -lm -lpthread -lX11 -o convertor

clean:
	rm -rf main convertor *.o *~