#include <stdlib.h>
#include <math.h>

double sampen(double *in, int len,int m, double r)
{
//[12] 2.206449621500217e-06,0.06279084168633738,0.12533626110650992,0.1873732663883192,0.24868504467168548,0.309015439741883,0.3681203619737157,0.42578623689150763,0.48174600129528894,0.5358267727872863,0.5877832262687279,0.6374319296683875
double SampEn = 0;

       // double r = 0.2;
       // int m = 2;
        int count1 = 0;
        int count2 = 0;
        for(int i = 0; i < len - 1; i ++){
        	for(int j = 0; j < len - 1; j ++){
        		if(fabs(in[i] - in[j]) <= r && fabs(in[i+1] - in[j+1]) <= r){
        			count1 = count1 + 1;
        		        if (i+2 < len && j+2 < len && fabs(in[i+2] - in[j+2]) <= r) {
                                        count2 = count2 + 1;
                                }
                        }
        	}
        }
        count1 = count1 - len + m - 1;
        double B = (double)count1/((len-m+1)*(len-m));
        count2 = count2 - len + m;
        double A = (double)count2/((len-m)*(len-m-1));
        
        if(A == 0){SampEn = 100000;}
        else {SampEn = log(B/A);}

        return SampEn;
}
