#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
typedef long int int32;
int prime(int32);
void ced(int32[],int32[],int32,int32);
void encrypt(int32, char[],int32,int32[]);
void decrypt(int32,int32[],int32);
int32 decryptencrypt(int32 key,int32 msg,int32 n);
int32 gcd(int32 a,int32 b);
int lower[26]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
int upper[26]={26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
int num[10]={52,53,54,55,56,57,58,59,60,61};
int main()
{
    int32 p,q,n,flag,e,d,en[100];
    char msg[100];
    int i=0;
    printf("Enter message:\n");
    while((msg[i++]=getchar()) != '\n');
    msg[i-1]='\0';
    //puts(msg);
    printf("\nENTER FIRST PRIME NUMBER\n");
    scanf("%ld",&p);
    flag=prime(p);
    if(flag==0)
    {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    printf("\nENTER ANOTHER PRIME NUMBER\n");
    scanf("%ld",&q);
    flag=prime(q);
    if(flag==0||p==q)
    {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    n=p*q;
    ced(&e,&d,p,q);
    printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
    printf("\n%ld\t%ld",e,d);
    printf("\n");
    encrypt(e,msg,n,en);
    decrypt(d,en,n);
    return 0;
}
int prime(int32 pr)
{
    int i;
    for(i=2;i<=pr/2;i++)
    {
        if(pr%i==0)
        return 0;
    }
    return 1;
}
void ced(int32 *e,int32 *d,int32 p,int32 q)
{
    int32 phi,s,t;
    int32 n;
    n = p*q;
    phi=(p-1)*(q-1);
    *e=1;
    do
    {
    	(*e)++;
    	t=gcd(phi,*e);
    }while(t!=1&& (*e)<phi);
    *d = 0;
    do
    {
        (*d)++;
        s = ((*d)*(*e))%phi;
    }while(s!=1);
}
int32 gcd(int32 a,int32 b)
{
	int32 n=1;
	while(n)
	{
		n= a%b;
		a=b;
		b=n;
	}
	return a;
}
int32 decryptencrypt(int32 key,int32 msg,int32 n)
{
	int32 k;
	int32 j;
    k=1;
    for(j=0;j<key;j++)
    {
		k=k*msg;
		k=k%n;
    }
    return k;
}
void encrypt(int32 key,char msg[100],int32 n,int32 en[100])
{
    int32 k,len;
    int32 temp[100];
    int i=0,j=0;
    int ch;
    int m[100];
    len=strlen(msg);
    if(len%2 != 0)
    {
        printf("\nCharacter used for padding: %c\n",'x');
        msg[len++]='x';
    }
    msg[len]='\0';
    for(i=0;i<len;i++)
    {
        if(isupper(msg[i]))
        ch=upper[msg[i]-65];
        else if(islower(msg[i]))
        ch=lower[msg[i]-97];
        else if(msg[i]>=48 && msg[i]<=57)
        ch=num[msg[i]-48];
        else if(msg[i] == ' ')
        ch=62;
        else if(msg[i] == '.')
        ch=63;
        else if(msg[i] == ',')
        ch=64;
        else if(msg[i] == ';')
        ch=65;
        else if(msg[i] == '?')
        ch=66;
        else
        {
            printf("Invalid character in message\n");
            exit(1);
        }
        m[i]=ch;
    }
    for(i=0,j=0;i<len;i+=2,j++)
    {
        temp[j]=(m[i]*100+m[i+1]);
        k=decryptencrypt(key,temp[j],n);
        en[j]=k;
    }
    en[j]=-1;
    printf("\n\nTHE ENCRYPTED MESSAGE IS\n");
    for(i=0;en[i]!=-1;i++)
    printf(" %ld ",en[i]);
}
void decrypt(int32 key,int32 en[100],int32 n)
{
    int32 k;
    int32 de[100];
    int m[100],len=0;
    int j;
    char msg[100];
    int ch1,ch2;
    int i;
    i=0;
    while(en[i]!=-1)
    {
        k=decryptencrypt(key,en[i],n);
        de[i]=k;
        i++;
    }
    de[i]=-1;
    printf("\n\nTHE DECRYPTED MESSAGE IS\n");
    for(i=0;de[i]!=-1;i++)
    printf(" %ld ",de[i]);
    i=0;
    while(de[i] != -1)
    {
        ch2=de[i]%100;
        ch1=de[i]/100;
        m[len++]=ch1;
        m[len++]=ch2;
        i++;
    }
    for(i=0;i<len;i++)
    {
        if(m[i]>=0 && m[i]<=25)
        msg[i]=m[i]+'a';
        else if(m[i]>=26 && m[i]<=51)
        msg[i]=m[i]-26+'A';
        else if(m[i]>=52 && m[i]<=61)
        msg[i]=m[i]-52+'0';
        else if(m[i]==62)
        msg[i]=' ';
        else if(m[i]==63)
        msg[i]='.';
        else if(m[i]==64)
        msg[i]=',';
        else if(m[i]==65)
        msg[i]=';';
        else if(m[i]==66)
        msg[i]='?';
    }
    msg[i]='\0';
    printf("\nTHE ORIGINAL MESSAGE IS: ");
    for(j=0;j<i;j++)
    if(msg[j]!='x')
    printf("%c",msg[j]);
    printf("\n");
}
