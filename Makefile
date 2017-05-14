all: main

main: image.o feature.o main.cpp
	mpic++ main.cpp image.o feature.o -o main

feature.o: feature.cpp util.hpp feature.hpp
	g++ -c feature.cpp

image.o: image.cpp image.hpp util.hpp
	g++ -c image.cpp

clean:
	rm main *.o