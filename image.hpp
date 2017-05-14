#ifndef IMAGE
#define IMAGE


#include <iostream>
#include <vector>
#include <cstdlib>
#include "feature.hpp"

using namespace std;

class Image {
 
    vector<vector<int> > data;
    short clacc;
    vector<vector<int> > integral;
    vector<Feature> featureVector;

    public:
        Image(string fname, short c);
        Image(vector<vector<int> > &data, short c);
        void calIntegral();
        //void calFeatureVector();
        void initialize();
        vector<vector<int> > &getImageData();
        short getImageClass ();
        vector<vector<int> > &getImageIntegral();
        vector<Feature> &getFeatureVector();
        void calFeatureByLines(int start, int end);

};

#endif
