double determinant(unsigned int n, double arr[n][n]);

double cofactor(unsigned int n, unsigned int r, unsigned int c, double arr[n][n])
{
	if(n == 1)
		return 1.00;
	double ar[n-1][n-1];
	unsigned int rk = 0;
	unsigned int ck;
	for(unsigned int i=0; i<n; i++)
	{
		if(i != r)
		{
			ck = 0;
			for(unsigned int j=0; j<n; j++)
			{
				if(j != c)
				{
					ar[rk][ck] = arr[i][j];
					ck++;
				}
			}
			rk++;
		}
	}
	int sign = ((r+c)%2 == 0)?(1):(-1);
	return (sign*determinant(n-1,ar)); 
}

double determinant(unsigned int n, double arr[n][n])
{
	double det = 0;
	for(unsigned int i=0; i<n; i++)
	{
		det += (arr[0][i] * cofactor(n,0,i,arr));
	}
	return det;	
}
