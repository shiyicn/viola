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

    //genDistFeature(argc, argv, dir)

    std::vector<std::vector<int> > data;

    cout<<"image :"<<endl;
    for (int i = 0; i < 4; i++) {
        vector<int> row;
        for (int j = 0; j < 4; j++){
            row.push_back(i*4 + j + 1);
            cout<<(i*4 + j + 1)<<"\t";
        }
        cout<<endl;
        data.push_back(row);
    }

    Image img = Image(data, 1);
    img.initialize();
    //img.calIntegral();

    Shape s = {4, 4};
    Position p = {0, 0};
    Feature f = Feature(A, s, p, img.getImageIntegral());
    //cout<<"feature type A value : "<<f.getValue()<<endl;
    f = Feature(B, s, p, img.getImageIntegral());
    //cout<<"feature type B value : "<<f.getValue()<<endl;
    f = Feature(C, s, p, img.getImageIntegral());
    cout<<"feature type C value : "<<f.getValue()<<endl;
    f = Feature(D, s, p, img.getImageIntegral());
    //cout<<"feature type D value : "<<f.getValue()<<endl;
    //vector<Feature> & fl = img.getFeatureVector();

    //cout<<"feature vector size : "<<fl.size()<<endl;

}

void genDistFeature(int argc, char** argv, dir){

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
