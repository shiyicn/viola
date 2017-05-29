#ifndef LOADER
#define LOADER

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>

#include "image.hpp"

const char* POSITIVE = "pos";

const char* NEGATIVE = "neg";

const int POSITIVE_CLASS = 1;

const int NEGATIVE_CLASS = 0;

const char* TEST = "test";

const char* VALIDATION = "val";

const char* TRAIN = "train";

using namespace std;

void load_images(vector<Image>& images, int argc, char** argv);
void load_single_image(vector<Image>& images, const char* file, const char* path);
vector<vector<int> > load_vector(const char * file);
void list_files(vector<char*>& files, const char* path, const char* filter);

#endif
