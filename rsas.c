#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<netinet/in.h>
typedef long int int32;
int32 decryptencrypt(int32 key,int32 msg,int32 n)
{
	int32 k;
	int32 i=0,j;
    k=1;
    for(j=0;j<key;j++)
    {
		k=k*msg;
		k=k%n;
    }
    return k;
}
void main()
{
	int32 msg,en;
	int32 e,n;
	int sockfd,newsockfd,port,clen,y=1;
	int32 pu[2];
	struct sockaddr_in server,client;
	clen = sizeof(client);
	printf("Enter the port number: ");
	scanf("%d",&port);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&y,sizeof(int));
	bind(sockfd,(struct sockaddr * )&server, sizeof(server) );
	listen(sockfd,1);
	bzero((char*)&client,clen);
	newsockfd = accept(sockfd, (struct sockaddr *)&client, &clen);
	close(sockfd);
	recv(newsockfd,(char*)pu,sizeof(pu),0);
	printf("\nThe received public key is PU{%ld,%ld}",pu[0],pu[1]);
	e=pu[0],n=pu[1];
	printf("\nEnter the message to be encrypted: ");
	scanf("%ld",&msg);
	en = decryptencrypt(e,msg,n);
	printf("\nThe encrypted message sent is: %ld\n",en);
	send(newsockfd,(char*)&en,sizeof(en),0);
	close(sockfd);
}
