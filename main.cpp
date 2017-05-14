#include "image.hpp"
#include "feature.hpp"
#include "simpleClassifier.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>

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
	
	if (argc != 3) {
		if (taskid == root) {
			std::cerr << "Usage : " << argv[0]
			<< " imagefile"
			<< std::endl;
		} else { }
		MPI_Finalize();
		return 1;
	}
	
	/*
	//get image directory from command line
	const dir = argv[1];
	
	//load images from directory "dir"
	vector<Image> images = load(dir);
	//get images amount
	*/

	//create fake images
	vector<Images> images;
	vector<vector<int> > fake;
	for (int i = 0; i< 112; i+=1){
		vector<int> row;
		for (int j=0; j< 92; j+=1) {
			row.push_back(1);
		}
		fake.push_back(row);
	}
	Image image = Image(fake, 1);
	
	for(int i = 0; i<20; i+=1){
		images.push_back(image);
	}
	
	ushort rows = images.size();
	
	// the root decides how may rows will be handled by each of the
	// processors, and MPI_Scatters its decision
	unsigned int sendbuf[numtasks];
	ushort interval = rows/numtasks;
	if (row%numtasks != 0) interval += 1;
	for(int i=0; i<numtasks-1; i+=1){
		sendbuf[i] = i * interval;
	}
	
	int start = -1;
	int end = -1;
	
	//send start index for every processor
	MPI_Scatter(sendbuf, 1, MPI_INT, &start, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//get end index according to start index and interval size
	end = start + min(interval, rows - start);
	cout<<"Taskid : "<<taskid<<" computes from lines "<<
		start<<" to "<<end;
	for (int i=0; i<images.size(); i+=1){
		//compute features from start to end
		images[i].calFeatureByLines(start, end);
	}
}
