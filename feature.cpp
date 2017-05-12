#include "feature.hpp"

using namespace std;


int featureCal(int type, Shape s, Position p,  vector<vector<int> > &integral);
int featureAcal(Shape s, Position p, vector<vector<int> > &integral);
int featureBcal(Shape s, Position p, vector<vector<int> > &integral);
int featureCcal(Shape s, Position p, vector<vector<int> > &integral);
int featureDcal(Shape s, Position p, vector<vector<int> > &integral);

int Feature::getValue() {
    return value;
}

Feature::Feature(ushort type,Shape s,Position p, vector<vector<int> > &integral){
    this->type = type;
    this->shape = s;
    this->position = p;
    this->value = featureCal(type,s,p,integral);
}

int featureCal(int type, Shape s,Position p,  vector<vector<int> > &integral){
    switch (type)
    {
        case 1: 
            return featureAcal(s,p,integral);
            break;
        case 2:
            return featureBcal(s,p,integral);
            break;
        case 3:
            return featureCcal(s,p,integral);
            break;
        case 4:
            return featureDcal(s,p,integral);
            break;
    default:
        exit(-1);
        break;
    }
}

int featureAcal(Shape s, Position p, vector<vector<int> > &integral){

    int bottomRight = integral[p.x + s.width-1][p.y + s.height-1];        //bottom-left point of black part
    int bottomCenter = integral[p.x + s.width/2-1][p.y + s.height-1];    //bottom-center point 
    int bottomLeft = (p.x==0)?0:integral[p.x-1][p.y + s.height-1];                  //bottom-right point

    int upRight = (p.y==0)?0:integral[p.x + s.width-1][p.y-1];                   //up-left point of black part
    int upCenter = (p.y==0)?0:integral[p.x + s.width/2 - 1][p.y-1];               //up-center point
    int upLeft = (p.x==0||p.y==0)?0:integral[p.x-1][p.y-1];


    int wholePart = bottomRight - bottomLeft;
    wholePart -= (upRight - upLeft);

    int whitePart = bottomCenter - bottomLeft;
    whitePart -= (upCenter - upLeft);

    return wholePart - 2*whitePart;
}

int featureBcal(Shape s, Position p, vector<vector<int> > &integral){

    int bottomRight = integral[p.x + s.width - 1][p.y + s.height - 1];
    int bottomLeft = (p.x==0)?0:integral[p.x - 1][p.y + s.height - 1];
    int rightCenter = integral[p.x + s.width - 1][p.y + s.height/2 - 1];
    int leftCenter = (p.x==0)?0:integral[p.x-1][p.y + s.height/2 -1 ];
    int upRight = (p.y==0)?0:integral[p.x + s.width - 1][p.y - 1];
    int upLeft = (p.x==0||p.y==0)?0:integral[p.x - 1][p.y - 1];

    int wholePart = bottomRight - bottomLeft;
    wholePart -= (upRight - upLeft);

    int whitePart = bottomRight - bottomLeft;
    whitePart -= (rightCenter - leftCenter);

    return wholePart - 2*whitePart;
}

int featureCcal(Shape s, Position p, vector<vector<int> >&integral){

    int bottomRight = integral[p.x + s.width - 1][p.y + s.height - 1];
    int bottomBRight = integral[p.x + s.width*0.75 - 1][p.y + s.height - 1];    // the bottom-right point of the black part
    int bottomBLeft = integral[p.x + s.width*0.25 - 1][p.y + s.height - 1];
    int bottomLeft = (p.x==0)?0:integral[p.x - 1][p.y + s.height - 1];

    int upRight = integral[p.x + s.width - 1][p.y - 1];
    int upBRight = (p.y==0)?0:integral[p.x + s.width*0.75 - 1][p.y - 1];
    int upBLeft = (p.y==0)?0:integral[p.x + s.width*0.25 - 1][p.y - 1];
    int upLeft = (p.x==0||p.y==0)?0:integral[p.x - 1][p.y - 1];

    int wholePart = bottomRight - bottomLeft;
    wholePart -= (upRight - upLeft);

    int whitePart1 = bottomRight - bottomBRight;
    whitePart1 -= (upRight - upBRight);

    int whitePart2 = bottomBLeft - bottomLeft;
    whitePart2 -= (upBLeft - upLeft);

    return wholePart - 2*whitePart1 - 2*whitePart2;
}

int featureDcal(Shape s, Position p, vector<vector<int> > &integral){
    Shape part1 = {s.width,s.height/2};
    Shape part2 = {s.width,s.height/2};
    Position p2 = {p.x,p.y+s.height/2};
    return featureAcal( part1,p,integral) - featureAcal(part2,p2,integral);
}
