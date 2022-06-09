#include <stdlib.h>

extern "C" {double c_sum(const double * matrix, int n){
    double results = 0; 
    int index = 0;
        for(int j=0; j<n; j++){
            results += matrix[j];
    }
    return results;
}
}
