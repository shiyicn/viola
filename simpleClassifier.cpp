#include "simpleClassifier.hpp"
#include "mpi.h"
#include <iostream>

void genDistFeature(int argc, char** argv){

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
    
    //get image directory from command line
    const dir = argv[1];

    //load images from directory "dir"
    vector<Image> images = load(dir);
    //get images amount
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
    for (int i=0; i<images.size(); i+=1){
        //compute features from start to end
        images[i].calFeatureByLines(start, end);
    }
}

SimpleClassifier::SimpleClassifier(double w_0,double w_1){
    this->w_0 = w_0;
    this->w_1 = w_1;
}

double SimpleClassifier::getW0(){
    return w_0;
}

double SimpleClassifier::getW1(){
    return w_1;
}

Type SimpleClassifier::getType(){
    return this->type;
}

Shape SimpleClassifier::getShape(){
    return this->shape;
}

Position SimpleClassifier::getPosition(){
    return this->position;
}

short SimpleClassifier::predict(Feature &f){
    this->type = f.getType();
    this->shape = f.getShape();
    this->position = f.getPosition();
    double predit = w_0 * f.getValue() + w_1;
    return (predit>=0)?1:-1;
}


