#include "convertor.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

void list_files(vector<char*>& files const char* path, const char* filter){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (strstr(ent->d_name, filter) != NULL) {
                char* img = new char[strlen(ent->d_name)];
                strcpy(img, ent->d_name);
                files.push_back()
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
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
        outFile.close();
    }
    else cout<<"Unable to open file : "<<file<<endl;
}

vector<vector<int> > load_vector(const char* file){
    ifstream inFile (file, ios::in|ios::binary|ios::ate);
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

int main(int argc, char** argv){
    int ret = -1;
    // examine calling command line
    cout<<"load images from : "<<argv[1]<<endl;
    vector<char*> files;
    list_files(files, argv[1], "jpg");

    // store the image vectors corresponding to filenames passed on command line
    stringstream ss;
    for (int c = 0; c < files.size(); c++){
        try {
            //load image with CImg
            CImg<unsigned char> image(files[c]);
            int w = image.width();
            int h = image.height();
            int d = image.depth();
            cout<<"Load image : <"<<files[c]<<"> with size "<<w<<"*"<<h<<"*"<<"d"<<endl;
            if (d != 1)
                cout<<"The depth of image : <"<<files[c]<<"> is not equal to 1"<<endl;
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
            int a = 10;
            ss.clear();
            ss << "img_" << c << ".txt";
            string str = ss.str();
            const char* file = str.c_str();
            save_vector(data, file);
        } catch (CImgException& e) {
            // some errors in reading the image
            cerr << argv[0] << ": CImg error while reading " << files[c] << endl;
            ret = 2;
            exit(ret);
        }
    }
}


