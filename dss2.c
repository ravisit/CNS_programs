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
void verify(int p,int q,int g,int s1, int r1,int y, int hash)
{
    int w,u1,u2,v;
    w=inverse(s1,q);
    printf("w: %d\n",w);
    u1=(hash*w)%q;
    printf("u1: %d\n",u1);
    u2=(r1*w)%q;
    printf("u2: %d\n",u2);
    v=((powermod(g,u1,p)*powermod(y,u2,p))%p)%q;
    printf("v: %d\nr': %d\n",v,r1);
    if(v==r1)
    	printf("Signature verified\n");
    else
    	printf("Signature does not match\n");
}
void main()
{
	struct sockaddr_in server;
	int port,sockfd,newsockfd,rcv[5],p,q;
	printf("Enter the values of p and q : ");
	scanf("%d%d",&p,&q);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	printf("Enter the port number: ");
	scanf("%d",&port);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	listen(sockfd,1);
	newsockfd = accept(sockfd,NULL,NULL);
	close(sockfd);
	read(newsockfd,rcv,sizeof(rcv));
	printf("\np: %d\nq: %d\ng: %d\nhash:%d\ns: %d\nr: %d\n",p,q,rcv[4],rcv[0],rcv[1],rcv[2]);
	verify(p,q,rcv[4],rcv[1],rcv[2],rcv[3],rcv[0]);
	close(newsockfd);
}
