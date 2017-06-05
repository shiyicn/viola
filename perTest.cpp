#include "perTest.hpp"
#include <mpi.h>
#include "adaboost.hpp"
#include "loader.hpp"

const double theta_start = -0.01;
const double theta_inf = -0.007;
const double theta_end = 0.015;
const double theta_sup = 0.008;
const double theta_step_small = 0.0001;
const double theta_step_big = 0.005;

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
    double term = 0.0;
    for(int i=0;i<strong.size();i++){
        pre +=alpha[i]*strong[i].predictByImage(img);
        term +=alpha[i];
    }
    return pre/term;
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
        if((imgs[i].getImageClass()==1)&&(results[i-start]==1)) tp++;
    }
    return tp;
}

int getfpMPI(vector<Image>&imgs, vector<int> &results,int start,int end){
    int fp = 0;
    for(int i=start;i<end;i++){
        if((imgs[i].getImageClass()==-1)&&(results[i-start]==1)) fp++;
    }
    return fp;
}

int gettnMPI(vector<Image>&imgs, vector<int> &results,int start,int end){
    int tn = 0;
    for(int i=start;i<end;i++){
        if((imgs[i].getImageClass()==-1)&&(results[i-start]==-1)) tn++;
    }
    return tn;
}

int getfnMPI(vector<Image>&imgs, vector<int> &results,int start,int end){
    int fn = 0;
    for(int i=start;i<end;i++){
        if((imgs[i].getImageClass()==1)&&(results[i-start]==-1)) fn++;
    }
    return fn;
}

/*pair<double,double> evaluate(vector<Image> &imgs,vector<SimpleClassifier> & strong, vector<double>&alpha,double theta){
    vector<int>result;
    int TP,FP,TN,FN;
    for(int i=0;i<imgs.size();i++){
        result.push_back(predictMPI(imgs[i],strong,alpha));
    }
    TP = calTP(imgs,result);
    FP = calFP(imgs,result);
    TN = calTN(imgs,result);
    FN = calFN(imgs,result);
    return make_pair((double)FP/(FP+TN),(double)TP/(TP+FN));
}*/
//Get the information of the N first classifiers 
void getStrongInfo(Image & img,vector<SimpleClassifier> &strong, int num){
    ofstream myfile;
    myfile.open("result/strongInfo.txt");
    img.initialize();
    for(int i=0;i<num;i++){
        int index = strong[i].getIndex();
        Position p = img.getFeatureVector()[index].getPosition();
        Shape s = img.getFeatureVector()[index].getShape();
        Type t = img.getFeatureVector()[index].getType();

        myfile<<p.x<<' '<<p.y<<' '<<s.width<<' '<<s.height<<' '<<t<<endl;
    }
    myfile.close();
}

void evaluateROC(vector<Image> &imgs,vector<SimpleClassifier> &strong, vector<double>&alpha){
    vector<double>preValue;
    vector<int> result;
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    int TP,FP,TN,FN;
    int gTP,gFP,gTN,gFN;

    int num = imgs.size()/size;
    if((imgs.size() % size)!=0) num+=1;
    int start = num * rank;
    int end = ((start+num)>imgs.size())?imgs.size():(start + num);
    cout<<"Processus "<<rank<<" calcul images from "<<start<<" to "<<end<<endl;
    for(int i=start;i<end;i++){
        imgs[i].initialize();
       // cout<<"Image "<<i<<" initiaized"<<endl;
        preValue.push_back(predictImage(imgs[i],strong,alpha)); 
    }
    cout<<"Processus "<<rank<<" feature calcul finished"<<endl;

    /*if(rank==0){
        getStrongInfo(imgs[0],strong,10);
        cout<<"Strong classifier info saved"<<endl;
    }*/

    //compute the roc point coordinate and save
    
    vector<ROC> perf;
    double fpr,tpr;
    for(double theta=theta_start;theta<theta_end;){
        for(int i=0;i<preValue.size();i++){
            if(preValue[i]>=theta){
		    result.push_back(1);
		}
            else {
		result.push_back(-1); 
		}
        }
        TP = gettpMPI(imgs,result,start,end);
	//cout<<"tp for processus "<<rank<<" for theta "<<theta<<" is "<<TP<<endl;
        FP = getfpMPI(imgs,result,start,end);
	//cout<<"fp for processus "<<rank<<" for theta "<<theta<<" is "<<FP<<endl;
        TN = gettnMPI(imgs,result,start,end);
	//cout<<"tn for processus "<<rank<<" for theta "<<theta<<" is "<<TN<<endl;
        FN = getfnMPI(imgs,result,start,end);
	//cout<<"fn for processus "<<rank<<" for theta "<<theta<<" is "<<FN<<endl;
        MPI_Reduce(&TP, &gTP, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&FP, &gFP, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&TN, &gTN, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&FN, &gFN, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        if(rank==0){
            fpr = (double)gFP/(gFP+gTN);
            tpr = (double)gTP/(gTP+gFN);
            ROC t = {theta,fpr,tpr};
            perf.push_back(t);
            cout<<"Theta "<<theta<<" calcul completed"<<endl;
        }
        
        result.clear();
	if((theta>theta_inf)&&(theta<theta_sup)) theta +=theta_step_small;
	else theta +=theta_step_big;
    }
    if(rank==0){
            ofstream myfile;
            myfile.open("result/testPerf.txt");
            for(int i=0;i<perf.size();i++){
                myfile<<perf[i].theta<<' '<<perf[i].fpr<<' '<<perf[i].tpr<<'\n';
            }          
            myfile.close();
    }    
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
	
	cout<<" going to load images"<<endl;
	load_images(testSet,"test/pos/");
	load_images(testSet,"test/neg/", 0, 1500);
	cout<<" load finished"<<endl;
    vector<double>alpha;
    vector<SimpleClassifier> strongs;
    loadClassifier(strongs,alpha);
    cout<<"Strong classifier load success, to compute roc performance..."<<endl;
    //getStrongInfo(testSet[0],strongs,20);
    evaluateROC(testSet,strongs,alpha);
    /*if(taskid == 0){
        cout<<"Test performance : false positive rate: "<<perfor.first<<" true positive rate : "<<perfor.second<<endl;
    }*/
    if(taskid == 0){
        cout<<"ROC performance calculation finished"<<endl;
    }
    MPI_Finalize();

	


}
