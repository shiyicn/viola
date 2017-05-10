#include "image.hpp"


std::vector<std::vector<int> > Image::calIntegral(std::vector<std::vector<int> > image){
    int t;
    std::vector<std::vector<int> > res;
    for (int i = 0; i < image.size(); i+=1) {
        std::vector<int> row;
        for (int j = 0; j < image[i].size(); j+=1){
            t = image[i][j];
            if (j > 0) t += res[i][j-1];
            if (i > 0) t += res[i-1][j];
            if (i > 0 && j > 0) t -= res[i-1][j-1];
            row.push_back(t);
        }
        res.push_back(row);
    }
    return res;
}

