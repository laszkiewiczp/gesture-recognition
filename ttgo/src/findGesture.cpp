#include "findGesture.h"

int findGesture(double accData[][3], int n_samples)
{

    double features[48];
    int gesture;
	float feat[48];


    static coder::array<double, 2> accelerationData;

    accelerationData = matlabArray(n_samples, accData);

    computeFeatures(accelerationData, features);

    for (int i = 0; i < 48; i++){
		feat[i] = (float) features[i];
	}

    computeFeatures_terminate();
	
    Eloquent::ML::Port::SVM svm;
    gesture = svm.predict_class(feat);

    return gesture;

}