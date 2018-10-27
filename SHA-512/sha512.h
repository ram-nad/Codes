typedef unsigned long long int block;

extern block a,b,c,d,e,f,g,h;

int sha512(const char*);

/*
We have use block to store 64 bits.
So there are total 8 vars (a,b,c,d,e,f,g,h) that reperesents our 512 bit hash
block is declared as long long cause it is guaranteed to be atleast 64 bits long.
*/

/*
The function sha512 calculates hash values and updates the variables a,b,c,d,e,f,g,h.
This function takes argument of the path of the file from whose content it will create a hash value.
If hash is calculated it returns 1.
Else it returns 0.
*/
