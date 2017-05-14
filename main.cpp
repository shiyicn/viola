#include "image.hpp"
#include "feature.hpp"
#include "simpleClassifier.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
	

	/**
	* initialize image data and assign tasks
	*/
	const int root = 0;

	int numtasks, taskid;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if (taskid == 0) cout<<"Assigned tasks"<<endl;
	
	/*
	//get image directory from command line
	const dir = argv[1];
	
	//load images from directory "dir"
	vector<Image> images = load(dir);
	//get images amount
	*/
	
	//create fake images
	
	vector<Image> images;
	vector<vector<int> > fake;
	for (int i = 0; i< 112; i+=1){
		vector<int> row;
		for (int j=0; j< 92; j+=1) {
			row.push_back(1);
		}
		fake.push_back(row);
	}
	Image image = Image(fake, 1);
	
	for(int i = 0; i<100; i+=1){
		images.push_back(image);
	}
	
	//image amount
	int nums = images.size();
	//image row nums
	int rows = images[0].getImageData().size();

	int sz = 0;
	
	// the root decides how may rows will be handled by each of the
	// processors, and MPI_Scatters its decision
	unsigned short sendbuf[numtasks];
	unsigned short interval = (ushort) rows/numtasks;
	if(rows%numtasks != 0) interval += 1;
	for(unsigned short i=0; i<numtasks; i+=1){
		sendbuf[i] = i * interval;
	}
	
	unsigned short start = -1;
	unsigned short end = -1;
	
	//send start index for every processor
	MPI_Scatter(sendbuf, 1, MPI_UNSIGNED_SHORT, &start, 1, MPI_UNSIGNED_SHORT, 0, MPI_COMM_WORLD);
	//get end index according to start index and interval size
	end = start + min((int) interval, rows - interval);
	cout<<"Taskid : "<<taskid<<" computes from line "<<
		start<<" to "<<end<<endl;
	
	for (int i=0; i<nums; i+=1){
		//compute features from start to end
		images[i].calIntegral();
		images[i].calFeatureByLines(start, end);
	}
	int sum = images[0].getFeatureVector().size();
	
	MPI_Reduce(&sum, &sz, 1, MPI_INT,
               MPI_SUM, root, MPI_COMM_WORLD);

	if (taskid == root) {cout<<"total size : "<<sz<<endl;}
	
	MPI_Finalize();
}
