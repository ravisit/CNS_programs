#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
void swap(int *a,int *b)
{
            int t=*a;
	*a=*b;
	*b=t;
}
void init(int key[],int len,int s[])
{
	int i,j,t[256];
	for(i=0;i<256;i++)
	{
		s[i]=i;
		t[i]=key[i%len];
	}
	for(i=0,j=0;i<256;i++)
	{
		j=(j+s[i]+t[j])%256;
		swap(&s[i],&s[j]);
	}
}
void print_key(int key[],int len)
{
    int i,j,t,temp,k=0;
    int keystream[len*8];
    int bits[8];
	printf("The first %d key bytes generated by the key generation process are : \n",len);
    for(i=0;i<len;i++)
    {
        temp=key[i];
        for(j=7;j>=0;j--)
        {
            if(temp>0)
            {
                bits[j]=temp%2;
                temp/=2;
            }
            else
            bits[j]=0;
        }
        for(j=0;j<8;j++)
        keystream[k++]=bits[j];
    }
    for(i=0;i<(len*8);i++)
    {
        if((i%8) == 0)
        printf(" ");
        printf("%d",keystream[i]);
    }
    printf("\n");
}
void stream(int s[],int len,int key[])
{
	int i=0,j=0,k=0;
	while(k<len)
	{
		i = (i+1)%256;
		j=(j+s[i])%256;
		swap(&s[i],&s[j]);
		key[k++]=s[(s[i]+s[j])%256];
	}
	print_key(key,len);
}
void encrypt(int p[],int key[],int len,int c[])
{
	int i;
	for(i=0;i<len;i++)
		c[i]=p[i]^key[i];
	printf("\nThe encrypted message is: ");
	for(i=0;i<len;i++)
		printf("%d\t",c[i]);
}
void decrypt(int p[],int key[],int len,int c[])
{
	int i;
	for(i=0;i<len;i++)
		p[i]=c[i]^key[i];
	printf("\nThe decrypted message is: ");
	for(i=0;i<len;i++)
		printf("%d\t",p[i]);
}
void main()
{
		int s[256],k[256],len,key[500],p[500],c[500];
		int i;
		printf("Enter the length of the key: ");
		scanf("%d",&len);
		/*printf("Enter the key : ");
		for(i=0;i<len;i++)
			scanf("%d",&k[i]);*/
        srand(time(NULL));
        for(i=0;i<len;i++)
            k[i]=rand()%256 + 1;
		init(k,len,s);
		printf("Enter the length of the message in bytes: ");
		scanf("%d",&len);
		printf("Enter the message: \n");
		for(i=0;i<len;i++)
			scanf("%d",&p[i]);
		stream(s,len,key);
		encrypt(p,key,len,c);
		decrypt(p,key,len,c);
}
