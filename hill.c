#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
void encrypt(char input[20],char cipher[20],int key[3][3],int dim)
{
	int i,j,k,clen, len, flag=0,l;
	int out[3][1], med[3][1];
	char inp[30];
	for(i=0,len=0;i<strlen(input);i++)
		if(input[i]!=' ' && isalpha(input[i]))
           inp[len++]=tolower(input[i]);
	inp[len]='\0';
	i=len=strlen(inp);
	while(len%dim!=0)
	{
		inp[i++]='x';
		len++;
		flag=1;
	}
	if(flag)
		inp[len]='\0';
	for(i=0,clen=0;i<strlen(inp);i=i+dim)
	{
		for(k=0;k<dim;k++)
			med[k][0]=inp[i+k]-'a';
		for(k=0;k<dim;k++)
		{
			out[k][0]=0;
			for(l=0;l<dim;l++)
				out[k][0]+=key[k][l]*med[l][0];
		}
		for(k=0;k<dim;k++)
			cipher[clen++]=(out[k][0]%26)+'a';
	}
	cipher[clen]='\0';
	printf("cipher:%s\n",cipher);
}
void inverse(int key[3][3],int dim,int inv[3][3])
{
	int i,j,k,l,m,n;
	int cofact[3][3],med[2][2];
	int sign=1,det=0,temp;
	if(dim==2)
	{
		cofact[0][0]=key[1][1];
		cofact[0][1]=key[0][1]*-1;
		cofact[1][0]=key[1][0]*-1;
		cofact[1][1]=key[0][0];
                       det=key[0][0]*key[1][1]- key[0][1]*key[1][0];
	}
	else
	{
		for(k=0;k<dim;k++)
		{
			for(l=0;l<dim;l++)
			{
				m=0,n=0;
				for(i=0;i<dim;i++)
					if(i!=k)
						for(j=0;j<dim;j++)
					 	if(j!=l)
						{
							med[m][n++]=key[i][j];
							if(n==2)
								m++,n=0;
						}
			cofact[k][l]=sign*(med[0][0]*med[1][1]-med[1][0]*med[0][1]);
				sign*=-1;
			}
		}
		for(i=0,det=0;i<dim;i++)
			det+=(cofact[0][i]*key[0][i]);
		for(i=0;i<dim-1;i++)
			for(j=i+1;j<dim;j++)
			{
				temp=cofact[i][j];
				cofact[i][j]=cofact[j][i];
				cofact[j][i]=temp;
			}
	}
	if(det==0)
	{
		printf("determinant is zero\n");
		exit(1);
	}
	printf("determinant :%d\n",det);
	if((det%2==0)||(det==13))
	{
		printf("(1/|%d|)mod26 cannot be found\n",det);
		exit(1);
	}
	n=1;
	while(n%det!=0)
		n+=26;
	n/=det;
	for(i=0;i<dim;i++)
		for(j=0;j<dim;j++)
		{
			inv[i][j]=(n*cofact[i][j])%26;
			while(inv[i][j]<0)
			{
				inv[i][j]+=26;
			}
		}
}
void decrypt(char cipher[20],char plain[20],int inv[3][3],int dim)
{
	int i,j,k,l,len,temp=0;
	int out[3][1],med[3][1];
	for(len=0,i=0;i<strlen(cipher);i+=dim)
{
		for(k=0;k<dim;k++)
			med[k][0]=cipher[i+k]-'a';
		for(k=0;k<dim;k++)
		{
			out[k][0]=0;
			for(l=0;l<dim;l++)
				out[k][0]+=inv[k][l]*med[l][0];
		}
		for(k=0;k<dim;k++)
			plain[len++]=(out[k][0]%26)+'a';
	}
	plain[len]='\0';
	printf("Plaintext : ");
	for(i=0;i<len;i++)
	if(plain[i] != 'x')
	printf("%c",plain[i]);
	printf("\n");
}
int main()
{
    char input[30], cipher[30], plain[30];
    int key[3][3],dim, inv[3][3];
	int i,j;
	printf("Enter the plain text:");
	gets(input);
	printf("Enter dimension:");
	scanf("%d",&dim);
	printf("Enter matrix:\n");
	for(i=0;i<dim;i++)
		for(j=0;j<dim;j++)
			scanf("%d",&key[i][j]);
    inverse(key,dim,inv);
	encrypt(input,cipher,key,dim);
	decrypt(cipher,plain,inv,dim);
	return 0;
}
