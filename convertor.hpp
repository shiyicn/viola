#ifdef CONVERTOR
#define CONVERTOR

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<vector<int> > load_vector(const char * file);
void save_vector(vector<vector<int> > &data, const char* file);
void list_files(vector<char*>& files, const char* path, const char* filter);

#endif
