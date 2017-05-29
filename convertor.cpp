#include "convertor.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <string>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char** argv){
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
        try {
                //load image with CImg
                CImg<unsigned char> image(path);
                int w = image.width();
                int h = image.height();
                int d = image.depth();
                cout<<"Load image : <"<<path<<"> with size "<<w<<"*"<<h<<"*"<<"d"<<endl;
                if (d != 1)
                    cout<<"The depth of image : <"<<path<<"> is not equal to 1"<<endl;
                int count = 0;
                vector<int> col;
                vector<vector<int> > data;
                // need more details about the mechanism of CImg library
                for (CImg<unsigned char>::iterator it = image.begin(); it != image.end(); ++it, ++count) {
                    col.push_back(*it);
                    if (count % w == (w - 1)) {
                        //push a colon to data vector
                        data.push_back(col);
                        col.clear();
                    }
                }
                string file = "img_" + i + ".txt"
                save_vector(data, file)
        } catch (CImgException& e) {
            // some errors in reading the image
            cerr << argv[0] << ": CImg error while reading " << argv[c] << endl;
            ret = 2;
            exit(ret);
        }
    }
}

void save_vector(vector<vector<int> > &data, const char* file){
    //create output stream
    ofstream outFile;
    outFile.open(file);
    if (outFile.is_open())
    {
        //write the size to 
        outFile<<data[0].size()<<endl;
        outFile<<data.size()<<endl;
        for (int i=0; i<data.size(); i+=1){
            for (int j=0; j<data.size(); j+=1){
                outFile<<data[i][j]<<endl;
            }
        }
    }
    else cout<<"Unable to open file : "<<file<<endl;
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

void load_single_image(vector<Image>& images, const char* path){
    std::ofstream outFile;
    outFile.open("my_file.txt");

    //load image with CImg
    CImg<unsigned char> image(path);
    int w = image.width();
    int h = image.height();
    int d = image.depth();
    cout<<"Load image : <"<<path<<"> with size "<<w<<"*"<<h<<"*"<<"d"<<endl;
    if (d != 1)
        cout<<"The depth of image : <"<<path<<"> is not equal to 1"<<endl;
    int count = 0;
    vector<double> col;
    vector<vector<double> > data;
    // need more details about the mechanism of CImg library
    for (CImg<unsigned char>::iterator it = image.begin(); it != image.end(); ++it, ++count) {
        col.push_back(*it / 255.0);
        if (count % w == (w - 1)) {
            //push a colon to data vector
            data.push_back(col);
            col.clear();
        }
    }

    int c = 1;
    images.push_back(Image(data, c));
}