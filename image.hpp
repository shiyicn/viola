#ifndef IMAGE
#define IMAGE


#include <iostream>
#include <vector>
#include <cstdlib>
#include "feature.hpp"

using namespace std;

class Image {
 
    vector<vector<int> > data;
    int clacc;
    vector<vector<int> > integral;
    vector<Feature> featureVector;

    public:
        Image(string fname, int c);
        Image(vector<vector<int> > &data, int c);
        void calIntegral();
        void calFeatureVector();
        void initialize();
        vector<vector<int> > &getImageData();
        int getImageClass ();
        vector<vector<int> > &getImageIntegral();
        vector<Feature> &getFeatureVector();

};

#endif