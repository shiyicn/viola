#all: main

#main: image.o feature.o loader.o main.cpp
#	mpic++ main.cpp image.o feature.o loader.o -o main

#loader.o: loader.cpp loader.hpp image.cpp image.hpp
#	g++ -c loader.cpp

#feature.o: feature.cpp util.hpp feature.hpp
#	g++ -c feature.cpp

#image.o: image.cpp image.hpp util.hpp
#	g++ -c image.cpp

#clean:
#	rm main *.o

OBJS = main
CXX = mpic++
DEBUG = -g
CXXFLAGS= -Wall -c $(DEBUG) -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
LFLAGS = -Wall $(DEBUG) -lm -lX11

all: main

loader.o: loader.cpp loader.hpp image.cpp image.hpp
	$(CXX) $(CXXFLAGS) loader.cpp

feature.o: feature.cpp util.hpp feature.hpp
	$(CXX) $(LFLAGS) feature.cpp

image.o: image.cpp image.hpp util.hpp
	$(CXX) $(LFLAGS) image.cpp

main : image.o feature.o loader.o main.cpp
	$(CXX) $(LFLAGS) main.cpp image.o feature.o loader.o -o main

clean:
	\rm *.o main