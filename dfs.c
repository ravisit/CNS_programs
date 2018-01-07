#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>
int generate(int x,int q,int num)
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
	int q,alpha;
	int xb,yb=1,ya,k=1,i,port,sockfd,len,p,c,newsockfd;
	struct sockaddr_in server;
	srand(time(NULL));
	printf("Enter the value of q and alpha : ");
	scanf("%d%d",&q,&alpha);
	xb = rand()%q;
	yb = generate(xb,q,alpha);
	printf("Private Key : %d \t Public Key : %d\n",xb,yb);
	printf("Enter the port number: ");
	scanf("%d",&port);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	server.sin_family= AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	listen(sockfd,1);
	newsockfd = accept(sockfd,NULL,NULL);
	close(sockfd);
	printf("Sending the public key...\n");
	send(newsockfd,&yb,sizeof(yb),0);
	printf("Waiting to receive USER A's public key...\n");
	recv(newsockfd,&ya,sizeof(ya),0);
	printf("USER A's public key received: %d\nCalculating shared key....",ya);
	k = generate(xb,q,ya);
	printf("The Shared Key is : %d \n",k);
	printf("Waiting to receive encrypted mesage...\n");
	recv(newsockfd,&c,sizeof(c),0);
	printf("The encrypted message received is : %d\n", c);
	p=c^k;
	printf("The decrypted message is : %d\n",p);
	close(newsockfd);
}
