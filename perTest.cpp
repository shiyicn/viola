#include "perTest.hpp"
#include <mpi.h>
#include "adaboost.hpp"

int predict(Image &img,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta){
    double pre,term;
    for(int i=0;i<strong.size();i++){
        pre +=alpha[i]*strong[i].predictByImage(img);
        term +=alpha[i];
    }
    term *= theta;
    term -=1;
    if(pre >= term) return 1;
    else return -1;
}



int calTP(vector<Image> &imgs, vector<int> &results){
    int tp = 0;
    for(int i=0;i<imgs.size();i++){
        if((imgs[i].getImageClass()==1)&&(results[i]==1)) tp++;
    }
    return tp;
}

int calFP(vector<Image> &imgs, vector<int> &results){
    int fp = 0;
    for(int i=0;i<imgs.size();i++){
        if((imgs[i].getImageClass()==-1)&&(results[i]==1)) fp++;
    }
    return fp;
}

int calTN(vector<Image> &imgs, vector<int> &results){
    int tn = 0;
    for(int i=0;i<imgs.size();i++){
        if((imgs[i].getImageClass()==-1)&&(results[i]==-1)) tn++;
    }
    return tn;
}

int calFN(vector<Image> &imgs, vector<int> &results){
    int fn = 0;
    for(int i=0;i<imgs.size();i++){
        if((imgs[i].getImageClass()==1)&&(results[i]==-1)) fn++;
    }
    return fn;
}

pair<double,double> evaluate(vector<Image> &imgs,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta){
    vector<int>result;
    int TP,FP,TN,FN;
    for(int i=0;i<imgs.size();i++){
        result.push_back(predict(imgs[i],strong,alpha,theta));
    }
    TP = calTP(imgs,result);
    FP = calFP(imgs,result);
    TN = calTN(imgs,result);
    FN = calFN(imgs,result);
    return make_pair((double)FP/(FP+TN),(double)TP/(TP+FN));
}


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

    vector<Image> testSet;

    load_images(testSet,"test/pos/");
    load_images(testSet,"test/neg/");

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
    int inte = sz/numtasks;
    if(sz/numtasks !=0) inte +=1;
    int start = taskid * inte;
    int end = ((start+inte)>sz)?sz:(start+inte);

    cout<<"Taskid : "<<taskid<<" computes from line "<<start<<" to "<<end<<endl;
    for (int i=0; i<nums; i+=1){
 		//compute features from start to end
 		images[i].calIntegral();
 		images[i].calFeatureByLines(start, end, couples);
 	}

    int szlocal = images[0].getFeatureVector().size();
	cout<<"Local features size : "<<szlocal<<endl;

    vector<double>alpha;
    vector<SimpleClassifier> strongs;
    loadClassifier(strongs,alpha);
	


}
