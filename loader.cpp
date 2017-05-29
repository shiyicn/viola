/******* includes *******/
#include "loader.hpp"

using namespace std;

void load_images(vector<Image>& images, int argc, char** argv) {

    int ret = -1;
    // examine calling command line
    if (argc < 2) {
        cout << argv[0] << ": syntax error: syntax is:" << endl;
        cout << "   " << argv[0] << " imgfile1.jpg imgfile2.jpg ..." << endl;
        ret = 1;
        exit(ret);
    }

    // store the image vectors corresponding to filenames passed on command line
    for (int c = 0; c < argc; c++){
        load_single_image(images, argv[c]);
    }
}

void load_single_image(vector<Image>& images, const char* path){
    int c = 1;
    vector<vector<int> > data = load_vector(path);
    vector<vector<double> > data_float;
    for (int i=0; i<data.size(); i+=1){
        vector<double> row;
        for(int j=0; j<data[0].size(); j+=1){
            row.push_back(data[i][j] / 255.0);
        }
        data_float.push_back(row);
    }
    images.push_back(Image(data_float, c));
}

vector<vector<int> > load_vector(const char * file){
    ifstream inFile;
    inFile.open(file);
    int w = -1;
    int h = -1;
    vector<vector<int> > data;
    if (inFile.is_open())
    {
        if (!inFile>>w || !inFile>>h) {
            cout<<"Error in reading width and height infos\n";
            exit(-1);
        }
        int elt = -1;
        for (int i=0; i<w; i+=1){
            vector<int> row;
            for (int j=0; j<h; j+=1){
                if (!inFile>>elt){
                    cout<<"Error in reading element in ("<<i<<" , "<<j<<")\n";
                    exit(-1);
                };
                row.push_back(elt);
            }
            data.push_back(row);
        }
    }
    else
    {
        cout<<"Unable to open file"<<file<<endl;
        exit(-1);
    }
    return data;
}