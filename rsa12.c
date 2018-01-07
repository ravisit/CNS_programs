#include <stdio.h>
#include <stdlib.h>
#include<netinet/in.h>
typedef long int int32;
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
void keygen(int32 *d,int32 *e,int32 *n)
{
    int32 phi,s;
    int32 t,p,q;
    printf("\nEnter two prime numbers: ");
    scanf("%ld%ld",&p,&q);
    *n = p*q;
    phi=(p-1)*(q-1);
    *e=1;
    do
    {
    	(*e)++;
    	t=gcd(phi,*e);
    	printf("%ld ",t);
    }while(t!=1&& (*e)<phi);
    *d = 0;
    do
    {
        (*d)++;
        s = ((*d)*(*e))%phi;
    }while(s!=1);

    printf("\nPublic key: { e=%ld n=%ld }",*e,*n);
    printf("\nPrivate key: { d=%ld n=%ld }\n",*d,*n);
}
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
int main()
{
    int32 d,e,n;
	int sockfd,k;
	int32 idA,N1,N2;
	int32 eN2,ek;
	int32 snd[2];
	int32 pu_client[2],pu_server[2];
	struct sockaddr_in server;
	int port;
	char host[15];
            sockfd = socket(AF_INET,SOCK_STREAM,0);
	printf("Enter the port number: ");
	scanf("%d",&port);
	printf("Enter the address of B : ");
	scanf("%s",host);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(host);
	connect(sockfd,(struct sockaddr*)&server,sizeof(server));
	keygen(&d,&e,&n);
	pu_client[0] = e;
	pu_client[1] = n;
	printf("\nPublic key of A: {%ld,%ld}\n",e,n);
	send(sockfd,&pu_client,sizeof(pu_client),0);
	printf("Public key of A sent to B...\n");
	recv(sockfd,&pu_server,sizeof(pu_server),0);
	printf("Public key of B is : {%ld,%ld}\n ",pu_server[0],pu_server[1]);
	printf("Enter the Identity of A:\n");
	scanf("%ld",&idA);
	printf("Enter nonce value N1:\n");
	scanf("%ld",&N1);
	snd[0]=decryptencrypt(pu_server[0],idA,pu_server[1]);
	snd[1]=decryptencrypt(pu_server[0],N1,pu_server[1]);
	printf("Sending encrypted idA and nonce N1 to B...\n");
	send(sockfd,&snd,sizeof(snd),0);
	recv(sockfd,&snd,sizeof(snd),0);
	N2=decryptencrypt(d,snd[1],n);
	eN2=decryptencrypt(pu_server[0],N2,pu_server[1]);
	printf("Sending encrypted nonce N2 to B...\n");
	send(sockfd,&eN2,sizeof(eN2),0);
	printf("Enter the secret key : ");
	scanf("%d",&k);
	ek=decryptencrypt(d,k,n);
	ek=decryptencrypt(pu_server[0],ek,pu_server[1]);
	printf("Sending encrypted secret key to B...\n");
	send(sockfd,&ek,sizeof(ek),0);
	close(sockfd);
    return 0;
}
