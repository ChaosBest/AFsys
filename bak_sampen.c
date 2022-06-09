#include <string.h>
#include <math.h>
// #define Length  360

double * sampen(const double *in, int len)
// void sampen(float *in, int len, float& SampEn)
{
//[12] 2.206449621500217e-06,0.06279084168633738,0.12533626110650992,0.1873732663883192,0.24868504467168548,0.309015439741883,0.3681203619737157,0.42578623689150763,0.48174600129528894,0.5358267727872863,0.5877832262687279,0.6374319296683875
double * results = (double *)malloc(sizeof(double) * len);
// len = 360;
// len = Length;
int Length = len;
int SampEn = 0;
        float buff[Length];
        // float r = 20;
        float r = 0.2;
        
        
        int m = 2;
        //int Samp;

        memcpy(buff, (const float*) in, len * sizeof(float));
        //
        int count1 = 0;
        int count2 = 0;
        for(int i = 0; i < len - 1; i ++){
        	for(int j = 0; j < len - 1; j ++){
        		if(abs(buff[i] - buff[j]) <= r && abs(buff[i+1] - buff[j+1]) <= r){
        			count1 = count1 + 1;
        		        if (i+2 < len && j+2 < len && abs(buff[i+2] - buff[j+2]) <= r) {
                                        count2 = count2 + 1;
                                }
                        }
        	}
        }
        //
        count1 = count1 - len + m - 1;
        float B = (float)count1/((len-m+1)*(len-m));
        count2 = count2 - len + m;
        float A = (float)count2/((len-m)*(len-m-1));
        // if(A == 0){SampEn = 100;}
        // else {SampEn = log(B/A);}
        
        if(A == 0){SampEn = 100000;}
        else {SampEn = (int)1000*log(B/A);}
        results[0] = SampEn;
        return results;
}
