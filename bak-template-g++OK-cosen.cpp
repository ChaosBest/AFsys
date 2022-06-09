// #include "sampen.hpp"
#include <string.h>
#include <math.h>
#include<iostream>

extern "C"{
int sampen_count2(const double *in, int len, double r)
{

        double buff[len];

        int m = 2;
     
        memcpy(buff, (const double*) in, len * sizeof(double));
 
        int count1 = 0;
        int count2 = 0;
        for(int i = 0; i < len - 2; i ++){
        	for(int j = 0; j < len - 2; j ++){
        		if(abs(buff[i] - buff[j]) <= r && abs(buff[i+1] - buff[j+1]) <= r && abs(buff[i+2] - buff[j+2]) <= r){
        			count2 = count2 + 1;
                        }
        	}
        }
        //
        count1 = count1 - len + m - 1;
        double B = (double)count1/((len-m+1)*(len-m));
        count2 = count2 - len + m;
        double A = (double)count2/((len-m)*(len-m-1));
        count2 = count2/2;
        return count2;
            
}

double sampen_value(const double *in, int len, double r)
{

double SampEn;
        double buff[len];

        int m = 2;
        //int Samp;
        memcpy(buff, (const double*) in, len * sizeof(double));
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
        double B = (double)count1/((len-m+1)*(len-m));
        count2 = count2 - len + m;
        double A = (double)count2/((len-m)*(len-m-1));
        std::cout<<"count1:"<<count1<<" count2:"<<count2<<std::endl;
        if(A == 0){SampEn = 100000;}
        else {SampEn = log(B/A);}  
        return SampEn;            
}

double cosen(const double *in, int len){
        // len = Length;
        // double in[12] = {-0.329715968120021,-0.122676299245712,-0.0967963406364238,-0.148556257855001,-0.200316175073578,-0.122676299245712,-0.0967963406364238,-0.0450364234178466,-0.0191564648085581,-0.0709163820271352,-0.148556257855001,-0.17443621646429};
        double buff[len];
        // double r = 20;
        double r = 0.15;
        
        double SampEn;
        int m = 2;
        int mNc = 5;
        double dr = 0.001;
        memcpy(buff, (const double*) in, len * sizeof(double));
        double r_front = 0;
        double r_end = 1;
        double r_mid;
        int c_front = 0;
        int c_end = 0;
        int c_mid;
        c_front = sampen_count2(buff, len, r_front);
        c_end = sampen_count2(buff, len, r_end);
        while(c_front < mNc){     // "=" 此时r_front 也会等效，找到
                if(c_end <= mNc){
                        c_front = c_end;
                        r_front = r_end;
                        r_end = 2 * r_end;
                        c_end = sampen_count2(buff, len, r_end);
                }
                else if(c_end > mNc){
                        if(r_end - r_front <= dr){
                                break;
                        }
                        else{
                                r_mid = (r_front+r_end)/2;
                                c_mid = sampen_count2(buff, len, r_mid);
                                if(c_mid < mNc){
                                        r_front = r_mid;
                                }
                                else{
                                        r_end = r_mid;
                                        c_end = c_mid;
                                }
                        }
                }
        }
        std::cout<<"r_front:"<<r_front<<" c_front:"<<c_front<<" buff:"<<buff[0]<<std::endl;
        SampEn = sampen_value(buff, len, r_front);
        return SampEn;
}

}
