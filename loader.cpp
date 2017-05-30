/******* includes *******/
#include "loader.hpp"

using namespace std;

const char* POSITIVE = "pos";

const char* NEGATIVE = "neg";

const int POSITIVE_CLASS = 1;

const int NEGATIVE_CLASS = 0;

const char* TEST = "test";

const char* VALIDATION = "val";

const char* TRAIN = "train";

void load_dataset(vector<Image>& images, const char* path){
    
}

void list_files(vector<char*>& files, const char* path, const char* filter){
    DIR *dir;
    struct dirent *ent;
    cout<<"Try to get the list of all files from : "<<path<<endl;
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

void load_images(vector<Image>& images, const char* path) {

    // store the image vectors corresponding to filenames passed on command line
    vector<char*> files;
    cout<<"Try to fetch files from : "<<path<<endl;
    list_files(files, path, "txt");
    for (int c = 0; c < files.size(); c++){
        load_single_image(images, files[c], path);
    }
}

void load_single_image(vector<Image>& images, const char* file, const char* path){
    
    int c = -1;
    if ((strstr(path, POSITIVE)) != NULL) {
        cout<<"create positive images from : "<<path<<endl;
        c = POSITIVE_CLASS;
    } else if((strstr(path, NEGATIVE)) != NULL) {
        cout<<"create negative images from : "<<path<<endl;
        c = NEGATIVE_CLASS;
    } else {
        cout<<"invalid dataset : "<<path<<endl;
        exit(-1);
    }
    //create load path
    char img_load[strlen(path)+strlen(file)];
    strcpy(img_load, path);
    strcat(img_load, file);
    vector<vector<int> > data = load_vector(img_load);
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
