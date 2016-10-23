#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N(a,b) 2.0*a/b*100
FILE *fp1,*fp2;
int t,m;
char string1[500],string2[500];
char file1[50],file2[50];
void Contrast()
{
char str1[50],str2[50];
int i=0,j=0;
int s,t=0,flag1=1,flag2=1;
int n,sum,sam=0,word1=0,word2=0,sbm=0;
char c;
while(flag1==1)
    {
for(s=0;(string1[i]!=' ')&&(string1[i]!=0);s++,i++)
            str1[s]=string1[i];
            str1[s]='\0';
if(str1=="")
continue;
        flag2=1;
        j=0;
while(flag2==1)
        {
for(s=0;(string2[j]!=' ')&&(string2[j]!=0);j++,s++)
                str2[s]=string2[j];
                str2[s]='\0';
if(str2=="")
continue;
if(strcmp(str1,str2)==0)
            {
t++;
                flag2=0;
continue;
            }
j++;
if(string2[j]==0)
                flag2=0;
        }
i++;
if(string1[i]==0)
            flag1=0;
    }
printf("The same word:%d\n",t);
for(n=0;(c=string1[n])!='\0';n++)
if(c==' '||c==','||c=='.')
            word1=0;
else
if(word1==0)
        {
            word1=1;
sam++;
        }
for(m=0;(c=string2[m])!='\0';m++)
if(c==' '||c==','||c=='.')
            word2=0;
else
if(word2==0)
        {
            word2=1;
sbm++;
        }
sum=sam+sbm;
printf("Similarity:%5.2f%%\n",N(t,sum));
}

int main()
{
printf("Press 1 to get file1:\n");
printf("Press 2 to get file2:\n");
printf("Press 3 to compare file1 and file2:\n");
printf("Press 4 to exit:\n");
while(t!=4)
{
    scanf("%d",&t);
    if(t==1)
        {
gets(file1);
            fp1=fopen( file1,"r");
fgets(string1,500,fp1);
        }
else
if(t==2)
            {
gets(file2);
                fp2=fopen( file2,"r");
fgets(string2,500,fp2);
            }
else
if(t==3)
Contrast();
else
printf("Error!\n");
    }
}
