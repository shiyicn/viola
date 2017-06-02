#ifndef UTIL
#define UTIL

typedef unsigned short ushort;

struct Shape
{
    ushort width;
    ushort height;
};

struct Position{        //the coordinate of the upleft point
    ushort x;
    ushort y;
};

struct ROC{
    double theta;
    double fpr;
    double tpr;
};

#endif
