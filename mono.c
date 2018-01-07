#include<stdio.h>
#include<stdlib.h>
void sort(float fr[26],float free[26],char aaa[26]);
void sort1(float fr[26],float free[26],char aa[26],char ad[26]);
char ke[26];
int main()
{
float fre[26];
int i,j,freq[26],count=0;
for(i=0;i<26;i++)
{
freq[i]=0;
fre[i]=0;
}
randm();
char ak[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char akk[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

float sf2[26]={8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.996,0.153,0.773,4.025,2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074};

char plain[100],ct[100];
FILE *fp,*fp1;
char ch,ch1;
printf("enter the plain text\n");
gets(plain);
fp=fopen("plaintext.txt","w");
fprintf(fp,"%s",plain);
fclose(fp);
fp=fopen("plaintext.txt","r");
fp1=fopen("ciphertext.txt","w");
printf("encrypted text is\n");
while((ch=fgetc(fp))!=EOF)
{
count++;
j=ch-'a';
ch1=ke[j];
freq[ch1-'a']++;
printf("%c",ch1);
fprintf(fp1,"%c",ch1);
}
printf("\n");
for(i=0;i<26;i++)
{
fre[i]=((float)freq[i]/count)*100.0;
}
//sort(fre,sf2,ak);
sort1(fre,sf2,akk,ak);
}
/*void sort(float fr[26],float free[26],char aaa[26])
{
   int i, j;
   float key;
   char  q;
   for (i = 1; i < 26; i++)
   {
       q=aaa[i];
       key = free[i];
       j = i-1;

       while (j >= 0 && free[j] > key)
       {
	   aaa[j+1]=aaa[j];
           free[j+1] = free[j];
           j = j-1;
       }
	aaa[j+1]=q;
       free[j+1] = key;
   }
}
*/

void sort1(float fr[26],float free[26],char aa[26],char ad[26])
{
   int i, j,len=0,x;
   float key;
   char  q,pl[26],ch;
   for (i = 1; i < 26; i++)
   {
       q=aa[i];
       key = fr[i];
       j = i-1;

       while (j >= 0 && fr[j] > key)
       {
           aa[j+1]=aa[j];
           fr[j+1] = fr[j];
           j = j-1;
       }
        aa[j+1]=q;
       fr[j+1] = key;
   }
   for(i=0;i<strlen(aa);i++)
   {
       ch=aa[i];
       for(j=0;j<=25;j++)
       {
           if(ch==ke[j])
            x=j;

       }
       pl[len++]=ad[x];
   }
printf("\n\n");
printf("FREQUENCY\tCIPHER TEXT\tSTANDARD TEXT\n");
printf("---------\t-----------\t-------------\n");
for(i=25;i>=0;i--)
printf("%f\t%c\t\t%c\n",fr[i],aa[i],pl[i]);
}
void randm()
{
    int key[26];
    int flag[26]={0};
    int i,x,count=0,len=0;
    srand(time(NULL));
    while(count<26)
    {
        x=rand()%26;
    if(flag[x]==0)
    {
        key[len++]=x;
        flag[x]=1;
        count++;
    }
    }
    for(i=0;i<=25;i++)
    {
        printf("%d ",key[i]);
    }
    printf("character array\n");
    for(i=0;i<=25;i++)
        ke[i]=key[i]+'a';
    return 0;
}

