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
 
    vector<vector<double> > data;
    int clacc;
    vector<vector<double> > integral;
    vector<Feature> featureVector;

    public:
        Image(string fname, short c);
        Image(vector<vector<double> > &data, int c);
        void calIntegral();
        void calFeatureVector();
        void initialize();
        vector<vector<double> > &getImageData();
        int getImageClass();
        vector<vector<double> > &getImageIntegral();
        vector<Feature> &getFeatureVector();
        void calFeatureByLines(int start, int end, vector<pair<int, int> > &couples);
        int sizeOfFeatures();
};

#endif
