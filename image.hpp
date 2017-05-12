#ifndef IMAGE
#define IMAGE


#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Image {
 
    vector<vector<int> > data;
    int c;

    public:
        Image(string fname, int c);
        Image(vector<vector<int> > &data, int c);
        vector<vector<int> > calIntegral();
};

#endif