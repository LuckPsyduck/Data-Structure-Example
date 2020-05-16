/********************串定长顺序存储**************************/

#include<stdio.h>                  
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define ERROR -1
#define OK 1

#define STACK_INIT_SIZE 10//初始分配量
#define STACK_INCREMENT 2//分配增量

typedef int Status;


#define MAX_STR_LEN 40
typedef unsigned char SString[MAX_STR_LEN + 1];//0号单元存放串的长度


											   /*****************生成一个其值等于chars的串T*****************/
Status StrAssign(SString T, char *chars)
{
	int i;
	if (strlen(chars) > MAX_STR_LEN)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++)
			T[i] = *(chars + i - 1);//自己输入时，是从0下标开始的
		return OK;
	}
}
/******************串S复制得串T**************************/
void StrCopy(SString T, SString S)
{
	int i;
	for (i = 0; i <= S[0]; i++)
		T[i] = S[i];
}

Status StrEmpty(SString S)
{
	if (S[0] == 0)
		return true;
	else
		return false;
}

int StrCompare(SString S, SString T)
{
	int i;
	for (i = 1; i <= S[0] && i <= T[0]; i++)
		if (S[i] != T[i])
			return S[i] - T[i];
	return S[0] - T[0];
}

int Strlength(SString S)
{
	return S[0];
}

void ClearString(SString S)
{
	S[0] = 0;
}

/*****************用T返回S1和S2连接而成的新串，诺未被截断，则返回TRUE，反正则返回FALSE**************/
Status Concat(SString T, SString S1, SString S2)
{
	int i;
	if (S1[0] + S2[0] <= MAX_STR_LEN)//未截断
	{
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i <= S2[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = S1[0] + S2[0];
		return true;
	}
	else//截断
	{
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i < MAX_STR_LEN - S1[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = MAX_STR_LEN;
		return false;
	}
}

/******************用Sub返回串S的自第pos个字符起的长度为len的子串****************/
Status SubString(SString Sub, SString S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] || len<0 || len>S[0] - pos + 1)
		return ERROR;
	for (i = 1; i <= len; i++)
		Sub[i] = S[pos + i - 1];
	Sub[0] = len;
	return OK;
}

/******返回子串T在主串S中的第pos个字符之后的位置，诺不存在，则函数值为0(1<=pos<=strlength(s))********/
int Index1(SString S, SString T, int pos)
{
	int i, j;
	if (1 <= pos&&pos <= S[0])
	{
		i = pos;
		j = 1;
		while (i <= S[0] && j <= T[0])
			if (S[i] == T[i])
			{
				++i;
				++j;
			}
			else
			{
				i = i - j + 2;
				j = 1;
			}
		if (j > T[0])
			return i - T[0];
		else
			return 0;
	}
	else
		return 0;
}


/*（1<=pos<=strlength(s)+1）*/
/*在串S的第pos个字符之前插入串T，完全插入返回TRUE，部分插入返回FALSE*/
Status StrInsert(SString S, int pos, SString T)
{
	int i;
	if (pos<1 || pos>S[0] + 1)
		return ERROR;
	if (S[0] + T[0] <= MAX_STR_LEN)//完全插入
	{
		for (i = S[0]; i >= pos; i--)
			S[T[0] + i] = S[i];
		for (i = pos; i < pos + T[0]; i++)
			S[i] = T[i - pos + 1];
		S[0] += T[0];
		return true;
	}
	else//部分插入
	{
		for (i = MAX_STR_LEN; i >= pos + T[0]; i--)
			S[i] = S[i - T[0]];
		for (i = pos; i < pos + T[0] && i <= MAX_STR_LEN; i++)
			S[i] = T[i - pos + 1];
		S[0] = MAX_STR_LEN;
		return false;
	}
}

/*****************(1<=pos<=strlength(pos)-len+1)***************/
/*从串S中删除自第pos个字符起长度为len的子串*/
Status StrDelete(SString S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S[0] - len + 1 || len < 0)
		return ERROR;
	for (i = pos + len; i <= S[0]; i++)
		S[i - len] = S[i];//向前移动删除子串的长度
	S[0] -= len;
	return OK;//删除成功的标记
}


void StrPrint(SString S)
{
	int i;
	for (i = 1; i <= S[0]; i++)
		printf("%c", S[i]);
	printf("\n");
}
/********************************KMP算法的核心****************/
void get_next(SString T, int next[])//对模式串T的next函数值并存入数组next
{
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T[0])
		if (j == 0 || T[i] == T[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
}

void get_nextval(SString T, int nextval[])//求模式串T的next函数修正值并存入数组nextval
{
	int i = 1,j = 0;
	nextval[1] = 0;
	while (i < T[0])
		if (j == 0 || T[i] == T[j])
		{
			++i;
			++j;
			if (T[i] != T[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
}

/*利用模式串的next数组求T在主串S中的第pos个字符之后的位置*/
int Index_KMP(SString S, SString T, int pos, int next[])
{
	int i = pos, j = 1;
	while (i <= S[0] && j <= T[0])
		if (j == 0 || S[i] == T[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	if (j > T[0])
		return i - T[0];
	else
		return 0;
}


