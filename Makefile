all: main

main: image.o feature.o loader.o main.cpp
	mpic++ main.cpp image.o feature.o loader.o -o main

loader.o: loader.cpp loader.hpp image.cpp image.hpp
	g++ -c loader.cpp

feature.o: feature.cpp util.hpp feature.hpp
	g++ -c feature.cpp

image.o: image.cpp image.hpp util.hpp
	g++ -c image.cpp

clean:
	rm main *.o