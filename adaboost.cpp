#include "adaboost.hpp"
#include <math.h>

#include <iostream>   // std::cout
#include <string>     // std::string, std::stod


const int Class_W0 = 0;
const int Class_W1 = 1;
const int Class_Index =2;
const int numCouple = 378;
const int numParCouple = 1012;


double errCal(Image & img,SimpleClassifier & classifier){
    return (classifier.predictByImage(img)==img.getImageClass())?0.0:1.0;
}

void getBestClassifier(double *lambda, vector<Image>& valSet, vector<SimpleClassifier> &classifiers, SimpleClassifier & best,double *err){
    double minErr = numeric_limits<double>::infinity();
    int index=0;
    for(int i=0;i<classifiers.size();i++){
        double errCur = 0.0;
        for(int j=0;j<valSet.size();j++){
		//cout<<"image class: "<<valSet[j].getImageClass()<<endl;
            errCur += lambda[j]*errCal(valSet[j],classifiers[i]);
		//cout<<" current locerr: "<<errCur<<endl;
        }
        if(errCur < minErr){
            index = i;
            minErr = errCur;

        }
    }
    best = classifiers[index];
    *err = minErr;
	//cout<<"min err: "<<minErr<<endl;
}

int indexLocal2Global(int localIndex, int rank, int size){
    int inte = numCouple / size;
    if(numCouple%size != 0) inte += 1;
    int numPre = rank * inte * numParCouple;
    return (numPre + localIndex);

}

pair<int,int> indexGlobal2Local(int globalIndex, int size){
    int numParPro = numCouple/size;
    if(numCouple/size !=0) numParPro +=1;
    numParPro *=numParCouple;
    int rank = globalIndex / numParPro;
    int localIndex = globalIndex % numParPro;
    return make_pair(rank,localIndex);
}


void strongClassifier(vector<Image> &valSet, vector<SimpleClassifier> &weaks, vector<SimpleClassifier>&strong, vector<double> &alphas, int N){
    int rank,nProcs;
    MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    double *lambda = new double[valSet.size()];
    double weightInit = 1.0/(double)valSet.size();

    for(int i=0;i<valSet.size();i++){               //initialize the weights
        lambda[i] = weightInit;
	//cout<<"Initial lambda : ------"<<i<<" ----- "<<lambda[i]<<endl;
    }

    for(int i=0;i<N;i++){
        MPI_Barrier(MPI_COMM_WORLD);
        SimpleClassifier best = SimpleClassifier(1.0, 1.0, 1);
        double alpha;
        double locErr;
        struct error {double value; int index;} errLocal,errGlobal;               //get the best classifier in this round and the rank of processus which contain this classifier
        getBestClassifier(lambda,valSet,weaks,best,&locErr);
        cout<<"Round "<<i<<" -- The best of classifier in processus "<<rank<<" is calculated\n";
	//cout<<"And the local err is : "<<locErr<<endl;
        errLocal.value = locErr;
        errLocal.index = rank;
        MPI_Reduce(&errLocal,&errGlobal,1,MPI_DOUBLE_INT,MPI_MINLOC,0, MPI_COMM_WORLD);
	//cout<<"The best classifier rank: "<<errGlobal.index<<" and the err value: "<<errGlobal.value<<endl;
        //**
        //not finished: 1,root brocast the id of the processus which have the best classifier in this round
        //              2,the processus which have the best classifier update the lambda and brocast to the other processus 
        //              end and run the next round
        
        MPI_Bcast(&errGlobal.index,1,MPI_INT,0,MPI_COMM_WORLD);

        if(rank == errGlobal.index){
            cout<<"The classifier calculated by processus "<<rank<<" is chosed\n";
            alpha = (1.0-locErr)/locErr;
            alpha = log(alpha) / 2.0;
            cout<<"The classifier chosed get error "<<locErr<<endl;;
            cout<<"The local alpha caculated is "<<alpha<<"\nValset size: "<<valSet.size()<<endl;
            for(int i=0;i<valSet.size();i++){
                double term = valSet[i].getImageClass()*alpha;
                term *=best.predictByImage(valSet[i]);
                lambda[i] *= exp(-term);
               // cout<<"Processus "<<rank<<" computed lambda "<<i<<" : "<<lambda[i]<<endl;
            }
            double lambda_sum = 0.0;
            for(int i=0;i<valSet.size();i++){
                lambda_sum +=lambda[i];
            }
            for(int i=0;i<valSet.size();i++){
                lambda[i] /=lambda_sum;
            }
            cout<<"Processus "<<rank<<" updated lamda\n";
	        double t1 = best.getW0();
            MPI_Send(&t1,1,MPI_DOUBLE,0,Class_W0,MPI_COMM_WORLD);
            cout<<"Processus "<<rank<<" sent w0 of the best classifier to 0\n";
	        double t2 = best.getW1();
            MPI_Send(&t2,1,MPI_DOUBLE,0,Class_W1,MPI_COMM_WORLD);
            cout<<"Processus "<<rank<<" sent w1 of the best classifier to 0\n";
	        int index_t = best.getIndex();
            MPI_Send(&index_t,1,MPI_INT,0,Class_Index,MPI_COMM_WORLD);
            cout<<"Processus "<<rank<<" sent index of the best classifier to 0\n";

        }

        if(rank == 0){
            double w0,w1;
            int index;
	    MPI_Status status;
            MPI_Recv(&w0,1,MPI_DOUBLE,errGlobal.index,Class_W0,MPI_COMM_WORLD, &status);
            cout<<"Processus 0 recieved w0 from "<<errGlobal.index<<endl;
            MPI_Recv(&w1,1,MPI_DOUBLE,errGlobal.index,Class_W1,MPI_COMM_WORLD, &status);
            cout<<"Processus 0 recieved w1 from "<<errGlobal.index<<endl;
            MPI_Recv(&index,1,MPI_INT,errGlobal.index,Class_Index,MPI_COMM_WORLD, &status);
            cout<<"Processus 0 recieved index from "<<errGlobal.index<<endl;
            index = indexLocal2Global(index,errGlobal.index,nProcs);
            strong.push_back(SimpleClassifier(w0,w1,index));
            alpha = (1.0-errGlobal.value)/errGlobal.value;
            alpha = log(alpha) / 2.0;
            alphas.push_back(alpha);
            cout<<"The global err got is "<<errGlobal.value<<endl;
            cout<<"The alpha got for this round is "<<alpha<<endl;
        }
        MPI_Bcast(lambda,valSet.size(),MPI_DOUBLE,errGlobal.index,MPI_COMM_WORLD);
        cout<<"Processus "<<errGlobal.index<<" brocasted lambda to all the others processus\n";
        MPI_Barrier(MPI_COMM_WORLD);
    }
    delete []lambda;
}

void saveClassifier(vector<SimpleClassifier>&strongs, vector<double>&alpha){
    ofstream myfile;
    myfile.open("result/strongclassifier.txt");
    for(int i=0;i<strongs.size();i++){
        myfile<<alpha[i]<<'\t'<<strongs[i].toString();
    }
    myfile.close();
}

void split(string& s, string& delim,vector<string>& ret)  
{  
    unsigned int last = 0;  
    unsigned int index=s.find_first_of(delim,last);  
    while (index!=std::string::npos)  
    {  
        ret.push_back(s.substr(last,index-last));  
        last=index+1;  
        index=s.find_first_of(delim,last);  
    }  
    if (index-last>0)  
    {  
        ret.push_back(s.substr(last,index-last));  
    }  
}  

void loadClassifier(vector<SimpleClassifier>&strongs, vector<double>&alpha){
    string line;
    ifstream myfile("result/strongclassifier.txt");
    if(myfile.is_open())
    {
        while(getline(myfile,line)){
            //double alpha,w_0,w_1;
            int index;
            vector<string> ret;
	    string dlt = "\t";
            split(line, dlt, ret);
            alpha.push_back(strtod(ret[0].c_str(), NULL));
            strongs.push_back(SimpleClassifier(strtod(ret[1].c_str(), NULL),strtod(ret[2].c_str(), NULL),atoi(ret[3].c_str())));
        }
        myfile.close();
    }
}




