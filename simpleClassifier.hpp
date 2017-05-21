#ifndef SIMPLECLASSIFIER
#define SIMPLECLASSIFIER

typedef unsigned short ushort;

#include <vector>
#include <cstdlib>
#include "feature.hpp"
#include "image.hpp"

class SimpleClassifier{

    double w_0,w_1;
    int index;    
    //Type type;
    //Shape shape;
    //Position position;
     

    public:
        SimpleClassifier(double w_0,double w_1,int index);
        short predictByFeature(Feature &f);
        short predictByImage(Image &img);
        double getW0();
        double getW1();
        int getIndex();
        void setW0(double w);
        void setW1(double w);
        void updatePara(Image &img, double alpha);

        string toString();
        //Type getType();
        //Shape getShape();
       // Position getPosition();
};

#endif
