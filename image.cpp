#include "image.hpp"

using namespace std;

Image::Image(vector<vector<int> > &data, int c){
    this->data = data;
    this->c = c;
}

vector<vector<int> > Image::calIntegral(){
    int t;
    vector<vector<int> > res;
    for (int i = 0; i < data.size(); i+=1) {
        vector<int> row;
        for (int j = 0; j < data[i].size(); j+=1){
            t = data[i][j];
            if (j > 0) t += row[j-1];
            if (i > 0) t += res[i-1][j];
            if (i > 0 && j > 0) t -= res[i-1][j-1];
            row.push_back(t);
        }
        res.push_back(row);
    }
    return res;
}