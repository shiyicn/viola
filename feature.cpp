#include "feature.hpp"

using namespace std;


double featureCal(Type type, Shape s, Position p,  const vector<vector<double> > &integral);
double featureAcal(Shape s, Position p, const vector<vector<double> > &integral);
double featureBcal(Shape s, Position p, const vector<vector<double> > &integral);
double featureCcal(Shape s, Position p, const vector<vector<double> > &integral);
double featureDcal(Shape s, Position p, const vector<vector<double> > &integral);

double Feature::getValue() {
    return value;
}

Type Feature::getType(){
    return this->type;
}

Shape Feature::getShape(){
    return this->shape;
}

Position Feature::getPosition(){
    return this->position;
}

Feature::Feature(Type type,Shape s,Position p, const vector<vector<double> >& integral){
    this->type = type;
    this->shape = s;
    this->position = p;
    this->value = featureCal(type,s,p,integral);
}

double featureCal(Type type, Shape s,Position p,  const vector<vector<double> > &integral){
    switch (type)
    {
        case A: 
            return featureAcal(s,p,integral);
            break;
        case B:
            return featureBcal(s,p,integral);
            break;
        case C:
            return featureCcal(s,p,integral);
            break;
        case D:
            return featureDcal(s,p,integral);
            break;
    default:
        exit(-1);
        break;
    }
}

double featureAcal(Shape s, Position p, const vector<vector<double> > &integral){

    double bottomRight = integral[p.x + s.width-1][p.y + s.height-1];        //bottom-left podouble of black part
    double bottomCenter = integral[p.x + s.width/2-1][p.y + s.height-1];    //bottom-center podouble 
    double bottomLeft = (p.x==0)?0:integral[p.x-1][p.y + s.height-1];                  //bottom-right podouble

    double upRight = (p.y==0)?0:integral[p.x + s.width-1][p.y-1];                   //up-left podouble of black part
    double upCenter = (p.y==0)?0:integral[p.x + s.width/2 - 1][p.y-1];               //up-center podouble
    double upLeft = (p.x==0||p.y==0)?0:integral[p.x-1][p.y-1];


    double wholePart = bottomRight - bottomLeft;
    wholePart -= (upRight - upLeft);

    double whitePart = bottomCenter - bottomLeft;
    whitePart -= (upCenter - upLeft);

    return wholePart - 2*whitePart;
}

double featureBcal(Shape s, Position p, const vector<vector<double> > &integral){

    double bottomRight = integral[p.x + s.width - 1][p.y + s.height - 1];
    double bottomLeft = (p.x==0)?0:integral[p.x - 1][p.y + s.height - 1];
    double rightCenter = integral[p.x + s.width - 1][p.y + s.height/2 - 1];
    double leftCenter = (p.x==0)?0:integral[p.x-1][p.y + s.height/2 -1 ];
    double upRight = (p.y==0)?0:integral[p.x + s.width - 1][p.y - 1];
    double upLeft = (p.x==0||p.y==0)?0:integral[p.x - 1][p.y - 1];

    double wholePart = bottomRight - bottomLeft;
    wholePart -= (upRight - upLeft);

    double whitePart = bottomRight - bottomLeft;
    whitePart -= (rightCenter - leftCenter);

    return wholePart - 2*whitePart;
}

double featureCcal(Shape s, Position p, const vector<vector<double> >&integral){

    double bottomRight = integral[p.x + s.width - 1][p.y + s.height - 1];
    double bottomBRight = integral[p.x + s.width*3/4 - 1][p.y + s.height - 1];    // the bottom-right podouble of the black part
    double bottomBLeft = integral[p.x + s.width/4 - 1][p.y + s.height - 1];
    double bottomLeft = (p.x==0)?0:integral[p.x - 1][p.y + s.height - 1];

    double upRight = (p.y==0)?0:integral[p.x + s.width - 1][p.y - 1];
    double upBRight = (p.y==0)?0:integral[p.x + s.width*3/4 - 1][p.y - 1];
    double upBLeft = (p.y==0)?0:integral[p.x + s.width/4 - 1][p.y - 1];
    double upLeft = (p.x==0||p.y==0)?0:integral[p.x - 1][p.y - 1];

    double wholePart = bottomRight - bottomLeft;
    wholePart -= (upRight - upLeft);
    
    double whitePart1 = bottomRight - bottomBRight;
    whitePart1 -= (upRight - upBRight);

    double whitePart2 = bottomBLeft - bottomLeft;
    whitePart2 -= (upBLeft - upLeft);

    return wholePart - 2*whitePart1 - 2*whitePart2;
}

double featureDcal(Shape s, Position p, const vector<vector<double> > &integral){
    Shape part1 = {s.width,s.height/2};
    Shape part2 = {s.width,s.height/2};
    Position p2 = {p.x,p.y+s.height/2};
    return featureAcal( part1,p,integral) - featureAcal(part2,p2,integral);
}
