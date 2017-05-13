#include "image.hpp"

using namespace std;
typedef unsigned short ushort;

const ushort widthInit = 8;
const ushort heightInit = 8;
const ushort increment = 4;

Image::Image(vector<vector<int> > &data, int c){
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
    int imageHeight = this->data.size();
    int imageWidth = this->data[0].size();
    for(ushort hj =0;(heightInit+4*hj)<=imageHeight;hj++){
        for(ushort wi=0;(widthInit+4*wi)<=imageWidth;wi++){                    //size of rectangle : (widthInit+4*wi)*(heightInit+4*hj)

        }
    }

}

void Image::initialize(){

}

vector<vector<int> > & Image::getImageData(){
    return (this->data);
}

int Image::getImageClass(){
    return this->clacc;
}

vector<vector<int> > & Image::getImageIntegral(){
    return (this->integral);
}

vector<Feature> & Image::getFeatureVector(){
    return (this->featureVector);
}