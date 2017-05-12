#include "feature.hpp"

int featureAcal(Shape s, Position p, & std::vector<std::vector<int> >integral);
int featureBcal(Shape s, Position p, & std::vector<std::vector<int> >integral);
int featureCcal(Shape s, Position p, & std::vector<std::vector<int> >integral);
int featureDcal(Shape s, Position p, & std::vector<std::vector<int> >integral);

Feature::Feature(ushort type,Shape s,Position p,& std::vector<std::vector<int> >integral){
    this->type = type;
    this->shape = s;
    this->position = p;
    this->value = 
}

int featureAcal(Shape s, Position p, & std::vector<std::vector<int> >integral){
    int bottomRight = integral[p.x + s.width][p.y + s.height];        //bottom-left point of black part
    int bottomCenter = integral[p.x + s.width/2][p.y + s.height];    //bottom-center point 
    int bottomLeft = integral[p.x][p.y + s.height];                  //bottom-right point

    int upRight = integral[p.x + s.width][p.y];                   //up-left point of black part
    int upCenter = integral[p.x + s.width/2][p.y];               //up-center point
    int upLeft = integral[p.x][p.y];


    int blackPart = bottomRight - bottomCenter;
    blackPart -= (upRight - upCenter);

    int whitePart = bottomCenter - bottomLeft;
    whitePart -= (upCenter - upLeft);

    return blackPart - whitePart;
}

int featureBcal(Shape s, Position p, & std::vector<std::vector<int> >integral){
    int bottomRight = integral[p.x + s.width][p.y + s.height];
    int bottomLeft = integral[p.x][p.y + s.height];
    int rightCenter = integral[p.x + s.width][p.y + s.height/2];
    int leftCenter = integral[p.x][p.y + s.height/2];
    int upRight = integral[p.x + s.width][p.y];
    int upLeft = integral[p.x][p.y];

    int blackPart = rightCenter - leftCenter;
    blackPart -= (upRight - upLeft);

    int whitePart = bottomRight - bottomLeft;
    whitePart -= (rightCenter - leftCenter);

    return blackPart - whitePart;
}

int featureCcal(Shape s, Position p, & std::vector<std::vector<int> >integral){

}

int featureDcal(Shape s, Position p, & std::vector<std::vector<int> >integral){
    
}
