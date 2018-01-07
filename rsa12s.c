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
    int32 d,e,n,k;
	int sockfd,clen,nsfd;
	int32 snd[2];
	int32 N1,N2,eN1,eN2,ek,N2_new;
	int32 pu_client[2],pu_server[2];
	struct sockaddr_in server;
	int port;
	printf("Enter the port number: ");
	scanf("%d",&port);
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr*)&server,sizeof(server));
	listen(sockfd,1);
	nsfd = accept(sockfd,NULL,NULL);
	printf("Connected to A...\n");
	close(sockfd);
	keygen(&d,&e,&n);
	pu_server[0] = e;											// PU{e,n}
	pu_server[1] = n;
	printf("\nPublic key of B: {%ld,%ld}\n",e,n);
	send(nsfd,&pu_server,sizeof(pu_server),0);
	printf("Public key of B sent to A...\n");
    recv(nsfd,&pu_client,sizeof(pu_client),0);
    printf("Public key of A is : {%ld,%ld}\n ",pu_client[0],pu_client[1]);
	recv(nsfd,&snd,sizeof(snd),0);
	N1=decryptencrypt(d,snd[0],n);
	printf("Enter nonce value N2:");
	scanf("%ld",&N2);
	snd[0]=decryptencrypt(pu_client[0],N1,pu_client[1]);
	snd[1]=decryptencrypt(pu_client[0],N2,pu_client[1]);
	printf("Sending encrypted nonce N1 and nonce N2 to A...\n");
	send(nsfd,&snd,sizeof(snd),0);

	recv(nsfd,&eN2,sizeof(eN2),0);
	printf("Received encrypted nonce N2 from A...%ld\nDecrypting N2...",eN2);
	N2_new=decryptencrypt(d,eN2,n);
	if(N2==N2_new)
	printf("N2 received is from User A...\n");
	printf("Waiting to receive the encrypted key from user A...\n");
	recv(nsfd,&ek,sizeof(ek),0);
	printf("The encrypted key sent by A is : %ld\n",ek);
	k=decryptencrypt(d,ek,n);
            k=decryptencrypt(pu_client[0],k,pu_client[1]);
	printf("The secret key is: %ld",k);
    printf("\nDone!\n");
	close(nsfd);
    return 0;
}
