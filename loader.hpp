#ifndef LOADER
#define LOADER

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <string>

#include "image.hpp"

#include "CImg.h"

using namespace std;

void load_images(vector<Image>& images, int argc, char** argv);
void load_single_image(vector<Image>& images, const char* path);

#endif
