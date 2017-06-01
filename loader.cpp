/******* includes *******/
#include "loader.hpp"
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;

const char* POSITIVE = "pos";

const char* NEGATIVE = "neg";

const int POSITIVE_CLASS = 1;

const int NEGATIVE_CLASS = -1;

const char* TEST = "test";

const char* VALIDATION = "val";

const char* TRAIN = "train";

void load_dataset(vector<Image>& images, const char* path){
    
}

void list_files(vector<char*>& files, const char* path, const char* filter){
    DIR *dir;
    struct dirent *ent;
    //cout<<"Try to get the list of all files from : "<<path<<endl;
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

void list_files_by_name(vector<string>& files, const char* prefix, const char* path, int start, int end, const char* suffix){
	stringstream ss;
    for (int i=start; i<end; i+=1){

	ss.str("");
	ss << i;
	const char* num = ss.str().c_str();
	char img[strlen(suffix) + strlen(prefix) + strlen(path) + strlen(num)];
	strcpy(img, path);
	strcpy(img, prefix);
	strcat(img, num);
	strcat(img, suffix);
	string str = string(img);
	//cout<<img<<endl;
	files.push_back(str);
    }
}

void load_images(vector<Image>& images, const char* path) {

    // store the image vectors corresponding to filenames passed on command line
    vector<char *> files;
    //cout<<"Try to fetch files from : "<<path<<endl;
    list_files(files, path, ".txt");
 //   for (int c = 0; c < files.size(); c++){
    for (int c = 0; c < files.size(); c++){
        load_single_image(images, files[c], path);
    }
}

void load_images(vector<Image>& images, const char* path, int start, int end) {

    // store the image vectors corresponding to filenames passed on command line
    vector<string> files;
    //cout<<"Try to fetch files from : "<<path<<endl;
    list_files_by_name(files, "img_", path, start, end, ".txt");
 //   for (int c = 0; c < files.size(); c++){
    for (int c = 0; c < files.size(); c++){
        load_single_image(images, files[c].c_str(), path);
    }
}

void load_single_image(vector<Image>& images, const char* file, const char* path){
    
    int c = -10;
    if ((strstr(path, POSITIVE)) != NULL) {
        c = POSITIVE_CLASS;
    } else if((strstr(path, NEGATIVE)) != NULL) {
        c = NEGATIVE_CLASS;
    } else {
        cout<<"invalid dataset : "<<path<<endl;
        exit(-1);
    }
    //create load path
    char img_load[strlen(path)+strlen(file)];
    strcpy(img_load, path);
    strcat(img_load, file);
    //cout<<"load image : "<<img_load<<endl;
    vector<vector<int> > data = load_vector(img_load);
    //cout<<"Size of loaded vector : "<<data.size()<<" , "<<data[0].size()<<endl;
    vector<vector<double> > data_float;
    for (int i=0; i<data.size(); i+=1){
        vector<double> row;
        for(int j=0; j<data[0].size(); j+=1){
            row.push_back(data[i][j] / 255.0);
//cout<<data[i][j]<<endl;
        }
        data_float.push_back(row);
    }
    images.push_back(Image(data_float, c));
}

vector<vector<int> > load_vector(const char * file){
    ifstream inFile (file, ifstream::in);
    int w = -1;
    int h = -1;
    vector<vector<int> > data;
    if (inFile.is_open())
    {
        inFile>>w;
        inFile>>h;
        //cout<<"Size is : "<<w<<" , "<<h<<endl;
        int elt = -1;
	string line = "";
        for (int i=0; i<h; i+=1){
            vector<int> row;
            for (int j=0; j<w; j+=1){
		getline(inFile,line);
		elt = atoi(line.c_str());
//cout<<elt<<endl;
//                 if (inFile.getline()){
//                     cout<<"Error in reading element in ("<<i<<" , "<<j<<")\n";
//                     exit(-1);
//                 };

                row.push_back(((int) elt));
            }
            data.push_back(row);
        }
        inFile.close();
    }
    else
    {
        cout<<"Unable to open file"<<file<<endl;
        exit(-1);
    }
    return data;
}
