#include "adaboost.hpp"
#include <math.h>

const int Class_W0 = 0;
const int Class_W1 = 1;
const int Class_Index =2;

double errCal(Image & img,SimpleClassifier & classifier){
    return (classifier.predictByImage(img)==img.getImageClass())?0.0:1.0;
}

void getBestClassifier(double *lambda, vector<Image>& valSet, vector<SimpleClassifier> &classifiers, SimpleClassifier & best,double err){
    double minErr = numeric_limits<double>::infinity();
    int index=0;
    for(int i=0;i<classifiers.size();i++){
        double errCur = 0.0;
        for(int j=0;i<valSet.size();i++){
            errCur += lambda[j]*errCal(valSet[j],classifiers[j]);
        }
        if(err < minErr){
            index = i;
            minErr = errCur;
        }
    }
    best = classifiers[index];
    err = minErr;
}


void strongClassifier(vector<Image> &valSet, vector<SimpleClassifier> &weaks, vector<SimpleClassifier>&strong, vector<double> &alphas, int N){
    int rank,nProcs;
    MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    double *lambda = new double[valSet.size()];
    double weightInit = 1.0/(double)valSet.size();

    for(int i=0;i<valSet.size();i++){               //initialize the weights
        lambda[i] = weightInit;
    }

    for(int i=0;i<N;i++){
        MPI_Barrier(MPI_COMM_WORLD);
        SimpleClassifier best;
        double alpha;
        double locErr;
        struct {double value, int index} errLocal,errGlobal;               //get the best classifier in this round and the rank of processus which contain this classifier
        getBestClassifier(lambda,valSet,weaks,best,locErr);
        cout<<"Round "<<i<<"The best of classifier in processus "<<rank<<" is calculated\n";
        errLocal.value = locErr;
        errLocal.index = rank;
        MPI_Reduce(&errLocal,&errGlobal,1,MPI_DOUBLE_INT,MPI_MAXLOC,root, MPI_COMM_WORLD);
        //**
        //not finished: 1,root brocast the id of the processus which have the best classifier in this round
        //              2,the processus which have the best classifier update the lambda and brocast to the other processus 
        //              end and run the next round
        
        MPI_Bcast(&errGlobal.index,1,MPI_INT,0,MPI_COMM_WORLD);

        if(rank == errGlobal.index){
            alpha = (1.0-locErr)/locErr;
            alpha = log(alpha) / 2.0;
            for(int i=0;i<valSet.size();i++){
                double term = valSet[i].getImageClass*alpha;
                term *=best.predictByImage(valSet[i]);
                lambda[i] *= exp(-term);
            }
            MPI_Send(&best.getW0(),1,MPI_DOUBLE,0,Class_W0,MPI_COMM_WORLD);
            MPI_Send(&best.getW1(),1,MPI_DOUBLE,0,Class_W1,MPI_COMM_WORLD);
            MPI_Send(&best.getIndex(),1,MPI_INT,0,Class_Index,MPI_COMM_WORLD);

        }

        if(rank == 0){
            double w0,w1;
            int index;
            MPI_Recv(&w0,1,MPI_DOUBLE,errGlobal.index,Class_W0,MPI_COMM_WORLD);
            MPI_Recv(&w1,1,MPI_DOUBLE,errGlobal.index,Class_W1,MPI_COMM_WORLD);
            MPI_Recv(&index,1,MPI_INT,errGlobal.index,Class_Index,MPI_COMM_WORLD);
            strong.push_back(SimpleClassifier(w0,w1,index));
            alpha = (1.0-errGlobal.value)/errGlobal.value;
            alpha = log(alpha) / 2.0;
            alphas.push_back(alpha);
        }
        MPI_Bcast(lambda,valSet.size(),MPI_DOUBLE,errGlobal.index,MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
    }
}