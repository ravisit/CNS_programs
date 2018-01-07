#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char modify[20],char cipher[20],char mat[5][5]);
void decrypt(char cipher[20],char plain[20],char mat[5][5]);
void create_mat(char key[20],char mat[5][5]);
void modify_ip(char input[20],char modify[20]);
int main()
{
    char input[20],modify[20],cipher[20],plain[20];
    char key[20];
    char mat[5][5];
    printf("enter plain text without spaces\n");
	gets(input);
	printf("enter key\n");
	scanf("%s",key);
	modify_ip(input,modify);
	create_mat(key,mat);
	encrypt(modify,cipher,mat);
	decrypt(cipher,plain,mat);
	return 0;
}
void encrypt(char modify[20],char cipher[20],char mat[5][5])
{
	int clen=0,i,j,k,l;
	int c11,c12,c21,c22;
	char ch1,ch2;
	for(i=0;i<strlen(modify);i=i+2)
	{
		ch1=modify[i];
		ch2=modify[i+1];
		for(k=0;k<5;k++)
			for(l=0;l<5;l++)
			{
				if(ch1==mat[k][l])
					c11=k,c12=l;
				if(ch2==mat[k][l])
					c21=k,c22=l;
			}
		if(c11==c21)
		{
			cipher[clen++]=mat[c11][(c12+1)%5];
			cipher[clen++]=mat[c21][(c22+1)%5];
		}
		else if(c12==c22)
		{
			cipher[clen++]=mat[(c11+1)%5][c12];
			cipher[clen++]=mat[(c21+1)%5][c22];
		}
		else
		{
			cipher[clen++]=mat[c11][c22];
			cipher[clen++]=mat[c21][c12];
		}
	}
	cipher[clen]='\0';
	printf("Cipher : %s\n",cipher);
}
void decrypt(char cipher[20],char plain[20],char mat[5][5])
{
	int plen=0,i,j,k,l;
	int c11,c12,c21,c22;
	char ch1,ch2;
	for(i=0;i<strlen(cipher);i=i+2)
	{
		ch1=cipher[i];
		ch2=cipher[i+1];
		for(k=0;k<5;k++)
			for(l=0;l<5;l++)
			{
				if(ch1==mat[k][l])
					c11=k,c12=l;
				if(ch2==mat[k][l])
					c21=k,c22=l;
			}
		if(c11==c21)
		{
			plain[plen++]=mat[c11][(c12-1)>0?(c12-1)%5:((c12+4)%5)];
			plain[plen++]=mat[c21][(c22-1)>0?(c22-1)%5:((c22+4)%5)];
		}
		else if(c12==c22)
		{
			plain[plen++]=mat[(c11-1)>0?(c11-1)%5:((c11+4)%5)][c12];
			plain[plen++]=mat[(c21-1)>0?(c21-1)%5:((c21+4)%5)][c22];
		}
		else
		{
			plain[plen++]=mat[c11][c22];
			plain[plen++]=mat[c21][c12];
		}
	}
	plain[plen]='\0';
	printf("Plaintext : ");
	for(i=0;i<plen;i++)
	if(plain[i] != 'x')
	printf("%c",plain[i]);
	printf("\n");
}
void create_mat(char key[20],char mat[5][5])
{
	int i,j,k;
	int distinct[26]={0};
	for(i=0,k=0,j=0;i<strlen(key);i++)
	{
		if(!distinct[tolower(key[i])-'a'])
		{
			mat[k][j++]=tolower(key[i]);
			if(j==5)
				k++,j=0;
	    }
		if(key[i]=='j'||key[i]=='i')
			distinct['j'-'a']=distinct['i'-'a']=1;
		else
			distinct[tolower(key[i])-'a']=1;
	}  
	for(i=0;i<26;i++)
	{
		if(!distinct[i])
		{
			mat[k][j++]=i+'a';
			if(j==5)
				k++,j=0;
			if(i+'a'=='i')
				i++;
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%c",mat[i][j]);
		}
		printf("\n");
	}
}

void modify_ip(char input[20],char modify[20])
{
	int len=0,i=0;
	while(input[i]!='\0')
	{
		modify[len++]=input[i++];
		if(input[i]=='\0'||input[i]==input[i-1])
		{
			modify[len++]='x';
		}
		else
			modify[len++]=input[i++];
	}
	modify[len]='\0';
	printf("\n modified ip:%s\n",modify);
}
