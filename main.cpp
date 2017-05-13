
#include "image.hpp"
#include "feature.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    std::vector<std::vector<int> > data;

    for (int i = 0; i < 16; i++) {
        vector<int> row;
        for (int j = 0; j < 16; j++){
            row.push_back(1);
        }
        data.push_back(row);
    }

    cout<<"built image vector\n";

    Image img = Image(data, 1);
    img.initialize();
    //img.calIntegral();
    
    cout<<"built image vector\n";


   // Shape s = {8, 8};
    //Position p = {0, 0};
    //Feature f = Feature(A, s, p, img.getImageIntegral());
    vector<Feature> & fl = img.getFeatureVector();

    cout<<"feature vector size : "<<fl.size()<<endl;

}