
INCLUDE = -I/usr/local/boost-1.58.0/include/ -I/usr/local/CImg-1.6.2/
LIBS = -lpthread -lX11 -L/usr/local/boost-1.58.0/lib/
LDPATH = LD_LIBRARY_PATH=/usr/local/boost-1.58.0/lib:/usr/lib/alliance/lib

all: main convertor

main: image.o feature.o loader.o main.cpp
	mpic++ -o main.cpp image.o feature.o loader.o main

feature.o: feature.cpp util.hpp feature.hpp
	g++ -c feature.cpp

image.o: image.cpp image.hpp util.hpp
	g++ -c image.cpp

convertor: convertor.cpp convertor.hpp Makefile
	g++ $(FLAGS) $(INCLUDE) convertor.cpp -o convertor $(LIBS)

clean:
	rm -rf main convertor *.o *~