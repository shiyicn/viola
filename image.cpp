#include "image.hpp"
#include "util.hpp"

using namespace std;
typedef unsigned short ushort;

const ushort widthInit = 8;
const ushort heightInit = 8;
const ushort incrementP = 4;
const ushort incrementS = 4;

Image::Image(vector<vector<int> > &data, short c){
    this->data = data;
    this->clacc = c;
} 

void Image::calIntegral(){
    int t;
    //vector<vector<int> > res;
    for (int i = 0; i < data.size(); i+=1) {
        vector<int> row;
        for (int j = 0; j < data[i].size(); j+=1){
            t = data[i][j];
            if (j > 0) t += row[j-1];
            if (i > 0) t += integral[i-1][j];
            if (i > 0 && j > 0) t -= integral[i-1][j-1];
            row.push_back(t);
        }
        this->integral.push_back(row);
    }
}

void Image::calFeatureVector(){
    ushort imageHeight = this->data.size();
    ushort imageWidth = this->data[0].size();
    ushort recWidth = widthInit;
    ushort recHeight = heightInit;

    for(ushort hj =0;recHeight<=imageHeight;hj++){
        recWidth = widthInit;
        for(ushort wi=0;recWidth<=imageWidth;wi++){                    //size of rectangle : (widthInit+4*wi)*(heightInit+4*hj)
            ushort x = 0;
            ushort y = 0;
            for(ushort i=0;(y+recHeight)<=imageHeight;i++){
                x = 0;
                for(ushort j=0;(x+recWidth)<=imageWidth;j++){
                    Position p = {x,y};
                    Shape s = {recWidth,recHeight};
                    this->featureVector.push_back(Feature(A,s,p,this->integral));
                    this->featureVector.push_back(Feature(B,s,p,this->integral));
                    this->featureVector.push_back(Feature(C,s,p,this->integral));
                    this->featureVector.push_back(Feature(D,s,p,this->integral));
                    x +=incrementP;
                }
                y +=incrementP;
            }
            recWidth += incrementS;
        }
        recHeight += incrementS; 
    }

}

void Image::calFeatureByLines(int start, int end) {
    ushort imageHeight = this->data.size();
    ushort imageWidth = this->data[0].size();

    for (int w = widthInit; w <= imageWidth; w += incrementS){
        for (int h = heightInit; h <= imageHeight; h += incrementS){
            
            /*cal all feature vectors 
            *       {(x, y); (w, h)} such that "start <= x < end"
            */
            if (start%incrementP != 0) start = (incrementP - start%incrementP) + start;
            for (int x = start; x+w <= imageWidth && x < end; x += incrementP){
                for (int y = 0; y+h <= imageHeight; y += incrementP){
                    Position p = {x, y};
                    Shape s = {w, h};
                    this->featureVector.push_back(Feature(A,s,p,this->integral));
                    this->featureVector.push_back(Feature(B,s,p,this->integral));
                    this->featureVector.push_back(Feature(C,s,p,this->integral));
                    this->featureVector.push_back(Feature(D,s,p,this->integral));
                }
            }

        }
    }

}

void Image::initialize(){
    this->calIntegral();
    //this->calFeatureVector();
}

vector<vector<int> > & Image::getImageData(){
    return (this->data);
}

short Image::getImageClass(){
    return this->clacc;
}

vector<vector<int> > & Image::getImageIntegral(){
    return (this->integral);
}

vector<Feature> & Image::getFeatureVector(){
    return (this->featureVector);
}
