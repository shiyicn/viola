#ifndef IMAGE
#define IMAGE


#include <iostream>
#include <vector>
#include <cstdlib>
#include "feature.hpp"

using namespace std;

const ushort widthInit = 8;
const ushort heightInit = 8;
const ushort incrementP = 4;
const ushort incrementS = 4;

class Image {
 
    vector<vector<int> > data;
    short clacc;
    vector<vector<int> > integral;
    vector<Feature> featureVector;

    public:
        Image(string fname, short c);
        Image(vector<vector<int> > &data, short c);
        void calIntegral();
        void calFeatureVector();
        void initialize();
        vector<vector<int> > &getImageData();
        short getImageClass();
        vector<vector<int> > &getImageIntegral();
        vector<Feature> &getFeatureVector();
        void calFeatureByLines(int start, int end, vector<pair<int, int> > &couples);
        int sizeOfFeatures();
};

#endif
