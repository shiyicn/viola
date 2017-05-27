/******* includes *******/
#include "loader.hpp"

using namespace std;
using namespace cimg_library;

void load_images(vector<Image>& images, int argc, char** argv) {

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
            load_single_image(images, argv[c])
        } catch (CImgException& e) {
            // some errors in reading the image
            cerr << argv[0] << ": CImg error while reading " << argv[c] << endl;
            ret = 2;
            exit(ret);
        }
    }
}

void load_single_image(vector<Image>& images, const string& path){
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
            // push a colon to data vector
            data.push_back(col);
            col.clear();
        }
    }

    int c = 1;
    images.push_back(new Image(data, c));
}