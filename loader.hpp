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

#ifdef POSITIVE
#define POSITIVE = "pos";
#endif

#ifdef NEGATIVE
#define NEGATIVE = "neg";
#endif

#ifdef POSITIVE_CLASS
#define POSITIVE_CLASS = 1;
#endif

#ifdef NEGATIVE_CLASS
#define NEGATIVE_CLASS = 0;
#endif

#ifdef TEST
#define TEST = "test;
#endif

#ifdef VALIDATION
#define VALIDATION = "val;
#endif

#ifdef TRAIN
#define TRAIN = "train";
#endif

using namespace std;

void load_images(vector<Image>& images, int argc, char** argv);
void load_single_image(vector<Image>& images, const char* file, const char* path);
vector<vector<int> > load_vector(const char * file);
void list_files(vector<char*>& files, const char* path, const char* filter);

#endif
