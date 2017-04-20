#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>


float** Standard(int,float **,float ** );
float **addMatrix(float **, float **, int );   
float** Strassen(int, float **, float **);
void printMatrix(float **,int );
float ** split(float ** , int ,int,int );
float** parallel_Strasson(float** ,float **,int );

typedef struct args2{
	float **A;
	float **B;
	int n;
}thread_args2;

void* thread_function2(void *pv)
{
	struct args2 *S=malloc(sizeof(thread_args2 *));
	S=pv;
	return parallel_Strasson(S->A,S->B,S->n);
}

	


void main()
 {
	int n,i,j;
	clock_t t;
   	printf("Enter the size of the matrix:");
   	scanf("%d",&n);
   	float **M1 = (float **)malloc(n * sizeof(float *));
   	float **M2 = (float **)malloc(n * sizeof(float *));
   	float **M3 = (float **)malloc(n * sizeof(float *));
   	//float **M4 = (float **)malloc(n * sizeof(float *));
        float **M5 = (float **)malloc(n * sizeof(float *));
	//float **M6 = (float **)malloc(n * sizeof(float *));
	float **M7 = (float **)malloc(n * sizeof(float *));
   	for (i=0; i<n; i++)
		{
			M1[i] = (float *)malloc(n * sizeof(float));
         		M2[i] = (float *)malloc(n * sizeof(float));
         		M3[i] = (float *)malloc(n * sizeof(float));
         		//M4[i] = (float *)malloc(n * sizeof(float));
			M5[i] = (float *)malloc(n * sizeof(float));
			//M6[i] = (float *)malloc(n * sizeof(float));
			M7[i] = (float *)malloc(n * sizeof(float));
      		}
   	srand(time(NULL));
	for (i = 0; i <  n; i++)
		for (j = 0; j < n; j++)
		{
			M1[i][j] = (float)rand()/((float)RAND_MAX/100);   
         	     	M2[i][j] = (float)rand()/((float)RAND_MAX/100);      
        	}
    	
  
	t = clock();
    	M3=Standard(n,M1,M2);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	//printMatrix(M3,n);
 	printf("standard() took %f seconds to execute \n", time_taken);

    	t = clock();
	M5=Strassen(n,M1,M2);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	//printMatrix(M5,n);
 	printf("strassen() took %f seconds to execute \n", time_taken);
	
	t = clock();
	M7=parallel_Strasson(M1,M2,n);
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	//printMatrix(M7,n);
 	printf("parallel_Strasson() took %f seconds to execute \n", time_taken);

	free(M1);
	free(M2);
	free(M3);
	free(M5);
	free(M7);

 }



float ** split(float **m,int r,int c,int n)
{
	int i,j;
	float **M=malloc((n)*sizeof(float *));
	for(i=0;i<n;i++)
	{
		M[i]=malloc((n)*sizeof(float));
		for(j=0;j<n;j++)
		{
			M[i][j]=m[c+i][r+j];
		}
	}
	
return M;
}


float** Standard(int n, float **M1, float **M2)
 {
	
	float sum;
     	float **M3 = (float **)malloc(n * sizeof(float *));
     	for (int i=0; i<n; i++)
      	{
		M3[i] = (float *)malloc(n * sizeof(float));
      	}
     	for (int i=0;i<n;i++)
        {
       		for(int j=0;j<n;j++)
        	{
         		sum=0;
         		for(int k=0;k<n;k++)
           		{
             			sum=sum+M1[i][k]*M2[k][j];
           		}
         		M3[i][j]=sum;
        	}
      	}
    	
   	return M3;
 }

void printMatrix(float **M,int n)
{
	for (int i = 0; i <  n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%f ", M[i][j]);
                }
                printf("\n");
        }

printf("\n");
}

float **addMatrix(float **a, float **b, int n) 
{
		float **c = (float **)malloc(n * sizeof(float *));
		for (int i=0; i<n; i++)
		{
         		c[i] = (float *)malloc(n * sizeof(float));
      		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) 
			{
				c[i][j] = a[i][j] + b[i][j];
        		}
    		}

    	return c;
}

float **subMatrix(float **a, float **b, int n) 
{
		float **c = (float **)malloc(n * sizeof(float *));
		for (int i=0; i<n; i++)
		{
         		c[i] = (float *)malloc(n * sizeof(float));
      		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) 
			{
				c[i][j] = a[i][j] - b[i][j];
        		}
    		}

    	return c;
}


float** Strassen(int n, float **M1, float **M2)
 {
	
	float **M5 = (float **)malloc(n * sizeof(float *));
	float sum;
     	for (int i=0; i<n; i++)
      	{
		M5[i] = (float *)malloc(n * sizeof(float));
      	}
	if(n==1)
	{
		M5[0][0]=M1[0][0]*M2[0][0];
	}
	else
	{
	int hn=(n/2);  
        float **a11 = (float **)malloc(hn * sizeof(float *));
	float **a12 = (float **)malloc(hn * sizeof(float *));
	float **a21 = (float **)malloc(hn * sizeof(float *));
	float **a22 = (float **)malloc(hn * sizeof(float *));
	float **b11 = (float **)malloc(hn * sizeof(float *));
	float **b12 = (float **)malloc(hn * sizeof(float *));
	float **b21 = (float **)malloc(hn * sizeof(float *));
	float **b22 = (float **)malloc(hn * sizeof(float *));
	float **S1 = (float **)malloc(hn * sizeof(float *));
	float **S2 = (float **)malloc(hn * sizeof(float *));
	float **S3 = (float **)malloc(hn * sizeof(float *));
	float **S4 = (float **)malloc(hn * sizeof(float *));
	float **S5 = (float **)malloc(hn * sizeof(float *));
	float **S6 = (float **)malloc(hn * sizeof(float *));
	float **S7 = (float **)malloc(hn * sizeof(float *));
	float **S8 = (float **)malloc(hn * sizeof(float *));
	float **S9 = (float **)malloc(hn * sizeof(float *));
	float **S10 = (float **)malloc(hn * sizeof(float *));
	float **P1 = (float **)malloc(hn * sizeof(float *));
	float **P2 = (float **)malloc(hn * sizeof(float *));
	float **P3 = (float **)malloc(hn * sizeof(float *));
	float **P4 = (float **)malloc(hn * sizeof(float *));
	float **P5 = (float **)malloc(hn * sizeof(float *));
	float **P6 = (float **)malloc(hn * sizeof(float *));
	float **P7 = (float **)malloc(hn * sizeof(float *));
	for (int i=0; i<hn; i++)
	{
		a11[i] = (float *)malloc(hn * sizeof(float));
         	a12[i] = (float *)malloc(hn * sizeof(float));
         	a21[i] = (float *)malloc(hn * sizeof(float));
         	a22[i] = (float *)malloc(hn * sizeof(float));
		b11[i] = (float *)malloc(hn * sizeof(float));
         	b12[i] = (float *)malloc(hn * sizeof(float));
         	b21[i] = (float *)malloc(hn * sizeof(float));
         	b22[i] = (float *)malloc(hn * sizeof(float));
		S1[i] = (float *)malloc(hn * sizeof(float));
		S2[i] = (float *)malloc(hn * sizeof(float));
		S3[i] = (float *)malloc(hn * sizeof(float));
		S4[i] = (float *)malloc(hn * sizeof(float));
		S5[i] = (float *)malloc(hn * sizeof(float));
		S6[i] = (float *)malloc(hn * sizeof(float));
		S7[i] = (float *)malloc(hn * sizeof(float));
		S8[i] = (float *)malloc(hn * sizeof(float));
		S9[i] = (float *)malloc(hn * sizeof(float));
		S10[i] = (float *)malloc(hn * sizeof(float));
		P1[i] = (float *)malloc(hn * sizeof(float));
		P2[i] = (float *)malloc(hn * sizeof(float));
		P3[i] = (float *)malloc(hn * sizeof(float));
		P4[i] = (float *)malloc(hn * sizeof(float));
		P5[i] = (float *)malloc(hn * sizeof(float));
		P6[i] = (float *)malloc(hn * sizeof(float));
		P7[i] = (float *)malloc(hn * sizeof(float));
      	}
        for (int i = 0; i < n/2; i++) 
	{
		for (int j = 0; j < n/2; j++) 
		{

			a11[i][j] = M1[i][j]; // top left
        		a12[i][j] = M1[i][j + n/2]; // top right
        		a21[i][j] = M1[i + n/2][j]; // bottom left
        		a22[i][j] = M1[i + n/2][j + n/2]; // bottom right
	
        		b11[i][j] = M2[i][j]; // top left
        		b12[i][j] = M2[i][j + n/2]; // top right
        		b21[i][j] = M2[i + n/2][j]; // bottom left
        		b22[i][j] = M2[i + n/2][j + n/2]; // bottom right
    		}
	}  
	for(int i=0;i<hn;i++)
	{
		for(int j=0;j<hn;j++)
		{
			S1=subMatrix(b12,b22,hn);
			S2=addMatrix(a11,a12,hn);
			S3=addMatrix(a21,a22,hn);
			S4=subMatrix(b21,b11,hn);
			S5=addMatrix(a11,a22,hn);
			S6=addMatrix(b11,b22,hn);
			S7=subMatrix(a12,a22,hn);
			S8=addMatrix(b21,b22,hn);
			S9=subMatrix(a11,a21,hn);
			S10=addMatrix(b11,b12,hn);
		}
	}
	
	P1=Strassen(n/2,a11,S1);
	P2=Strassen(n/2,S2,b22);
	P3=Strassen(n/2,S3,b11);
	P4=Strassen(n/2,a22,S4);
	P5=Strassen(n/2,S5,S6);
	P6=Strassen(n/2,S7,S8);
	P7=Strassen(n/2,S9,S10);

	float** C11 = addMatrix(subMatrix(addMatrix(P5,P4,n/2),P2,n/2),P6,n/2);
        float** C12 = addMatrix(P1,P2,n/2);
        float** C21 = addMatrix(P3,P4,n/2);
        float** C22 = subMatrix(subMatrix(addMatrix(P5,P1,n/2),P3,n/2),P7,n/2);

	for (int i = 0; i < n/2; i++) 
	{
		for (int j = 0; j < n/2; j++) 
		{
			M5[i][j] = C11[i][j];
                	M5[i][j + n/2] = C12[i][j];
                	M5[i + n/2][j] = C21[i][j];
                	M5[i + n/2][j + n/2] = C22[i][j];
           	}
        }
        }
    	return M5;
		
     
 }




float** parallel_Strasson(float** M1,float **M2,int n)
 {
	
	pthread_t tid1,tid2,tid3,tid4,tid5,tid6,tid7,tid8;
	float sum;
	float **M7 = (float **)malloc(n * sizeof(float *));
     	for (int i=0; i<n; i++)
      	{
		M7[i] = (float *)malloc(n * sizeof(float));
      	}
	if(n==1)
	{
		M7[0][0]=M1[0][0]*M2[0][0];
	}
	else
	{
	int hn=(n/2);  
        float **a11 = (float **)malloc(hn * sizeof(float *));
	float **a12 = (float **)malloc(hn * sizeof(float *));
	float **a21 = (float **)malloc(hn * sizeof(float *));
	float **a22 = (float **)malloc(hn * sizeof(float *));
	float **b11 = (float **)malloc(hn * sizeof(float *));
	float **b12 = (float **)malloc(hn * sizeof(float *));
	float **b21 = (float **)malloc(hn * sizeof(float *));
	float **b22 = (float **)malloc(hn * sizeof(float *));
	float **S1 = (float **)malloc(hn * sizeof(float *));
	float **S2 = (float **)malloc(hn * sizeof(float *));
	float **S3 = (float **)malloc(hn * sizeof(float *));
	float **S4 = (float **)malloc(hn * sizeof(float *));
	float **S5 = (float **)malloc(hn * sizeof(float *));
	float **S6 = (float **)malloc(hn * sizeof(float *));
	float **S7 = (float **)malloc(hn * sizeof(float *));
	float **S8 = (float **)malloc(hn * sizeof(float *));
	float **S9 = (float **)malloc(hn * sizeof(float *));
	float **S10 = (float **)malloc(hn * sizeof(float *));
	float **P1 = (float **)malloc(hn * sizeof(float *));
	float **P2 = (float **)malloc(hn * sizeof(float *));
	float **P3 = (float **)malloc(hn * sizeof(float *));
	float **P4 = (float **)malloc(hn * sizeof(float *));
	float **P5 = (float **)malloc(hn * sizeof(float *));
	float **P6 = (float **)malloc(hn * sizeof(float *));
	float **P7 = (float **)malloc(hn * sizeof(float *));
	
	for (int i=0; i<hn; i++)
	{
		a11[i] = (float *)malloc(hn * sizeof(float));
         	a12[i] = (float *)malloc(hn * sizeof(float));
         	a21[i] = (float *)malloc(hn * sizeof(float));
         	a22[i] = (float *)malloc(hn * sizeof(float));
		b11[i] = (float *)malloc(hn * sizeof(float));
         	b12[i] = (float *)malloc(hn * sizeof(float));
         	b21[i] = (float *)malloc(hn * sizeof(float));
         	b22[i] = (float *)malloc(hn * sizeof(float));
		S1[i] = (float *)malloc(hn * sizeof(float));
		S2[i] = (float *)malloc(hn * sizeof(float));
		S3[i] = (float *)malloc(hn * sizeof(float));
		S4[i] = (float *)malloc(hn * sizeof(float));
		S5[i] = (float *)malloc(hn * sizeof(float));
		S6[i] = (float *)malloc(hn * sizeof(float));
		S7[i] = (float *)malloc(hn * sizeof(float));
		S8[i] = (float *)malloc(hn * sizeof(float));
		S9[i] = (float *)malloc(hn * sizeof(float));
		S10[i] = (float *)malloc(hn * sizeof(float));
		P1[i] = (float *)malloc(hn * sizeof(float));
		P2[i] = (float *)malloc(hn * sizeof(float));
		P3[i] = (float *)malloc(hn * sizeof(float));
		P4[i] = (float *)malloc(hn * sizeof(float));
		P5[i] = (float *)malloc(hn * sizeof(float));
		P6[i] = (float *)malloc(hn * sizeof(float));
		P7[i] = (float *)malloc(hn * sizeof(float));
      	}
        for (int i = 0; i < n/2; i++) 
	{
		for (int j = 0; j < n/2; j++) 
		{

			a11[i][j] = M1[i][j]; // top left
        		a12[i][j] = M1[i][j + n/2]; // top right
        		a21[i][j] = M1[i + n/2][j]; // bottom left
        		a22[i][j] = M1[i + n/2][j + n/2]; // bottom right
	
        		b11[i][j] = M2[i][j]; // top left
        		b12[i][j] = M2[i][j + n/2]; // top right
        		b21[i][j] = M2[i + n/2][j]; // bottom left
        		b22[i][j] = M2[i + n/2][j + n/2]; // bottom right
    		}
	}  
	for(int i=0;i<hn;i++)
	{
		for(int j=0;j<hn;j++)
		{
			S1=subMatrix(b12,b22,hn);
			S2=addMatrix(a11,a12,hn);
			S3=addMatrix(a21,a22,hn);
			S4=subMatrix(b21,b11,hn);
			S5=addMatrix(a11,a22,hn);
			S6=addMatrix(b11,b22,hn);
			S7=subMatrix(a12,a22,hn);
			S8=addMatrix(b21,b22,hn);
			S9=subMatrix(a11,a21,hn);
			S10=addMatrix(b11,b12,hn);
		}
	}

	pthread_create(&tid1,NULL,thread_function2,&(thread_args2){a11,S1,n/2});
	pthread_create(&tid2,NULL,thread_function2,&(thread_args2){S2,b22,n/2});
	pthread_create(&tid3,NULL,thread_function2,&(thread_args2){S3,b11,n/2});
	pthread_create(&tid4,NULL,thread_function2,&(thread_args2){a22,S4,n/2});
	pthread_create(&tid5,NULL,thread_function2,&(thread_args2){S5,S6,n/2});
	pthread_create(&tid6,NULL,thread_function2,&(thread_args2){S7,S8,n/2});
	pthread_create(&tid7,NULL,thread_function2,&(thread_args2){S9,S10,n/2});

	pthread_join(tid1,&P1);
	pthread_join(tid2,&P2);
	pthread_join(tid3,&P3);	
	pthread_join(tid4,&P4);	
	pthread_join(tid5,&P5);
	pthread_join(tid6,&P6);
	pthread_join(tid7,&P7);


	float** C11 = addMatrix(subMatrix(addMatrix(P5,P4,n/2),P2,n/2),P6,n/2);
        float** C12 = addMatrix(P1,P2,n/2);
        float** C21 = addMatrix(P3,P4,n/2);
        float** C22 = subMatrix(subMatrix(addMatrix(P5,P1,n/2),P3,n/2),P7,n/2);
	
	for (int i = 0; i < n/2; i++) 
	{
		for (int j = 0; j < n/2; j++) 
		{
			M7[i][j] = C11[i][j];
                	M7[i][j + n/2] = C12[i][j];
                	M7[i + n/2][j] = C21[i][j];
                	M7[i + n/2][j + n/2] = C22[i][j];
           	}
        }
        }
    	return M7;
		
     
 }


