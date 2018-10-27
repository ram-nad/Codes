#include<stdio.h>

typedef unsigned long long int block;

block rotr(block x, unsigned int n)
{
	return ((x>>n) | (x<<(64-n)));
}

block shr(block x, unsigned int n)
{
	return (x>>n);
}

block sigma0(block x)
{
	return ((rotr(x,1))^(rotr(x,8))^(shr(x,7)));
}

block sigma1(block x)
{
	return ((rotr(x,19))^(rotr(x,61))^(shr(x,6)));
}

block major(block x, block y, block z)
{
	return((x&y)^(x&z)^(y&z));
}

block ch(block x, block y, block z)
{
	return ((x&y)^((~x)&z));
}

block sum0(block x)
{
	return ((rotr(x,28))^(rotr(x,34))^(rotr(x,39)));
}

block sum1(block x)
{
	return ((rotr(x,14))^(rotr(x,18))^(rotr(x,41)));
}

/*
This are initial hash values. Final hash values are also stored in same variables.
*/
block a = 0x6a09e667f3bcc908;
block b = 0xbb67ae8584caa73b;
block c = 0x3c6ef372fe94f82b;
block d = 0xa54ff53a5f1d36f1;
block e = 0x510e527fade682d1;
block f = 0x9b05688c2b3e6C1f;
block g = 0x1f83d9abfb41bd6b;
block h = 0x5be0cd19137e2179;


block na,nb,nc,nd,ne,nf,ng,nh; // Temporary to store intermediate hash values

block rconst[80] = {
		    0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
                    0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
                    0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
		    0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
		    0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
		    0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
                    0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
		    0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
		    0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,        
		    0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
		    0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
		    0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
		    0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
		    0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
		    0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
		    0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
		    0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
		    0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
		    0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
		    0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
                   }; // SHA-512 Round Constant


block rvars[80]; // Round variables

block message[16]; // 1024 bits message that is processed in every round.

void genvars() // This variable generates round variables for every round based on message.
{
	for(int i=0; i<16; i++)
		rvars[i] = message[i];
	for(int i=16; i<80; i++)
		rvars[i] = ((sigma1(rvars[i-2])) + rvars[i-7] + (sigma0(rvars[i-15])) + rvars[i-16]);
}

void updatehash() // This function is excecuted in every round of SHA-512
{
	na = a;
	nb = b;
	nc = c;
	nd = d;
	ne = e;
	nf = f;
	ng = g;
	nh = h;
	block temp1, temp2;
	for(int i=0; i<80; i++)
	{
		temp1 = nh + ch(ne,nf,ng) + sum1(ne) + rvars[i] + rconst[i];
		temp2 = sum0(na) + major(na,nb,nc);
		nh = ng;
		ng = nf;
		nf = ne;
		ne = nd + temp1;
		nd = nc;
		nc = nb;
		nb = na;
		na = temp1 + temp2;
	}
	a = a + na;
	b = b + nb;
	c = c + nc;
	d = d + nd;
	e = e + ne;
	f = f + nf;
	g = g + ng;
	h = h + nh;
}

unsigned char pad1 = 128; // Constant to be padded to the message (For 1 bit rest followed by 0)
unsigned char pad0 = 0; // 0 to be padded

unsigned char size[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // This is the array to implement size of 128-bit

void countabyte() // This function increases size by 8 bits (1 byte)
{
	if(size[15] > 247)
	{
		size[15] = (256 - 8) - size[15];
		if(size[14] > 254)
		{
			size[14] = 0;
			if(size[13] > 254)
			{
				size[13] = 0;
				if(size[12] > 254)
				{
					size[12] = 0;
					if(size[11] > 254)
					{
						size[11] = 0;
						if(size[10] > 254)
						{
							size[10] = 0;
							if(size[9] > 254)
							{
								size[9] = 0;
								if(size[8] > 254)
								{
									size[8] = 0;
									if(size[7] > 254)
									{
										size[7] = 0;
										if(size[6] > 254)
										{
											size[6] = 0;
											if(size[5] >  254)
											{
												size[5] = 0;
												if(size[4] > 254)
												{
													size[4] = 0;
													if(size[3] > 254)
													{
														size[3] = 0;
														if(size[2] > 254)
														{
															size[2] = 0;
															if(size[1] > 254)
															{
																size[1] = 0;
																size[0] += 1;
															}
															else
															{
																size[1] += 1;
															}
														}
														else
														{
															size[2] += 1;
														}
													}
													else
													{
														size[3] += 1;
													}
												}
												else
												{
													size[4] += 1;
												}
											}
											else
											{
												size[5] += 1;
											}
										}
										else
										{
											size[6] += 1;
										}
									}
									else
									{
										size[7] += 1;
									}
								}
								else
								{
									size[8] += 1;
								}
							}
							else
							{
								size[9] += 1;
							}
						}
						else
						{
							size[10] += 1;
						}
					}
					else
					{
						size[11] += 1;
					}
				}
				else
				{
					size[12] += 1;
				}
			}
			else
			{
				size[13] += 1;
			}
		}
		else
		{
			size[14] += 1;
		}
	}
	else
	{
		size[15] += 8;
	}
}

void l_hash(FILE **fp, unsigned int N) // Calculates hash in little_endian system.
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<16; j++)
		{
			unsigned char *p = (unsigned char *)&message[j];
			for(int k=7; k>=0; k--)
			{
				fread(p+k,sizeof(unsigned char),1,*fp);
			}
		}
		genvars();
		updatehash();
	}
}

void b_hash(FILE **fp, unsigned int N) // Calculates hash in big_endian system.
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<16; j++)
		{
			unsigned char *p = (unsigned char *)&message[j];
			for(int k=0; k<=7; k++)
			{
				fread(p+k,sizeof(unsigned char),1,*fp);
			}
		}
		genvars();
		updatehash();
	}
}

/*
Both the above function only differ in how they read individual bytes 
from the file and store them in the message that will be processed.
They first generate 1024 bit message from input and then process it till
all the messages are processed.
*/

void test_endian(int *testendian)
{
	FILE *fpo;
	block endian = (111 + ((123*256*256*256)*((unsigned long long int)256)));
	unsigned char test_end;
	unsigned char test_middle;
	fpo = fopen("temp_sha512_file","wb");
	fwrite(&endian,sizeof(endian),1,fpo);
	fclose(fpo);
	fpo = fopen("temp_sha512_file","rb");
	fread(&test_middle,sizeof(test_middle),1,fpo);
	fread(&test_middle,sizeof(test_middle),1,fpo);
	fread(&test_middle,sizeof(test_middle),1,fpo);
	fread(&test_middle,sizeof(test_middle),1,fpo);
	fread(&test_end,sizeof(test_end),1,fpo);
	fread(&test_end,sizeof(test_end),1,fpo);
	fread(&test_end,sizeof(test_end),1,fpo);
	fread(&test_end,sizeof(test_end),1,fpo);
	fclose(fpo);
	remove("temp_sha512_file");
	if((test_end == (unsigned char)111) && (test_middle == (unsigned char)123))
		*testendian = 0;
}

/*
The above function is used to test the Endian of the System.
It only writes a 64 bit unsigned int to a file and retrieves the bytes
at particular position to see the endian of the system used.
*/

int sha512(const char* file_hash)
{
	FILE *fpr;
	FILE *fpo;
	int testendian = 1;
	test_endian(&testendian);
	fpr = fopen(file_hash,"rb");
	if(!fpr) // If input file was not available then return
	{
		return 0;	
	}
	fpo = fopen("temp_sha512_file","wb");
	int count = 0;
	unsigned int N = 0;
	unsigned char newc;
	/*
	Read from input file to a new file
	so that input file is not damaged by mistake.
	*/
	while(fread(&newc,sizeof(newc),1,fpr))
	{
		countabyte();
		fwrite(&newc,sizeof(newc),1,fpo);
		count += 8;
		if(count == 1024)
		{
			N++;
			count = 0;
		}
	}
	fclose(fpr);
	/*
	Add padding and size count at the end of the new file
	*/
	if((896 - count) > 0)
	{
		fwrite(&pad1,sizeof(pad1),1,fpo);
		count += 8;
		while((896 - count) > 0)
		{
			fwrite(&pad0,sizeof(pad0),1,fpo);
			count += 8;
		}
	}
	else
	{
		N += 1;
		fwrite(&pad1,sizeof(pad1),1,fpo);
		count += 8;
		while((1920 - count) > 0)
		{
			fwrite(&pad0,sizeof(pad0),1,fpo);
			count += 8;
		}
	}
	for(int i=0; i<16; i++)
	{
		fwrite(&size[i],sizeof(size[i]),1,fpo);
	}
	N += 1;
	fclose(fpo);
	/*
	Call applicable function to calculate hash from the file.
	*/
	fpo = fopen("temp_sha512_file","rb");
	if(testendian != 0)
	{
		l_hash(&fpo,N);
	}
	else
	{
		b_hash(&fpo,N);
	}
	fclose(fpo);
	remove("temp_sha512_file");
	return 1;
}
