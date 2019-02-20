#include<stdio.h>

void makelps(int *arr, const char *pat){
	arr[0] = 0;
	int j = 0;
	int i = 1;
	while(pat[i] != (char)0){
		while(j>0 && pat[j] != pat[i])
			j = arr[j];
		if(pat[j] == pat[i])
			j++;
		arr[i] = j;
		i++;
	}
}

int patternmatch(const char *pat, const char *text){
	int len;
	for(len=0; pat[len] != (char) 0; len++);
	int lps[len];
	makelps(lps,pat);
	int j = 0;
	int count = 0;
	for(int i=0; text[i] != (char)0; i++){
		while(j>0 && pat[j] != text[i])
			j = lps[j-1];
		if(pat[j] == text[i])
			j++;
		if(j == len){
			// return (i-len+1); //This would return first occurance index
			j = lps[len-1];
			count++;
		}
	}
	return count;
}

int main(){
	char text[] = "ADDASDNSBDJDJWSDSFFSDWEEGEFAEQEAADADNSKFHWKEHIEYVNSVXANDSVDAVCNVCMXBCZ";
	char pattern[] = "JDJWSDSFF";
	printf("Number of Occurance: %d\n",patternmatch(pattern,text));
}


