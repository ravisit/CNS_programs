#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
int powermod(int num,int power,int mod)
{
	int i,ret=1;
	for(i=0;i<power;i++)
	{
		ret=ret*num;
		ret=ret%mod;
	}
	return ret;
}
int inverse(int k,int mod)
{
	int i;
	for(i=0;i<mod;i++)
		if((k*i)%mod==1)
			return i;
	return -1;
}
void main()
{
	int p,q,h,x,k,sockfd,port,snd[5],hash;
	int r,s,g,y;
	int i=0;
	struct sockaddr_in server;
	char host[20];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	printf("Enter the port number: ");
	scanf("%d",&port);
	printf("Enter the receiver's IP address: ");
	scanf("%s",host);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(host);
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	srand(time(NULL));
	printf("Enter the values of p & q :");
	scanf("%d%d",&p,&q);
	h=rand()%(p-1);
	if(h==1) h++;
	g = powermod(h,(p-1)/q,p);
	do{
		x = rand()%q;
		k = rand()%q;
	}while(x==0||k==0);
	printf("Enter the hash value: ");
	scanf("%d",&hash);
	y = powermod(g,x,p);
	r = powermod(g,k,p)%q;
	s = ( inverse(k,q) * (hash+x*r) )%q;
	snd[0]=hash;
	snd[1]=s;
	snd[2]=r;
	snd[3]=y;
	snd[4]=g;
	printf("\np: %d\nq: %d\ny: %d\nhash: %d\ns: %d\nr: %d\ng: %d\n",p,q,y,hash,s,r,g);
	write(sockfd,snd,sizeof(snd));
	printf("Done!");
	close(sockfd);
}
