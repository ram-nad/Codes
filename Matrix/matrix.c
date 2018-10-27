#include<stdio.h>
#include"matrixcalc.h"

int main()
{
	int n = 3;
	double arr[n][n];
	arr[0][0] = -3.2;
	arr[0][1] = 19.14;
	arr[0][2] = 0.01;
	arr[1][0] = -11.1;
	arr[1][1] = 10.00;
	arr[1][2] = -4.11;
	arr[2][0] = 6.18;
	arr[2][1] = 5.15;
	arr[2][2] = -0.28;
	double det = determinant(n,arr);
	for(int j=0; j<n; j++)
	{
		for(int i=0; i<n; i++)
		{
			printf("%8.3lf ",cofactor(n,i,j,arr)/det); 
		}
		printf("\n");
	}
	return 0;
}
