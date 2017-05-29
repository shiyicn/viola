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

#ifndef POSITIVE
#define POSITIVE = "pos";
#endif

#ifndef NEGATIVE
#define NEGATIVE = "neg";
#endif

#ifndef POSITIVE_CLASS
#define POSITIVE_CLASS = 1;
#endif

#ifndef NEGATIVE_CLASS
#define NEGATIVE_CLASS = 0;
#endif

#ifndef TEST
#define TEST = "test";
#endif

#ifndef VALIDATION
#define VALIDATION = "val";
#endif

#ifndef TRAIN
#define TRAIN = "train";
#endif

using namespace std;

void load_images(vector<Image>& images, int argc, char** argv);
void load_single_image(vector<Image>& images, const char* file, const char* path);
vector<vector<int> > load_vector(const char * file);
void list_files(vector<char*>& files, const char* path, const char* filter);

#endif
