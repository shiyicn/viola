#ifndef FEATURE
#define FEATURE

#include <iostream>
#include <vector>
#include <cstdlib>
#include "util.hpp"

typedef unsigned short ushort;


class Feature{

    ushort type;    //0,1,2,3
    Shape shape;   //size,
    Position position;       //position 
    int value;              //the value caculated 

    public:
        Feature( ushort type, Shape s,Position p, std::vector<std::vector<int> >&integral);
};

#endif