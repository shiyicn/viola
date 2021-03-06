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

void list_files(vector<char*>& files, const char* path, const char* filter){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (strstr(ent->d_name, filter) != NULL) {
                char* img = new char[strlen(ent->d_name)];
                strcpy(img, ent->d_name);
                files.push_back(img);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
}

void save_vector(vector<vector<int> > &data, const char* file, const char* path){
    //create output stream
    char file_save[strlen(file)+strlen(path)];
    strcpy(file_save, path);
    strcat(file_save, file);
    ofstream outFile;
    outFile.open(file_save);
    cout<<"save file : "<<file_save<<endl;
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

void load_vector(vector<vector<int> >& data, const char* file){
    ifstream inFile (file, ios::in|ios::binary|ios::ate);
    int w = -1;
    int h = -1;
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
}

int main(int argc, char** argv){
    int ret = -1;
    // examine calling command line
    int length = 2;
    //char* folds[] = {"test/pos/", "test/neg/", "val/pos/", "val/neg/", "train/pos/", "train/neg/"};
    char* folds[] = {"train/pos/", "train/neg/"};
    for (int index = 0; index < length; index += 1){
        cout<<"load images from : "<<folds[index]<<endl;
        int path_len = strlen(folds[index]);
        vector<char*> files;
        list_files(files, folds[index], "jpg");

        // store the image vectors corresponding to filenames passed on command line
        stringstream ss;
        for (int c = 0; c < files.size(); c++){
            try {
                //load image with CImg
                char file_load[strlen(files[c])+path_len];
                strcpy(file_load, folds[index]);
                strcat(file_load, files[c]);
                CImg<unsigned char> image(file_load);
                int w = image.width();
                int h = image.height();
                int d = image.depth();
                //cout<<"Load image : <"<<files[c]<<"> with size "<<w<<"*"<<h<<"*"<<d<<endl;
                if (d != 1)
                    //cout<<"The depth of image : <"<<files[c]<<"> is not equal to 1"<<endl;
                int count = 0;
                ss.str("");
                ss << "img_" << c << ".txt";
                string str = ss.str();
                const char* file = str.c_str();
                cout<<"build txt file : "<<file<<endl;
                //save_vector(data, file, folds[index]);
                char file_save[strlen(file)+strlen(folds[index])];
                strcpy(file_save, folds[index]);
                strcat(file_save, file);
                ofstream outFile;
                outFile.open(file_save);
                if (outFile.is_open()){
                    // save image size
                    outFile<<w<<endl;
                    outFile<<h<<endl;
                    // need more details about the mechanism of CImg library
                    for (CImg<unsigned char>::iterator it = image.begin(); it != image.end(); ++it) {
			int tmp = (int) *it;
                        outFile<<tmp<<endl;
                    }
                    outFile.close();
                } else cout<<"Unable to open file : "<<file<<endl;
            } catch (CImgException& e) {
                // some errors in reading the image
                cerr << argv[0] << ": CImg error while reading " << files[c] << endl;
                ret = 2;
                exit(ret);
            }
        }
    }
}


