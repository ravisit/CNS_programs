#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<netinet/in.h>

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

void keygen(int *e,int *n,int *d)
{
	int phi,s,p,q,t;
	printf("Enter prime no's\n");
	scanf("%d%d",&p,&q);
	*n=p*q;
	phi=(p-1)*(q-1);
	*e=1;
	do
	{
		*e= *e+1;
		t=gcd(phi,*e);
		printf("%d",t);
	}while(t!=1 && *e<phi);
	*d=0;
	do
	{
		*d=*d+1;
		s=((*d) * (*e))%phi;
	}while(s!=1);
	printf("\n Public key: {e=%d n=%d}\n",*e,*n);
	printf("\n Private key: {d=%d n=%d}\n",*d,*n);
}

int decryptencrypt(int x,int num,int q)
{
	int i,ret=1;
	for(i=0;i<x;i++)
	{
		ret=ret*num;
		ret=ret%q;
	}
	return ret;
}

void main()
{
	int sockfd,clen,len,i;
	int msg,en,m;
	int pu[2];
	struct sockaddr_in server;
	int port=5001;
	int e,n,d;
	clen=sizeof(server);
	char plain[100];
	int blk[100];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(sockfd,(struct sockaddr *)&server,sizeof(server));
	keygen(&e,&n,&d);
	pu[0]=e;
	pu[1]=n;
	send(sockfd,(char*)pu,sizeof(pu),0);
	printf("PUBLIC KEY SENT -----\n");
	printf("Waiting for encrypted message\n");
	recv(sockfd,&blk,sizeof(blk),0);
	recv(sockfd,&len,sizeof(len),0);
	printf("encrypted message:\n");
	for(i=0;i<len;i++)
	{
		printf("%d ",blk[i]);
	}
	printf("\nDecrypting----\n");
	for(i=0;i<len;i++)
	{
		blk[i]=decryptencrypt(blk[i],d,n);
	}
	for(i=0;i<len;i++)
	{
		plain[i]=blk[i]+'a';
	}
	printf("The decrypted message is\n");
	for(i=0;i<=len;i++)
		printf("%c",plain[i]);
	printf("\n");
	close(sockfd);
}


