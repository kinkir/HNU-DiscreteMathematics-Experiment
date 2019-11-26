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
#define N 100
using namespace std;
struct stree{
    int pointa,pointb,weight;
};

/* 修改点1：合并两个矩阵的输入 */
int inputadjaceedge(int a[][N],int b[][N],int *n,int *m)
{
    int i=0,j=0;
    printf("点数：");scanf("%d",n);fflush(stdin);
    printf("边数：");scanf("%d",m);fflush(stdin);
    printf("n=%d m=%d\n",*n,*m);
    printf("\n输入邻接矩阵的值：");
    for(i=0;i<*n;++i)
        for(j=0;j<*n;++j)
            scanf("%d",&a[i][j]);
    fflush(stdin);
    printf("\n输入关联矩阵的值：");
    for(i=0;i<*n;++i)
        for(j=0;j<*m;++j)
            scanf("%d",&b[i][j]);
    return 1;
}

//int inputadjace(int a[][N],int *n)
//{
//    int i=0,j=0;
//    printf("点数：");scanf("%d",n);fflush(stdin);
//    printf("\n输入邻接矩阵的值：");
//    for(i=0;i<*n;++i)
//        for(j=0;j<*n;++j)
//            scanf("%d",&a[i][j]);
//    fflush(stdin);
//    return 1;
//}
//
//int inputedge(int b[][N],int n,int *m)
//{
//    int i=0,j=0;
//    printf("边数：");scanf("%d",m);fflush(stdin);
//    printf("\n输入关联矩阵的值：");
//    for(i=0;i<n;++i)
//        for(j=0;j<*m;++j)
//            scanf("%d",&b[i][j]);
//    return 1;
//}

int print(int t[][N],int n,int m,char msg[])
{
    int i=0,j=0;
    printf("\n%s: \n",msg);
    for(i=0;i<n;++i)
    {
        for(j=0;j<m;++j)
            printf("%4d",t[i][j]);
        printf("\n");
    }
    return 1;
}

void caldegree(int a[][N],int n,int d[])
{
    int i=0,j=0;
    for(i=0;i<n;++i)
        d[i]=0;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            d[i]+=(a[i][j]==0?0:1);
}

int iseuler(int d[],int n)
{
    int n0dd=0,i=0;
    int i0dd1=0,j0dd2=0;printf("\n各点的度数：");
    for(i=0;i<n;++i)
        printf("%4d",d[i]);
    printf("\n");
    for(i=0;i<n;++i)
        if(d[i]%2==1)
        {
            n0dd++;
            if(i0dd1==0) i0dd1=i;
            else j0dd2=i;
        }
    if(n0dd==0)
        printf("\n存在Euler回路，即为Euler图\n");
    else if(n0dd==1)
        printf("\n存在Euler路，起点为%d 终点为%d\n",i0dd1,j0dd2);
    else
        printf("\n不存在Euler路与回路\n");
}

void ishamilton(int d[],int n)
{
    int ishp=1,ishg=1;
    int i=0,j=0;
    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
            if(d[i]+d[j]<n-1)
            {
                ishp=0;
                ishg=0;
                break;
            }
            else if(d[i]+d[j]<n)
            {
                ishg=0;
                break;
            }
            if(ishp==0) break;
    }
    if(ishg==1)
        printf("为Hamilton图\n");
    else if(ishp==1)
        printf("存在Hamilton路\n");
    else
        printf("不存在Hamilton路\n");
}

void caldegreeb(int b[][N],int n,int m,int d[])
{
    int i=0,j=0;
    for(i=0;i<n;++i)
        d[i]=0;
    for(i=0;i<n;++i)
        for(j=0;j<m;++j)
            if(b[i][j]!=0)
                d[i]++;
}

int warshall(int a[][N],int n)
{
    int p[N][N],i=0,j=0,k=0,n1count=0;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            p[i][j]=(a[i][j]>0?1:0);
    for(j=0;j<n;++j)
        for(i=0;i<n;++i)
            if(p[i][j]==1)
                for(k=0;k<n;++k)
                {
                    p[i][k]=p[i][k]+p[j][k];
                    if(p[i][k]>=1)
                        p[i][k]=1;
                }
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            if(p[i][j]==1)
                for(k=0;k<n;++k)
                {
                    p[i][k]=p[i][k]+p[j][k];
                    if(p[i][k]>=1)
                        p[i][k]=1;
                }
    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        {
            printf("%3d",p[i][j]);
            n1count+=p[i][j];
        }
        printf("\n");
    }
    if(n1count==n*n)
        printf("图连通\n");
    else
        printf("图不连通\n");
    return n1count;
}

int poweradjace(int a[][N],int n)
{
    int t[N][N],t2[N][N],aa[N][N],a0[N][N];
    char msg[100]="长度为",msgi[10];
    int i=0,j=0,k=0,m=0;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
        {
            a0[i][j]=(a[i][j]>0?1:0);
            t[i][j]=a0[i][j];
            aa[i][j]=a0[i][j];
        }
    print(a0,n,n,strcat(msg,"长度为1的路情况即直接相连的情况"));
    for(i=2;i<=n;++i)
    {
        for(j=0;j<n;++j)
            for(k=0;k<n;++k)
            {
                t2[j][k]=0;
                for(m=0;m<n;++m)
                    t2[j][k]=t2[j][k]+t[j][m]*a0[m][k];
                aa[j][k]==aa[j][k]+t2[j][k];
            }
        for(j=0;j<n;++j)
            for(k=0;k<n;++k)
                t[j][k]=t2[j][k];
        itoa(i,msgi,10);
        strcpy(msg,"长度为");
        strcat(msg,msgi);
        strcat(msg,"的路情况");
        print(t2,n,n,msg);
    }
    print(aa,n,n,"汇总表");
    return 1;
}

int powellcolor(int a[][N],int n,int color[])
{
    int d[N],subindex[N],i=0,j=0,k=0,k0=0,itmp=0,thiscolor[N],m=0,nthiscolor=0;
    for(i=0;i<n;++i)
    {
        subindex[i]=i;
        color[i]=0;
    }
    caldegree(a,n,d);
    /* 修改点2：sort排序 */
    sort(d,d+n);
    sort(subindex,subindex+n);
//    for(i=0;i<n-1;++i)
//        for(j=0;j<n-1-i;++j)
//        {
//            if(d[j]<d[j+1])
//            {
//                swap(d[j],d[j+1]);
//                swap(subindex[j],subindex[j+1]);
//            }
//        }
    printf("排序后的结点度数:\n");
    for(i=0;i<n;++i)
        printf("%4d[%1d]",d[i],subindex[i]);
    itmp=0;
    for(i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
            thiscolor[j]=0;
        nthiscolor=0;
        j=0;
        while(d[j]==-1&&j<n)
            j++;
        if(j>=n)
            break;

        k0=subindex[j];
        itmp++;
        color[k0]=itmp;
        d[j]=-1;
        thiscolor[nthiscolor]=k0;
        printf("\nk0=%d j=%d nthiscolor=%d itmp=%d\n",k0,j,nthiscolor,itmp);

        nthiscolor++;
        j++;

        while(1)
        {
            while(d[j]==-1&&j<n)
                j++;
            if(j==n)
                break;
            k=subindex[j];
            for(m=0;m<nthiscolor;++m)
                if(a[k][thiscolor[m]]>0)
                    break;
            printf("j=%d n=%d k=%d m=%d nthiscolor=%d\n",j,n,k,m,nthiscolor);
            if(m>=nthiscolor)
            {
                color[k]=itmp;
                thiscolor[m]=k;
                nthiscolor++;
                d[j]=-1;
            }
            j++;
        }
    }
    return 0;
}

int getedge(int a[][N],int n,stree t[])
{
    int i=0,j=0,nstree=0;
    for(i=0;i<n;++i)
        for(j=i;j<n;++j)
            if(a[i][j]>0)
            {
                t[nstree].pointa=i;
                t[nstree].pointb=j;
                t[nstree].weight=a[i][j];
                nstree++;
            }
    return nstree;
}

void printtree(stree t[],int nt)
{
    int i=0;
    for(i=0;i<nt;++i)
        printf("%d--%d(%d)",t[i].pointa,t[i].pointb,t[i].weight);
}

void sortedge(stree t[],int nt)
{
    stree t0;
    int i=0,j=0;
    for(i=0;i<nt-1;++i)
        for(j=0;j<nt-1-i;++j)
            if(t[j].weight>t[j+1].weight)
                /* 修改点3：中间元交换值改为swap */
                swap(t[j],t[j+1]);
}

int kruskal(stree t0[],int nt0,int n,stree t[])
{
    int i=0,j=0,k=0,nt=0,b[N][N],m=0,mtmp=0,ncount=0;
    t[nt]=t0[0];
    nt++;
    for(i=1;i<nt0;++i)
    {
        for(j=0;j<n;++j)
            for(k=0;k<nt0;++k)
                b[j][k]=0;
        for(j=0;j<nt;++j)
        {
            b[t[j].pointa][j]=1;
            b[t[j].pointb][j]=1;
        }
        b[t[i].pointa][j]=1;
        b[t[i].pointb][j]=1;

        printf("加入新边后的关联矩阵\n");
        for(j=0;j<n;++j)
        {
            for(k=0;k<=nt;++k)
                printf("%4d",b[j][k]);
            printf("\n");
        }

        for(k=0;k<=nt;++k)
        {
            for(j=k;j<n;++j)
                if(b[j][k]!=0)
                {
                    if(j>k)
                        for(m=0;m<=nt;++m)
                            swap(b[j][m],b[k][m]);
                    break;
                }
            for(j=k+1;j<n;++j)
                if(b[j][k]==1)
                    for(m=k;m<=nt;++m)
                        b[j][m]=b[j][m]-b[k][m]*b[j][k]/b[k][k];
        }
        printf("关联矩阵处理以后：\n");
        for(j=0;j<n;++j)
        {
            for(k=0;k<=nt;++k)
                printf("%4d",b[j][k]);
            printf("\n");
        }
        ncount=0;
        for(k=0;k<=nt;++k)
            if(b[k][k]!=0)
                ncount++;
        if(ncount==nt+1)
        {
            t[nt]=t0[i];
            nt++;
            if(nt==n-1)
                break;
        }
    }
    return nt;
}

int prim(stree t0[],int nt0,int n,stree t[])
{
    int i=0,j=0,k=0,nt=0,b[N][N],m=0,mtmp=0,ncount=0;
    int u[N],mdis=0,idis=0,jtree=0,ntree=0;

    u[nt]=0;
    printf("u[%d]=%d\n",nt,u[nt]);
    nt++;
    while(nt<n)
    {
        mdis=999999;
        idis=-1;
        for(i=0;i<nt;++i)
        {
            k=u[i];
            for(j=0;j<nt0;++j)
            {
                if(t0[j].pointa==k)
                    if(mdis>t0[j].weight)
                    {
                        mdis=t0[j].weight;
                        idis=t0[j].pointb;
                        jtree=j;
                    }
                else if(t0[j].pointb==k)
                    if(mdis>t0[j].weight)
                    {
                        mdis=t0[j].weight;
                        idis=t0[j].pointa;
                        jtree=j;
                    }
            }
        }
        u[nt]=idis;
        t[ntree]=t0[jtree];
        t0[jtree].weight=999999;
        printf("nt=%d u[%d]=%d ntree=%d jtree=%d\n",nt,nt,u[nt],ntree,jtree);
        ntree++;
        nt++;
    }
    return ntree;
}

int main()
{
	stree st0[N],st1[N];
	int A[N][N],B[N][N],D[N],color[N];
	int i=0,j=0,n=0,m=0;
	int nchoice,nt0=0,nt=0;
    /* 修改点4：优化交互 */
	bool flag1=false;
	while(1)
    {
        printf("\n===========================\n");
        if(!flag1)
            printf("1.输入邻接矩阵及关联矩阵\n");
        if(flag1)
        {
            printf("2.邻接矩阵求每点度数及短短图形性质\n3.关联矩阵求每点度数及判断图形性质\n4.用warshall算法判断是否连通\n");
            printf("5.计算A,A^2,A^3,...\n6.用Powell染色算法对结点染色\n");
            printf("7.用kruskal求最小生成树\n8.用prim求最小生成树\n");
        }

        printf("\n===========================\n");
        printf("您的选择(输入0结束)：\n");
        
        /* 修改点5：判断输入是否合法 */
        while(scanf("%d",&nchoice))
            if((nchoice>=0&&nchoice<=8)) break;
            else printf("请重新输入\n");
        //scanf("%d",&nchoice);
        fflush(stdin);
        if(nchoice==0) break;
        switch(nchoice)
        {
            case 1:
                {
                    inputadjaceedge(A,B,&n,&m);
                    print(A,n,n,"邻接矩阵");
                    flag1=true;
                    break;
                }
//            case 11:
//                {
//                    inputedge(B,n,&m);
//                    print(B,n,m,"关联矩阵");
//                    flag11=true;
//                    break;
//                }
            case 2:
                {
                    caldegree(A,n,D);
                    iseuler(D,n);
                    ishamilton(D,n);
                    break;
                }
            case 3:
                {
                    caldegreeb(B,n,m,D);
                    iseuler(D,n);
                    ishamilton(D,n);
                    break;
                }
            case 4:
                {
                    warshall(A,n);
                    break;
                }
            case 5:
                {
                    poweradjace(A,n);
                    break;
                }
            case 6:
                {
                    powellcolor(A,n,color);
                    printf("各点的颜色:\n");
                    for(i=0;i<n;++i)
                        printf("%2d",color[i]);
                    break;
                }
            case 7:
                {
                    nt0=getedge(A,n,st0);
                    printtree(st0,nt0);
                    sortedge(st0,nt0);
                    printtree(st0,nt0);
                    nt=kruskal(st0,nt0,n,st1);
                    printtree(st1,nt);
                    break;
                }
            case 8:
                {
                    nt0=getedge(A,n,st0);
                    printtree(st0,nt0);
                    sortedge(st0,nt0);
                    printtree(st0,nt0);
                    nt=prim(st0,nt0,n,st1);
                    printtree(st1,nt);
                    break;
                }
        }
    }

	return 0;
}
