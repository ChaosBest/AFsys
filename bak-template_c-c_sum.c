#include <stdlib.h>

double * c_sum(const double * matrix, int n){
    static double results[1000]; 
    int index = 0;
        //results[0] = 0;
        for(int j=0; j<n; j++){
            results[j] = matrix[j];
    }
    return results;
}
