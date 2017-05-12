#ifndef IMAGE
#define IMAGE


#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


class Image {
 
    vector<vector<int> > data;
    vector<vector<int> > integral;
    //std::vector<Feature> featureVector; 
    int c;

    //Image(string fname, int c);

    public:
        Image(std::vector<std::vector<int> > &data, int c);

        vector<vector<int> > calIntegral();
        //vector<Feature> calFeatureVector(vector<vector<int> > integral, int incr, int size);
    
};

#endif