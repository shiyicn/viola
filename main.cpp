
#include "image.hpp"
#include "feature.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    std::vector<std::vector<int> > data;

    cout<<"image :"<<endl;
    for (int i = 0; i < 4; i++) {
        vector<int> row;
        for (int j = 0; j < 4; j++){
            row.push_back(i*4 + j + 1);
            cout<<(i*4 + j + 1)<<"\t";
        }
        cout<<endl;
        data.push_back(row);
    }

    Image img = Image(data, 1);
    img.initialize();
    //img.calIntegral();

    Shape s = {4, 4};
    Position p = {0, 0};
    Feature f = Feature(A, s, p, img.getImageIntegral());
    //cout<<"feature type A value : "<<f.getValue()<<endl;
    f = Feature(B, s, p, img.getImageIntegral());
    //cout<<"feature type B value : "<<f.getValue()<<endl;
    f = Feature(C, s, p, img.getImageIntegral());
    cout<<"feature type C value : "<<f.getValue()<<endl;
    f = Feature(D, s, p, img.getImageIntegral());
    //cout<<"feature type D value : "<<f.getValue()<<endl;
    //vector<Feature> & fl = img.getFeatureVector();

    //cout<<"feature vector size : "<<fl.size()<<endl;

}