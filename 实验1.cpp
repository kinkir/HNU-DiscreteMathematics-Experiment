/*
 * 实验一
 * 利用字符数组检索判断合式公式的合法性。 
 * by ljkjk
 */

/* 修改点1：使用万能头文件，减少了头文件的输入 */
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
void rule1(char a[],int i)
{
	if(a[i]>='a' && a[i]<='z') a[i]='1';
	else if(a[i]=='0') a[i]='1';
}
int rule2(char a[],int i)
{
	int n=strlen(a);
	int _result=0;

	if(i+1<n && a[i]=='!' && a[i+1]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+1]!='\0')
		{
			a[i]=a[i+1];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	/* 修改点2：修改运算顺序的问题，优化了运算的逻辑，减少了出错的概率 */
	else if(i+3<n && a[i]=='!' && a[i+1]=='(' && a[i+2]=='1' && a[i+3]==')')
	{
		a[i]='1';
		i++;
		while(a[i+3]!='\0')
		{
			a[i]=a[i+3];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	else if(i+2<n && a[i]=='(' && a[i+1]=='1' && a[i+2]==')')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	/* 修改点3：增加遇到空格时的判断，避免输入格式问题 */
	else if(i<n && a[i]==' ')
	{
		while(a[i+1]!='\0')
		{
			a[i]=a[i+1];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
int rule3Con(char a[],int i)
{
	int _result=0;
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && a[i+1]=='*' && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
int rule3BiCond(char a[],int i)
{
	int _result=0;
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && a[i+1]=='=' && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
int rule3Cond(char a[],int i)
{
	int _result=0;
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && a[i+1]=='-' && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
int rule3DisConj(char a[],int i)
{
	int _result=0;
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && a[i+1]=='+' && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
		_result=1;
	}
	return _result;
}
void rule3(char a[],int i)
{
	int n=strlen(a);
	if(i+2<n && a[i]=='1' && (a[i+1]=='*' || a[i+1]=='-' || a[i+1]=='=' || a[i+1]=='+') && a[i+2]=='1')
	{
		a[i]='1';
		i++;
		while(a[i+2]!='\0')
		{
			a[i]=a[i+2];
			i++;
		}
		a[i]='\0';
	}
}

int main()
{
	/* 修改点4：连续判断多个公式，方便了使用 */
	while(true)
	{
		char pstate[120],pstate0[120];
		int i=0,nold=0,nnew=0;
		printf("请输入公式(析+,合*,条-,双=,否定!,01):\n");
		gets(pstate0);
		fflush(stdin);

		nold=strlen(pstate0)+1;
		nnew=strlen(pstate0);
		for(i=0;i<nnew;i++)
			pstate[i]=pstate0[i];
		pstate[i]='\0';
		i=0;
		while(i<strlen(pstate))
		{
			rule1(pstate,i);
			i++;
		}
		printf("规则1后：%s\n",pstate);

		nold=strlen(pstate0)+1;
		nnew=strlen(pstate);
		/* 修改点5：优化了显示逻辑，只输出需要进行的步骤，便于理解 */
		while(nnew<nold)
		{
			nold=strlen(pstate);
			i=0;
			bool flag=false;
			while(i<strlen(pstate))
				if(rule2(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("规则2后：%s\n",pstate);

			i=0;
			flag=false;
			while(i<strlen(pstate))
				if(rule3Con(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("规则3合取后：%s\n",pstate);

			i=0;
			flag=false;
			while(i<strlen(pstate))
				if(rule3BiCond(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("规则3双条件后：%s\n",pstate);

			i=0;
			flag=false;
			while(i<strlen(pstate))
				if(rule3Cond(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("规则3单条件后：%s\n",pstate);

			i=0;
			flag=false;
			while(i<strlen(pstate))
				if(rule3DisConj(pstate,i)==0)
					i++;
				else flag=true;
			if(flag) printf("规则3析取后：%s\n",pstate);

			nnew=strlen(pstate);
		}
		if(pstate[0]=='1' && strlen(pstate)==1)
			printf("%s is valid\n\n",pstate0);
		else
			printf("%s is invalid\n\n",pstate0);
	}
	return 0;
}

