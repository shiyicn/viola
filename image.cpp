#include "image.hpp"
#include "util.hpp"

#include "feature.hpp"
using namespace std;
typedef unsigned short ushort;

Image::Image(vector<vector<double> > &data, int c){
    this->data = data;
    this->clacc = c;
}

void Image::calIntegral(){ 
    double t;
    //vector<vector<int> > res;
    for (int i = 0; i < data[0].size(); i+=1) {
        vector<double> col;
        for (int j = 0; j < data.size(); j+=1){
            t = data[j][i];
            if (j > 0) t += col[j-1];
            if (i > 0) t += integral[j][i-1];
            if (i > 0 && j > 0) t -= integral[j-1][i-1];
            col.push_back(t);
        }
        this->integral.push_back(col);
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

void Image::calFeatureByLines(int start, int end, vector<pair<int, int> > &couples) {
  ushort imageHeight = this->data.size();
  ushort imageWidth = this->data[0].size();
	cout<<"image heigth "<<imageHeight<<endl;
	cout<<"intergal : "<<this->integral.size()<<"  "<<this->integral[0].size()<<endl;

  int w, x;
  for (int i = start; i < end; i += 1) {
    //decode x and w infomations
    //(100*x+w) -> (x, w) -> (incrementP * x, incrementS * w + widthInit)
    x = couples[i].first;
    w = couples[i].second;
    int count = 0;
    for (int h = heightInit; h <= imageHeight; h += incrementS) {
      for (int y = 0; y <= imageHeight - h; y += incrementP) {
	count += 1;
        Position p = {x, y};
	Shape s = {w, h};
	//cout<<"Four features."<<endl;
	cout<<x<<" "<<y<<" "<<w<<" "<<h<<endl;
        this->featureVector.push_back(Feature(A, s, p, this->integral));
        this->featureVector.push_back(Feature(B, s, p, this->integral));
        this->featureVector.push_back(Feature(C, s, p, this->integral));
        this->featureVector.push_back(Feature(D, s, p, this->integral));
      }
    }
  }
}

void Image::initialize(){
    this->calIntegral();
    this->calFeatureVector();
}

vector<vector<double> > & Image::getImageData(){
    return (this->data);
}

int Image::getImageClass(){
    return this->clacc;
}

vector<vector<double> > & Image::getImageIntegral(){
    return (this->integral);
}

vector<Feature> & Image::getFeatureVector(){
    return (this->featureVector);
}
