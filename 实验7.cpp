/*
 * 实验七
 * by ljkjk
 */

/*
 * 共 6 个修改点
 * 修改点1：万能头文件
 * 修改点2：合并if和for语句，使代码简洁易懂
 * 修改点3：用strchr函数来代替搜索过程
 * 修改点4：使用memset函数替代双重循环初始化数组
 * 修改点5：利用布尔函数优化交互
 * 修改点6：利用while判断输入是否合法
 */

/* 修改点1：万能头文件 */
#include <bits/stdc++.h>
#define N 100

//集合的基本运算交、并、差、对称差、直积
int printYsh(char a[])
{
	//由于集合保存在一个字符串，显示时在各元素之间加入逗号，及返回长度
	int nLen = 0;
	int i = 0;
	nLen = strlen(a);
	if (nLen > 0)
	{
		printf("%c", a[0]);
	}
	for (i = 1; i < nLen; i++)
	{
		printf(",%c", a[i]);
	}
	printf("\n");
	return nLen;
}
int printRelaYsh(char a[][3], int n)
{
	//由于集合保存在一个字符串，显示时在各元素之间加入逗号，及返回长度
	int i = 0;
//	if (n > 0)
//	{
//		printf("<%c,%c>", a[0][0], a[0][1]);
//	}
//	for (i = 1; i < n; i++)
//	{
//		printf(",<%c,%c>", a[i][0], a[i][1]);
//	}
    for (i = 1; i <= n; i++)
	{
		printf(",<%c,%c>", a[i-1][0], a[i-1][1]);
	}
	/* 修改点2：合并if和for语句，使代码简洁易懂 */
	printf("\n");
	return n;
}
int printRelaMatrix(int M[][N], int n)
{
	//打印关系矩阵的值
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf("%4d", M[i][j]);
		printf("\n");
	}
}
int inputYsh(char a[])
{
	//由于集合保存在一个字符串，但是输入时各字符是用逗号分隔的
	//形参a是一个数组，送入是一个地址值，在函数对该数组的修改会反映在主函数
	char nLen = 0, i = 0, j = 0, k = 0;
	char stmp[1024];//最多1024个字符
	printf("集合元素只能是A-Za-z0-9,其他字符被当作分隔符而去掉：\n");
	gets(stmp);
	fflush(stdin);
	nLen = strlen(stmp);
	for (i = 0; i < nLen; i++)
	{
		if (((stmp[i] >= 'A') && (stmp[i] <= 'Z')) ||
		        ((stmp[i] >= 'a') && (stmp[i] <= 'z')) || ((stmp[i] >= '0') && (stmp[i] <= '9')))
			//还要判断该字符 是否已经在a中出现过
			/* 修改点3：用strchr函数来代替搜索过程 */
			if(strchr(a,stmp[i])==NULL)
            {
                a[j]=stmp[i];
                j++;
            }
	}
	a[j] = '\0';
	return j;//字符串的长度
}
int inputRelaYsh(char a[][3])
{
	//由于序偶是保存在一个字符串，但是输入时各字符是用逗号分隔的
	char nLen = 0, i = 0, j = 0;
	int nbit = 0;
	char stmp[1024];//最多1024个字符
	printf("序偶只能是A-Za-z0-9。其他字符被当作分隔符而去掉，形如<a,b>:\n");
	gets(stmp);
	fflush(stdin);
	nLen = strlen(stmp);
	for (i = 0; i < nLen; i++)
	{
		if (((stmp[i] >= 'A') && (stmp[i] <= 'Z')) ||
		        ((stmp[i] >= 'a') && (stmp[i] <= 'z')) ||
		        ((stmp[i] >= '0') && (stmp[i] <= '9')))
		{
			a[j][nbit] = stmp[i];
			nbit++;
			if (nbit == 2)
			{
				a[j][2] = '\0';
				j++;
				nbit = 0;
			}
		}
	}
	return j;//字符串的长度
}

int relaCompose(char R[][3], char S[][3], char T[][3], int nR, int nS)
{
	//关系的复合，让RS中每个序偶进行比较，组合成功的写入到T中
	int i = 0, j = 0, k = 0, m = 0;
	char a1 = ' ', a2 = ' ';
	for (i = 0; i < nR; i++)
	{
		for (j = 0; j < nS; j++)
		{
			if (R[i][1] == S[j][0]) //<a,b> of R,<b,c> of S then <a,c> in T
			{
				a1 = R[i][0];//还要在T中寻找新序偶是否存在
				a2 = S[j][1];
				m = 0;
				for (m = 0; m < k; m++)
				{
					//如果已经存在则中止
					if ((T[m][0] == a1) && (T[m][1] == a2))
					{
						break;
					}
				}
				if (m >= k) //如果原来不存在则加入其中
				{
					T[k][0] = a1;
					T[k][1] = a2;
					T[k][2] = '\0';
					k++;
				}
			}
		}
	}
	return k;
}
int relaSelf(char a[], char R[][3], int nR, char T[][3])
{
	//自反闭包：判断集合a中各序偶是否在关系R中出现，若没出现则加入其中
	int i = 0, j = 0, k = 0;
	int nLen = 0;
	nLen = strlen(a);
	//先将关系R全部转抄到T中
	for (i = 0; i < nR; i++)
	{
		T[i][0] = R[i][0];
		T[i][1] = R[i][1];
	}
	for (i = 0; i < nLen; i++)
	{
		for (j = 0; j < nR; j++)
		{
			if ((R[j][0] == a[i]) && (R[j][1] == a[i])) //<x,x> in R
			{
				break;
			}
		}
		if (j >= nR) //不在关系R中
		{
			T[j][0] = a[i];
			T[j][1] = a[i];
			T[j][2] = '\0';
			nR++;
		}
	}
	return nR;
}

int relaSym(char R[][3], char T[][3], int nR)
{
	//自反闭包:判断集合a中各序偶是否在关系R中出现，若没出现加入其中
	int i = 0, j = 0, k = 0;
	int nLen = nR;
	//先将关系R全部转抄到T中
	for (i = 0; i < nR; i++)
	{
		T[i][0] = R[i][0];
		T[i][0] = R[i][0];
	}
	for (i = 0; i < nR; i++)
	{
		for (j = 0; j < nR; j++)
		{

			//每个序偶到本关系中寻找对偶关系，若找到了则是对称，否则加上
			if ((R[j][0] == R[i][1]) && (R[j][1] == R[i][0])) //<x,y>,<y,a> inR
			{
				break;
			}
		}
		if (j >= nR) //不是成对出现
		{
			T[nLen][0] = R[i][1];
			T[nLen][1] = R[i][0];
			T[nLen][2] = '\0';
			nLen++;
		}
	}
	return nLen;
}

void rela2matrix(char a[], char R[][3], int nR, int M[][N])
{
	//关系矩阵的行数与列数，等于基本元素即数组a中当前元素的个数
	int i = 0, j = 0, na = 0, k = 0, m = 0;
	na = strlen(a); //基本元素的个数
	//关系矩阵的每个元素清0
//	for (i = 0; i < na; i++)
//	{
//		for (j = 0; j < na; j++)
//		{
//			M[i][j] = 0;
//		}
//	}
    memset(M,0,sizeof(M));
    /* 修改点4：使用memset函数替代双重循环初始化数组 */

	//寻找关系R中每个序偶之元素对应的序号，
	//从而在数组M的指定位置置成1
	for (i = 0; i < nR; i++)
	{
		//确定第i个序偶的首个元素在基本元素集中的序号
		for (j = 0; j < na; j++)
		{
			if (R[i][0] == a[j])
			{
				k = j;
				break;
			}
		}
		//确定第i个序偶的次个元素在基本元素集中的序号
		for (j = 0; j < na; j++)
		{
			if (R[i][1] == a[j])
			{
				m = j;
				break;
			}
		}
		M[k][m] = 1;
	}
}

int matrix2rela(char a[], char R[][3], int M[][N])
{
	int i = 0, j = 0, k = 0, nLen = 0;
	nLen = strlen(a);
	for (i = 0; i < nLen; i++)
	{
		for (j = 0; j < nLen; j++)
		{
			if (M[i][j] == 1)
			{
				//有次序偶则生成也
				R[k][0] = a[i];
				R[k][1] = a[j];
				k++;
			}
		}
	}
	return k;
}
void matrixmulti(int M[][100], int R[][N], int T[][N], int n)
{
	//两个方程相乘，超过二则为1
	int i = 0, j = 0, k = 0, nsum = 0;
	for (i = 0; i < n; i++)
	{
		for(j=0; j<n; j++)
		{
			nsum = 0;
			for (k = 0; k < n; k++)
			{
				nsum = nsum + M[i][k] * R[k][j];
				if (nsum >= 1)
				{
					nsum = 1;
					break;
				}
			}
			T[i][j] = nsum;
		}
	}
}


int trorder(char R[][3], char RM[][3], int nR, int n)
{
	char T[1024][3], T2[1024][3];//关系R的i次方
	int i = 0, nT = 0, j = 0, k = 0, nRM = 0, nT2 = 0;
	//先将R保存到RM中
	for (i = 0; i < nR; i++)
	{
		RM[i][0] = R[i][0];
		RM[i][1] = R[i][1];
		T[i][0] = R[i][0];
		T[i][1] = R[i][1];
	}
	nRM = nR;
	nT = nR;
	for (i = 2; i <= n; i++)//n-1为止
	{
		//将R@R的复合函数暂存到T
		printRelaYsh(T, nT);
		printRelaYsh(R, nR);
		nT2 = relaCompose(T, R, T2, nT, nR);
		printRelaYsh(T2, nT2);
		printf("\n");
		//将复合以后的添加到R中，得到R+R@R，剔除重复的元素
		for (j = 0; j < nT2; j++)
		{
			for (k = 0; k < nRM; k++)
			{
				if ((T2[j][0] == RM[k][0]) && (T2[j][1] == RM[k][1]))
				{
					break;
				}
			}
			if (k >= nRM)//如果没有找到，则加入其中
			{
				RM[nRM][0] = T2[j][0];
				RM[nRM][1] = T2[j][1];
				nRM++;
			}
		}
		//将T2复制给T
		for (j = 0; j < nT2; j++)
		{
			T[j][0] = T2[j][0];
			T[j][1] = T2[j][1];
		}
		nT = nT2;
	}
	return nRM;
}

int rPower(char R[][3], char T[][3], int nR, int n, int np)
{
	//R的np次方
	char T2[1024][3];//关系R的i次方
	int i = 0, nT = 0, j = 0, k = 0, nRM = 0, nT2 = 0;
	//先将R保存到T中
	for (i = 0; i < nR; i++)
	{
		T[i][0] = R[i][0];
		T[i][1] = R[i][1];
	}
	nT = nR;
	for (i = 2; i <= np; i++) //n-1为止
	{
		//将T@R的复合暂存到T2
		nT2 = relaCompose(T, R, T2, nT, nR);
		//将T2复制给T
		for (j = 0; j < nT2; j++)
		{
			T[j][0] = T2[j][0];
			T[j][1] = T2[j][1];
		}
		nT = nT2;
	}
	return nT;
}

int trmatrix(int R[][N], int n)
{
	int i = 0, j = 0, k = 0;
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n; i++)
		{
			if (R[i][j] == 1)
			{
				for (k = 0; k < n; k++)
				{
					//将第j行加到第i行
					R[i][k] = R[i][k] + R[j][k];
					if (R[i][k] >= 1)
					{
						R[i][k] = 1;
					}
				}
			}
		}
	}
	return n;
}

int main()
{
	char a[1024], R1[1024][3], R2[1024][3], T[1024][3];
	int nLen1 = 0, nLen2 = 0, nT = 0, M[N][N], nChoice = 0;
	int MR1[N][N], MR2[N][N];
	int i = 0, n = 0;
	/* 修改点5：利用布尔函数优化交互 */
	bool flag=false;
	while (1)
	{
		printf("\n========================\n");
		if(!flag)
            printf("1...输入相关元素值\n");
        if(flag)
        {
            printf("2...R1*R2关系的复合\n");
            printf("3...自反闭包\n");
            printf("4...对称闭包\n");
            printf("5...序偶形式的关系转关系矩阵\n");
            printf("6...利用矩阵求关系的复合\n");
            printf("7...利用序偶形式的复合求传递闭包\n");
            printf("8...利用warshall算法的求传递闭包\n");
            printf("9...R2*R1关系的复合\n");
            printf("10..R1的任意次方\n");
            printf("11..R2的任意次方\n");
        }
		printf("0...退出\n");
		printf("========================\n您的选择: ");
		//scanf("%d", &nChoice);
		//fflush(stdin);
		/* 修改点6：利用while判断输入是否合法 */
		while(scanf("%d",&nChoice))
            if((nChoice>=0&&nChoice<=8)) break;
            else printf("请重新输入\n");
        
		if (nChoice == 0)
		{
			break;
		}

		switch (nChoice)
		{
			case 1:
			{
			    flag=true;
				printf("输入集合a:");
				inputYsh(a);
				printf("输入关系R1:");
				nLen1 = inputRelaYsh(R1);
				printf("输入关系R2:");
				nLen2 = inputRelaYsh(R2);
				printf("A:");
				printYsh(a);
				printf("关系R1:");
				printRelaYsh(R1, nLen1);
				printf("关系R2:");
				printRelaYsh(R2, nLen2);
				break;
			}

			case 2:
			{
				nT = relaCompose(R1, R2, T, nLen1, nLen2);
				printf("R1@R2:");
				printRelaYsh(T, nT);
				break;
			}
			case 9:
			{
				nT = relaCompose(R2, R1, T, nLen2, nLen1);
				printf("R2@R1:");
				printRelaYsh(T, nT);
				break;
			}
			case 3:
			{
				nT = relaSelf(a, R1, nLen1, T);
				printf("R1的自反闭包：");
				printRelaYsh(T, nT);
				break;
			}
			case 4:
			{
				nT = relaSym(R1, T, nLen1);
				printf("R1的对称闭包：");
				printRelaYsh(T, nT);
				break;
			}
			case 5:
			{
				//序偶形式的关系转换为矩阵形式
				rela2matrix(a, R1, nLen1, M);
				printf("R1关系的序偶");
				printRelaYsh(R1, nLen1);
				printf("R1关系的矩阵\n");
				printRelaMatrix(M, strlen(a));
				break;
			}
			case 6:
			{
				//利用矩阵求关系的复合
				//先求出二个关系的关系矩阵
				rela2matrix(a, R1, nLen1, MR1);
				printf("R1关系的矩阵\n");
				printRelaMatrix(MR1, strlen(a));
				rela2matrix(a, R2, nLen2, MR2);
				printf("R2关系的矩阵\n");
				printRelaMatrix(MR2, strlen(a));
				matrixmulti(MR1, MR2, M, strlen(a));
				printf("复合后的矩阵\n");
				printRelaMatrix(M, strlen(a));
				printf("\n复合后的序偶");
				nT = matrix2rela(a, T, M);
				printRelaYsh(T, nT);
				break;
			}

			case 7://trorder(char R[][3],char RM[][3],int nR,int n)
			{
				nT = trorder(R1, T, nLen1, strlen(a));
				printf("R1的传递闭包:");
				printRelaYsh(T, nT);
				printf("\n序偶转化为数组\n");
				rela2matrix(a, T, nT, M);
				printRelaMatrix(M, strlen(a));
				break;
			}
			case 8:
			{
				rela2matrix(a, R1, nLen1, M);
				printf("R1关系的序偶");
				printRelaYsh(R1, nLen1);
				printf("R1关系中的矩阵\n");
				printRelaMatrix(M, strlen(a));
				trmatrix(M, strlen(a));
				printf("warshall后的矩阵\n");
				printRelaMatrix(M, strlen(a));
				printf("\n序偶");
				nT = matrix2rela(a, T, M);
				printRelaYsh(T, nT);
				break;
			}
			case 10:
			{
				printf("n=?");
				scanf("%d", &n);
				fflush(stdin);
				nT = rPower(R1, T, nLen1, strlen(a), n);
				printf("R1的%d次方：", n);
				printRelaYsh(T, nT);
				printf("\n序偶转换为数组\n");
				rela2matrix(a, T, nT, M);
				printRelaMatrix(M, strlen(a));
				break;
			}
			case 11:
			{
				printf("n=?");
				scanf("%d", &n);
				fflush(stdin);
				nT = rPower(R2, T, nLen2, strlen(a), n);
				printf("R2的%d次方：", n);
				printRelaYsh(T, nT);
				printf("\n序偶转换为数组\n");
				rela2matrix(a, T, nT, M);
				printRelaMatrix(M, strlen(a));
				break;
			}
			//序偶形式的关系到关系矩阵
			/*
			a,b,c,d,e
			<a,b>;<b,c>;<a,d>;<c,e>;<e,a>;<d,b>
			<b,a>;<c,b>;<d,a>;<e,c>;<a,e>;<b,d>
			*/
		}
	}
}

