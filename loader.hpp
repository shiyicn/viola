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

using namespace std;

void load_images(vector<Image>& images, const char* path);
void load_single_image(vector<Image>& images, const char* file, const char* path);
vector<vector<int> > load_vector(const char * file);
void list_files(vector<char*>& files, const char* path, const char* filter);
void load_images(vector<Image>& images, const char* path, int start, int end);

#endif
