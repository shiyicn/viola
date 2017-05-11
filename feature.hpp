#ifndef FEATURE
#define FEATURE

#include <iostream>
#include <vector>
#include <cstdlib>

typedef unsigned short ushort;

class Feature{

    ushort type;    //0,1,2,3
    ushort width,height;   //size
    ushort x,y;       //position 
    int value;              //the value caculated 

    public:
        Feature( ushort type, ushort w, ushort h, ushort x, ushort y,std::vector<std::vector<int> >integral);
};

#endif