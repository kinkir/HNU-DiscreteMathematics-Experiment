/*
 * 实验五
 * 计算两个集合的若干运算
 * by ljkjk
 */

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <iomanip>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
const int max0 = 1e8;
/* 修改点1：改进print函数，优化了代码质量 */
int print(char a[])
{
//    int nlen=0;
//    int i=0;
//    nlen=strlen(a);
//    if(nlen>0)
//        printf("%c",a[0]);
//    for(i=1;i<nlen;++i)
//        printf(",%c",a[i]);
    int nlen=strlen(a);
    if(nlen==0)
        printf("空集");
    else
        for(int i=0;i<nlen;++i)
        {
            if(i>0) printf(",");
            printf("%c",a[i]);
        }
    printf("\n");
    return nlen;
}

int input(char a[])
{
    char nlen=0,i=0,j=0,k=0;
    char stmp[1024];
    printf("集合元素只能是A-Z,a-z,0-9,其他字符被当作分隔符去掉：\n");
    gets(stmp);
    fflush(stdin);
    nlen=strlen(stmp);
    for(i=0;i<nlen;++i)
        if((stmp[i]>='A'&&stmp[i]<='Z')||(stmp[i]>='a'&&stmp[i]<='z')||(stmp[i]>='0'&&stmp[i]<='9'))
            /* 修改点2：使用strchr函数代替循环搜索，优化了运行速度 */
            if(strchr(a,stmp[i])==NULL)
            {
                a[j]=stmp[i];
                j++;
            }
    /* 修改点3：使用sort函数将集合排序，方便了使用 */
    sort(a,a+j);
    a[j]='\0';
    return j;
}

int setjiao(char a[],char b[],char c[])
{
    int i=0,j=0,k=0,nlen1=0,nlen2=0;
    nlen1=strlen(a);
    nlen2=strlen(b);
    for(i=0;i<nlen1;++i)
        if(strchr(b,a[i])!=NULL)
        {
            c[k]=a[i];
            ++k;
        }
    sort(c,c+k);
    c[k]='\0';
    return k;
}

int setbin(char a[],char b[],char c[])
{
    int i=0,j=0,k=0,nlen1=0,nlen2=0;
    nlen1=strlen(a);
    nlen2=strlen(b);
    /* 修改点4：使用strcpy函数复制数组 */
    strcpy(c,a);
    k=nlen1;
    for(i=0;i<nlen2;++i)
        if(strchr(c,b[i])==NULL)
        {
            c[k]=b[i];
            ++k;
        }
    sort(c,c+k);
    c[k]='\0';
    return k;
}

int setsub(char a[],char b[],char c[])
{
    int i=0,j=0,k=0,nlen1=0,nlen2=0;
    nlen1=strlen(a);
    nlen2=strlen(b);
    for(i=0;i<nlen1;++i)
        if(strchr(b,a[i])==NULL)
        {
            c[k]=a[i];
            ++k;
        }
    sort(c,c+k);
    c[k]='\0';
    return k;
}

int setdc(char a[],char b[],char c[])
{
    int i=0,j=0,k=0,nlen1=0,nlen2=0;
    nlen1=strlen(a);
    nlen2=strlen(b);
    for(i=0;i<nlen1;++i)
    {
        for(j=0;j<nlen2;++j)
            if(a[i]==b[j])
                break;
        if(j>=nlen1)
        {
            c[k]=a[i];
            ++k;
        }
    }
    for(i=0;i<nlen2;++i)
    {
        for(j=0;j<nlen1;++j)
            if(b[i]==a[j])
                break;
        if(j>=nlen1)
        {
            c[k]=b[i];
            ++k;
        }
    }
    c[k]='\0';
    return k;
}

int setdicarl(char a[],char b[],char c[][3])
{
    int i=0,j=0,k=0,nlen1=0,nlen2=0;
    nlen1=strlen(a);
    nlen2=strlen(b);
    for(i=0;i<nlen1;++i)
    {
        for(j=0;j<nlen2;++j)
        {
            c[k][0]=a[i];
            c[k][1]=b[j];
            c[k][2]='\0';
            ++k;
        }
    }
    return k;
}

int main()
{
	char a[1024],b[1024],c[1024],dcar[1024][3];
	int nlen=0;
	int i=0;
	printf("输入集合a：");
	input(a);
	printf("输入集合b：");
	input(b);
	printf("A:");
	print(a);
	printf("B:");
	print(b);
	printf("集合的交:");
	setjiao(a,b,c);
	print(c);
	printf("集合的并:");
	setbin(a,b,c);
	print(c);
	printf("集合的差:");
	setsub(a,b,c);
	print(c);
	printf("集合的对称差:");
	setdc(a,b,c);
	print(c);
	nlen=setdicarl(a,b,dcar);
	if(nlen>0)
        printf("<%c,%c>",dcar[0][0],dcar[0][1]);
    for(i=1;i<nlen;++i)
        printf(",<%c,%c>",dcar[i][0],dcar[i][1]);
	return 0;
}
