#include<stdio.h>
#include<time.h>
int gcd(int a,int b)
{
	int n=1;
	while(n)
	{
	    n=a%b;
	    a=b;
	    b=n;
	}
	return a;
}
void test(unsigned long long int n)
{
    unsigned long long int k=0,q=1,x,i,j,y,w;
    unsigned long long int z=n-1;
    unsigned long long int a;
    while(z%2==0)
    {
       z=z/2;
       k++;
    }
   q=z;
    a=rand()%(n-1);
    if(a==1) a++;
    x=1;
    for(i=1;i<=q;i++)
    {
        x*=a;
        x%=n;
    }
    if(x==1)
    {
        printf("%llu is Inconclusive\n",n);
        return;
    }
    x=1;
    for(i=0;i<k;i++)
    {
        x=1,y=1;
        for(j=1;j<=i;j++)
        {
            x*=2;
        }
        x*=q;
        for(w=1;w<=x;w++)			// a^((2^i)*q)%n
        {
            y*=a;
            y%=n;
        }
        if(y==(n-1))
        {
            printf("%llu is Inconclusive\n",n);
            return;
        }
    }
    printf("%llu is composite\n",n);
}
void BlumBlumShub()
{
    int p,q,no,i;
    unsigned long long int n,s,res=0,x;
    srand(time(NULL));
    printf("Enter two prime numbers (3mod4): ");
    scanf("%d%d",&p,&q);
    n=p*q;
    printf("Enter the no of bits required: ");
    scanf("%d",&no);
    do{
        s= rand();
    }while((gcd(s,n)!=1)&&(s==1));
    x=(s*s)%n;
    for(i=1;i<=no;i++)
    {
        x = (x*x)%n;
        res = (res<<1)|(x&1);
    }
    printf("Random number is %llu\n",res);
    printf("Testing %llu for primality using miller rabin\n",res);
    test(res);
}
void main()
{
    BlumBlumShub();
}
