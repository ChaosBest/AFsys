// #include <string.h>
#include <math.h>
// #include <stdio.h>
// #include<iostream>
// #define len  1000

extern "C"{
double * statistic(double *in, int len)
{
    double buff[len];
    double a[len];
    int location_a[len];

    double * results = (double*)malloc(sizeof(double)*4); 
    // memcpy(buff, (const double*) in, len * sizeof(double));
    
    for (int i = 0; i < len; i++){
            location_a[i] = i;
            a[i] = in[i];
    }


    double b[len];
    int location_b[len];
    int i = 0;
    int j = 0;
    int n  = len;
    int len_seg = 1;
    int Loop = ceil(log2(len));
    double tmp = 0;
    int limit_i,limit_j;
    int flag = 0;
    double Max;
	double Min;
	double Medium;
	double Mean;
	double Sum = 0;
    Loop:for(int loop = 0; loop < Loop;loop++){
        // for 2^Loop #elements data,itera : 1,2,4,8 ... 2^Loop 
        Itera:for(int itera=0; itera < ceil((double)n/2/len_seg);itera++){ 

            i = 2*itera*len_seg;
            j = (2*itera+1)*len_seg;
            limit_i = (2*itera+1)*len_seg;
            limit_j = 2*(itera+1)*len_seg;
            Merge:while( i < limit_i & i < len & j < limit_j & j < len ){

                if(flag == 0){
                    if(a[i] < a[j]){
                        b[i+j-2*itera*len_seg-len_seg] = a[i];
                        location_b[i+j-2*itera*len_seg-len_seg] = location_a[i];
                        i = i + 1;
                    }
                    else{
                        b[i+j-2*itera*len_seg-len_seg] = a[j];
                        location_b[i+j-2*itera*len_seg-len_seg] = location_a[j];
                        j = j + 1;           
                    }
                }
                else{
                    if(b[i] < b[j]){
                        a[i+j-2*itera*len_seg-len_seg] = b[i];
                        location_a[i+j-2*itera*len_seg-len_seg] = location_b[i];
                        i = i + 1;
                    }else{
                        a[i+j-2*itera*len_seg-len_seg] = b[j];
                        location_a[i+j-2*itera*len_seg-len_seg] = location_b[j];
                        j = j + 1;           
                    }                    
                }
            }
            Merge1:while(i < limit_i & i < len){

                if(flag == 0){
                    b[i+j-2*itera*len_seg-len_seg] = a[i];
                    location_b[i+j-2*itera*len_seg-len_seg] = location_a[i];
                    i = i + 1;          
                }else{
                    a[i+j-2*itera*len_seg-len_seg] = b[i];
                    location_a[i+j-2*itera*len_seg-len_seg] = location_b[i];
                    i = i + 1; 
                }        
            }
            Merge2:while(j < limit_j & j < len){

                if(flag == 0){
                    b[i+j-2*itera*len_seg-len_seg] = a[j];
                    location_b[i+j-2*itera*len_seg-len_seg] = location_a[j];
                    j = j + 1;    
                }else{
                    a[i+j-2*itera*len_seg-len_seg] = b[j];
                    location_a[i+j-2*itera*len_seg-len_seg] = location_b[j];
                    j = j + 1; 
                }                
            }
            
      
        }
        if (flag == 0) flag = 1;
        else flag = 0;
        len_seg = 2 * len_seg;
    }
    
    for(i = 0; i < n ; ++i){
        if (Loop % 2 == 0){
            a[i] = a[i];
            location_a[i] = location_a[i];
        }else{
            a[i] = b[i];
            location_a[i] = location_b[i];
        }
    }  
    
    Max = a[len-1];
	Min = a[0];
	if (len%2 == 0){
		Medium = (a[len/2]+a[len/2-1])/2;
	}else{
		Medium = a[(len-1)/2];
	}
	for(int i = 0;i<len;i++){
		Sum = Sum + a[i];
	}
	Mean = Sum/len;
	//std::cout<<"Max: "<<Max<<" Min: "<<Min<<" Medium: "<<Medium<<" Mean: "<<Mean<<std::endl;

	results[0] = Max;
	results[1] = Min;
	results[2] = Medium;
	results[3] = Mean;
	return results;
}

}
