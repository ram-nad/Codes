#include<stdio.h>

struct ch{
	char c;
	int cn;
};

char string[15];
int j=0;

void print_str(struct ch arr[], int count)
{
	int flag = 0;
	for(int i=0; i<count; i++)
	{
		if(arr[i].cn !=0)
		{
			flag=1;
			arr[i].cn -= 1;
			string[j] = arr[i].c;
			j += 1;
			print_str(arr,count);
			j -= 1;
			arr[i].cn += 1;
		}
	}
	if(flag == 0)
	{
		string[j] = (char)0;
		printf("%s\n",string);
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	char s[15];
	for(int num=0; num<t; num++)
	{
		scanf("%s",s);
		for(int i=0; s[i]!=(char)0; i++)
		{
			for(int j=i+1; s[j]!=(char)0; j++)
			{
				if(s[j]<s[i])
				{
					s[i] = s[i]^s[j];
					s[j] = s[i]^s[j];
					s[i] = s[i]^s[j];
				}
			}
		}
		int count=0;
		for(int i=0; s[i]!=(char)0; i++)
		{
			if(s[i]!=s[i+1])
				count++;
		}
		struct ch arr[count];
		for(int i=0,j=0; s[i]!=(char)0;)
		{
			arr[j].c = s[i];
			arr[j].cn = 1;
			i++;
			while(s[i]==arr[j].c)
			{
				arr[j].cn += 1;
				i++;
			}
			j++;
		}
		printf("\n");
		print_str(arr,count);
		printf("\n");
	}
}
