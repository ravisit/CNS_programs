#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<netinet/in.h>
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
	int msg,en,e,n,i;
	int sockfd,newsockfd,port,clen,y=1,len=0;
	int pu[2];
	char plain[100];
	int blk[100];
	struct sockaddr_in server,client;
	clen=sizeof(client);
	port=5001;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	server.sin_addr.s_addr=INADDR_ANY;
	bind(sockfd,(struct sockaddr *)&server,sizeof(server));
	printf("binded----\n");
	listen(sockfd,1);
	printf("listening----\n");
	newsockfd=accept(sockfd,(struct sockaddr*)&client,&clen);
	close(sockfd);
	recv(newsockfd,(char *)pu,sizeof(pu),0);
	printf("\nThe received public key is pu{%d,%d}\n",pu[0],pu[1]);
	e=pu[0],n=pu[1];
	printf("\nEnter the message to be encrypted:");
	gets(plain);
	len=strlen(plain);
	for(i=0;i<len;i++)
	{
		blk[i]=plain[i]-'a';
	}
	printf("\nencrypting-----\n");
	for(i=0;i<len;i++)
	{
		blk[i]=decryptencrypt(blk[i],e,n);
	}
	
	printf("\n The encrypted message is\n");
	for(i=0;i<len;i++)
	{
		printf("%d ",blk[i]);
	}
	send(newsockfd,(char *)&blk,sizeof(blk),0);
	send(newsockfd,&len,sizeof(len),0);
	printf("\n");
	close(newsockfd);
	
}

