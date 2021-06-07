#include "makeVector.h"   

void makeVector (std::string loaded_line, double sv[48]) {

    double d = 0.0;

    std::stringstream ss(loaded_line);
    int i = 0;

    while (ss >> d){
        sv[i] = d;
        i ++;}

}