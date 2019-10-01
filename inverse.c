#include<stdio.h>
#include<math.h>

void transpose(int n,int a[n][n]);
int determinant(int n,int a[n][n]);
void adjoint(int n,int a[n][n]);
void inverse(int n,int a[n][n],float b[n][n]);

int main()
{
	int n,i,j;
	printf("\nEnter the numbers of rows : ");
	scanf("%d",&n);
	int a[n][n];
	float b[n][n];
	printf("\nEnter the elements row wise \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	int det=determinant(n,a);
	if(det==0)
	{
		printf("\nInverse cannot be found\n");
		return 1;
	}
	inverse(n,a,b);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%f ",b[i][j]);
		}
		printf("\n");
	}
	return 1;
}

void transpose(int n,int a[n][n])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<i;j++)
		{
			int t=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=t;
		}
	}
}
	
int determinant(int n,int a[n][n])
{
	if(n<=2)
	{
		return (a[0][0]*a[1][1]-a[0][1]*a[1][0]);
	}
	int det=0;
	for(int i=0;i<n;i++)
	{
		int b[n-1][n-1],c=0;
		for(int j=1;j<n;j++)
		{
			for(int k=0,c=0;k<n;k++)
			{
				if(k==i)
					continue;
				b[j-1][c]=a[j][k];
				c++;
			}
		}
		if(i%2==0)
			det=det + a[0][i]*determinant(n-1,b);
		else
			det=det - a[0][i]*determinant(n-1,b);
	}
	return det;
}

void adjoint(int n,int a[n][n])
{
	int b[n][n],d[n-1][n-1];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			int c=0,r=0;
			for(int k=0;k<n;k++)
			{
				if(k==i)
					continue;
				for(int l=0,c=0;l<n;l++)
				{
					if(l==j)
						continue;
					d[r][c]=a[k][l];
					c++;
				}
				r++;
			}
			b[i][j]=pow(-1,i+j)*determinant(n-1,d);
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			a[i][j]=b[i][j];
	transpose(n,a);
}

void inverse(int n,int a[n][n],float b[n][n])
{
	int det=determinant(n,a);
	adjoint(n,a);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			b[i][j]=(a[i][j]*1.0)/det;
}



