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
	
	//load images to vector 
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
	//end loading images
	
	//image amount
	int nums = images.size();
	//image row nums
	int rows = images[0].getImageData().size();
	
	//store all (x, w) in couples
	vector<pair<int, int> > couples;
	for (int x = 0; x <= (rows-widthInit); x += incrementP){
		for (int w = widthInit; w <= (rows-x); w += incrementS){
			couples.push_back(make_pair(x, w));
		}
	}

	//size of set (x, w)
	int sz = couples.size();
	
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
	MPI_Scatter(sendbuf, 1, MPI_UNSIGNED_SHORT, &start, 1, MPI_UNSIGNED_SHORT, 0, MPI_COMM_WORLD);
	//get end index according to start index and interval size
	end = start + min((int) interval, sz - start);
	
	for (int i=0; i<nums; i+=1){
		//compute features from start to end
		images[i].calIntegral();
		images[i].calFeatureByLines(start, end, couples);
	}
	int szlocal = images[0].getFeatureVector().size()
	cout<<"Taskid : "<<taskid<<" computes from line "<<
	start<<" to "<<endl<<"Local features size : "<<szlocal<<endl;
	
	int sz = 0;
	MPI_Reduce(&szlocal, &sz, 1, MPI_INT,
               MPI_SUM, root, MPI_COMM_WORLD);

	if (taskid == root) {
		images[0].getFeatureVector().clear();
		images[0].calFeatureVector();
		int std = images[0].getFeatureVector().size();
		cout<<"Total features' size : "<<sz<<endl<<"Standard size : "<<std<<endl;
	}
	
	MPI_Finalize();
}
