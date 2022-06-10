// #include "sampen.hpp"
//#include <string.h>
#include <math.h>
//#include<iostream>

extern "C"{
double * afen(double *in, int len, int m, double r, double n)
// void sampen(double *in, int len, int& SampEn)
{
        double * results = (double *)malloc(sizeof(double) * 2);
        // int m = 2;
        double dis1[len-m+1][len-m+1];
        double dis2[len-m][len-m];
        // double r = 20;
        // double r = 0.05;
        // double n = 0.125;
        double MAX = 0;
        double MIN = 0;
        double temp = 0;
        double Thr = 1;
        int sum = 0;
 
        double D1 = 0;
        double D2 = 0;
        for(int i = 0; i < len - m + 1; i ++){
        	for(int j = 0; j < len - m + 1; j ++){
                        MAX = 0;
                        MIN = 0xefff; //magic number, 
                        temp = 0;
                        for(int k = 0; k < m; k++){
                                temp = fabs(in[i+k] - in[j+k]);
                                if(MAX < temp){MAX = temp;}
                                if(MIN > temp){MIN = temp;}
                        }
                        if(MAX == 0){dis1[i][j] = 0;}
                        else{
                                dis1[i][j] = (MAX-MIN)/(MAX+MIN);
                        }
//                        std::cout<<" dis1: "<<dis1[i][j]<<" MAX "<<MAX<<" MIN "<<MIN<<std::endl;
        	}
        }
        for(int i = 0; i < len - m; i ++){
        	for(int j = 0; j < len - m; j ++){
                        MAX = 0;
                        MIN = 0xefff;
                        temp = 0;                        
                        for(int k = 0; k < m+1; k++){
                                temp = fabs(in[i+k] - in[j+k]);
                                if(MAX < temp){MAX = temp;}
                                if(MIN > temp){MIN = temp;}
                        }
                        if(MAX == 0){dis2[i][j] = 0;}
                        else{
                                dis2[i][j] = (MAX-MIN)/(MAX+MIN);
                        }
        	}
        }
        
        r = r - 0.01;
        do{
                sum = 0;
                r = r + 0.01;
                for(int i = 0; i < len - m; i ++){
                        for(int j = 0; j < len - m; j ++){
                        if(dis2[i][j] <= r){sum = sum + 1;}  
                        }
                }
        }while(sum/(len - m) < Thr);
    

        for(int i = 0; i < len - m + 1; i ++){
        	for(int j = 0; j < len - m + 1; j ++){
                        D1 = D1 + exp(-1*pow(dis1[i][j], n)/r);
                        // D1 = D1 + log(-1*pow(1, n)/r);
                }
        }
        for(int i = 0; i < len - m ; i ++){
        	for(int j = 0; j < len - m ; j ++){
                        D2 = D2 + exp(-1*pow(dis2[i][j], n)/r);
                        // D2 = D2 + log(-1*pow(1, n)/r);
                }
        }
        // std::cout<<"len:"<<len<<" D1:"<<D1<<" D2:"<<D2<<" r:"<<r<<"dist00: "<<dis1[0][1]<<std::endl;
        double B = D1/((len-m)*(len-m+1));
        double A = D2/((len-m-1)*(len-m)); 
        //
        double FuzzyMEn  = -1 * log(A/B);
        double CorR = log(2*r);       
        results[0] = FuzzyMEn;
        results[1] = CorR;
        return results;
}
}
