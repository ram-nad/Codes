#include<stdio.h>
#include"sha512.h"

int main()
{
	FILE *fp;
	fp = fopen("test_file_sha3","w");
	fputc('a',fp);
	fputc('b',fp);
	fputc('c',fp);
	fclose(fp);
	if(sha512("test_file_sha3"))
	{
		printf("%016llx ",a);
		printf("%016llx ",b);
		printf("%016llx ",c);
		printf("%016llx ",d);
		printf("\n");
		printf("%016llx ",e);
		printf("%016llx ",f);
		printf("%016llx ",g);
		printf("%016llx ",h);
		printf("\n");
	}
	remove("test_file_sha3");
	return 0;
}
