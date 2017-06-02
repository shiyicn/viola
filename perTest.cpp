#include "perTest.hpp"
#include <mpi.h>
#include "adaboost.hpp"

const double theta_start = -1.0;
const double theta_end = 1.0;
const double theta_step = 0.02;

double predictMPI(Image &img,vector<SimpleClassifier> & strong, vector<double>&alpha){
    double localPre=0.0;
    double localAlpha=0.0;
    double pre=0.0;
    double term=0.0;
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(int i=0;i<strong.size();i++){
        pair<int,int> indexInfo = indexGlobal2Local(strong[i].getIndex(),size);
        int taskid = indexInfo.first;
        int localIndex = indexInfo.second;
        if(rank==taskid){
            strong[i].setIndex(localIndex);
            localPre += alpha[i]*strong[i].predictByImage(img);
            localAlpha +=alpha[i];
        }
        //pre +=alpha[i]*strong[i].predictByImage(img);
        //term +=alpha[i];
    }
    MPI_Reduce(&localPre, &pre, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&localAlpha,&term,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    //term *= theta;
    //term -=1;
   // if(pre >= term) return 1;
   // else return -1;
   return pre/term;
}


double  predictImage(Image & img, vector<SimpleClassifier> &strong, vector<double> &alpha){
    double pre = 0.0;
    double alpha = 0.0;
    for(int i=0;i<strong.size();i++){
        pre +=alpha[i]*strong[i].predictByImage(img);
        alpha +=alpha[i];
    }
    return pre/alpha;

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

int gettpMPI(vector<Image>&imgs, vector<int> &results,int start,int end){
    int tp = 0;
    for(int i=start;i<end;i++){
        if((imgs[i].getImageClass()==1)&&(results[i]==1)) tp++;
    }
    return tp;
}

int getfpMPI(vector<Image>&imgs, vector<int> &results,int start,int end){
    int fp = 0;
    for(int i=start;i<end;i++){
        if((imgs[i].getImageClass()==-1)&&(results[i]==1)) fp++;
    }
    return fp;
}

int gettnMPI(vector<Image>&imgs, vector<int> &results,int start,int end){
    int tn = 0;
    for(int i=start;i<end;i++){
        if((imgs[i].getImageClass()==-1)&&(results[i]==-1)) tn++;
    }
    return tn;
}

int getfnMPI(vector<Image>&imgs, vector<int> &results,int start,int end){
    int fn = 0;
    for(int i=start;i<end;i++){
        if((imgs[i].getImageClass()==1)&&(results[i]==-1)) fn++;
    }
    return fn;
}

pair<double,double> evaluate(vector<Image> &imgs,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta){
    vector<int>result;
    int TP,FP,TN,FN;
    for(int i=0;i<imgs.size();i++){
        result.push_back(predictMPI(imgs[i],strong,alpha,theta));
    }
    TP = calTP(imgs,result);
    FP = calFP(imgs,result);
    TN = calTN(imgs,result);
    FN = calFN(imgs,result);
    return make_pair((double)FP/(FP+TN),(double)TP/(TP+FN));
}

void evaluateROC(vector<Image> &imgs,vector<SimpleClassifier> &strong, vector<double>&alpha){
    vector<double>preValue;
    vectoe<int> result;
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    int TP,FP,TN,FN;

    int num = imgs.size()/size;
    if((imgs.size() % size)!=0) num+=1;
    int start = num * rank;
    int end = ((start+num)>imgs.size())?imgs.size():(start + num);
    for(int i=start;i<end;i++){
        imgs[i].initialize();
        preValue.push_back(predictImage(imgs[i],strong,alpha)); 
    }

    //compute the roc point coordinate and save
    ofstream myfile;
    myfile.open("result/testPerf.txt");
    for(double theta=theta_start;theta<theta_end;theta = theta + theta_step){
        for(int i=0;i<preValue.size();i++){
            if(preValue[i]>=theta) result.push_back(1);
            else result.push_back(-1); 
        }
        TP = gettpMPI(imgs,result,start,end);
        FP = getfpMPI(imgs,result,start,end);
        TN = gettnMPI(imgs,result,start,end);
        FN = getfnMPI(imgs,result,start,end);
        double fpr = (double)FP/(FP+TN);
        double tpr = (double)TP/(TP+FN);
        myfile<<theta<<'\t'<<fpr<<'\t'<<tpr<<'\n';
        result.clear();
    }
    myfile.close();
    
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
	/*int nums = images.size();
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
	cout<<"Local features size : "<<szlocal<<endl;*/

    vector<double>alpha;
    vector<SimpleClassifier> strongs;
    loadClassifier(strongs,alpha);
    evaluateROC(testSet,strongs,alpha);
    /*if(taskid == 0){
        cout<<"Test performance : false positive rate: "<<perfor.first<<" true positive rate : "<<perfor.second<<endl;
    }*/
    if(taskid == 0){
        cout<<"ROC performance calculation finished"<<endl;
    }
    MPI_Finalize();

	


}
