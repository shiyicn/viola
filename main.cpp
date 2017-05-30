#include "image.hpp"
#include "feature.hpp"
#include "simpleClassifier.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include "loader.hpp"
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
	
	//load images to vector 
	vector<Image> images;
	load_images(images, "test/pos/");

	//end loading images
	
	//image amount
	int nums = images.size();
	//image row nums
	int cols = images[0].getImageData()[0].size();
	
	//store all (x, w) in couples
	vector<pair<int, int> > couples;
	for (int x = 0; x <= (cols-widthInit); x += incrementP){
		for (int w = widthInit; w <= (cols-x); w += incrementS){
			couples.push_back(make_pair(x, w));
		}
	}

	//size of set (x, w)
	int sz = couples.size();
	if (taskid == root){
		cout<<"Size of all images : "<<nums<<endl;
		cout<<"Size of Image : "<<images[0].getImageData().size()<<" , "<<images[0].getImageData()[0].size()<<endl;
		cout<<"Size of all couples : "<<sz<<endl;
	}
	
	// the root decides how may rows will be handled by each of the
	// processors, and MPI_Scatters its decision
	unsigned short sendbuf[numtasks];
	unsigned short interval = (ushort) sz/numtasks;
	if(sz%numtasks != 0) interval += 1;
	for(unsigned short i=0; i<numtasks; i+=1){
		sendbuf[i] = i * interval;
	}
	
	unsigned short start = -1;
	unsigned short end = -1;
	
	//send start index for every processor
	MPI_Scatter(&sendbuf, 1, MPI_UNSIGNED_SHORT, &start, 1, MPI_UNSIGNED_SHORT, 0, MPI_COMM_WORLD);
	//get end index according to start index and interval size
	end = start + interval;
	if (end > sz) end = sz;
	
	cout<<"Taskid : "<<taskid<<" computes from line "<<
	start<<" to "<<end<<endl;

 	for (int i=0; i<nums; i+=1){
 		//compute features from start to end
 		images[i].calIntegral();
 		images[i].calFeatureByLines(start, end, couples);
 	}
	int szlocal = images[0].getFeatureVector().size();
	cout<<"Local features size : "<<szlocal<<endl;
	
	int sum = 0;
	MPI_Reduce(&szlocal, &sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
	if (taskid == root) {
		cout<<"Size of feature vector is : "<<sum<<endl;
	}

	/*if (taskid == root) {
		images[0].getFeatureVector().clear();
		images[0].calFeatureVector();
		int std = images[0].getFeatureVector().size();
		cout<<"Total features' size : "<<sz<<endl<<"Standard size : "<<std<<endl;
	}*/
	
	MPI_Finalize();
}
