#include <iostream>
#include <vector>
#include <cstdlib>

#include "image.hpp"
#include "simpleClassifier.hpp"
#include "feature.hpp"

int main() {
    vector<vector<int> > images;

    for (int i = 0; i < 16; i++) {
        vector<int> row;
        for (int j = 0; j < 16; j++){
            row.push_back(1);
        }
        images.push_back(row);
    }


}