#include<stdio.h>
int main()
{
	
	int size = 750;
	float x[size][size];
    	float y[size][size];
    	float z[size][size];//Resultant matrix
	//Initializing matrices
    	for (int i = 0; i < size; ++i) {
        	for (int j = 0; j < size; ++j) {
            		x[i][j] = (float)i + j;
            		y[i][j] = (float)i - j;
            		z[i][j] = 0.0f;
        	}
    	}

    	//Computing the product
    	#pragma omp parallel for
    	for (int i = 0; i < size; ++i) {
        	for (int j = 0; j < size; ++j) {
            		for (int k = 0; k < size; ++k) {
                		z[i][j] += x[i][k] * y[k][j];
            		}
        	}	
    	}

    	return 0;
}
