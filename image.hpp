#ifndef IMAGE
#define IMAGE

#include <iostream>
#include <vector>
#include <cstdlib>

class Image {
    std::vector<std::vector<int> > data;
    std::vector<std::vector<int> > integral;
    int c;

    Image(std::string fname, int c);

    std::vector<std::vector<int> > calIntegral(std::vector<std::vector<int> > image);
    std::vector<int> calFeatureVector(std::vector<std::vector<int> > integral, int incr, int size);
    
};

#endif