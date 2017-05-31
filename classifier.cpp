#include "classifier.hpp"
#include <cmath>

const double w0_init = 1.0;
const double w1_init = 0.0;


void trainWeakClassifier(SimpleClassifier &classifier,vector<Image>& images, double alpha, double p){

    double w1_cur = classifier.getW1();
    double w0_cur = classifier.getW0();
    double w0_pre,w1_pre;
    srand(time(NULL));
    do{
        w0_pre = w0_cur;
        w1_pre = w1_cur;
        int max = images.size();
        int index = rand() % max;
        cout<<" to update para"<<endl;
        classifier.updatePara(images[index],alpha);
        w0_cur = classifier.getW0();
        w1_cur = classifier.getW1();
    }while((abs(w0_pre - w0_cur)>p)||(abs(w1_pre-w1_cur)>p));
}

void getAllWeakClassifiers(vector<Image> &input, double alpha, double p, vector<SimpleClassifier> &cs){
     int featureNum = input[0].getFeatureVector().size();
     for(int i=0;i<featureNum;i++){
         SimpleClassifier classifier = SimpleClassifier(w0_init,w1_init,i);
         trainWeakClassifier(classifier,input,alpha,p); 
         cs.push_back(classifier);
     }
}



