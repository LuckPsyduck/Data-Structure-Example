/********************堆分配存储表示**************************/

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

typedef int QElemType;

struct HString
{
	char *ch;
	int length;
};

//产生空串
void InitString(HString &S)
{
	S.length = 0;
	S.ch = NULL;
}

void ClearString(HString &S)
{
	free(S.ch);
	InitString(S);
}
//生成一个其值等于串常量chars的串T
void StrAssign(HString &T, char *chars)
{
	int i, j;
	if (T.ch)
		free(T.ch);
	i = strlen(chars);
	if (!i)
		InitString(T);//生成空串
	else
	{
		T.ch = (char *)malloc(i * sizeof(char));
		if (!T.ch)
			exit(EXIT_FAILURE);
		for (j = 0; j < i; j++)
			T.ch[j] = chars[j];
		T.length = i;
	}
}
//串S赋值得到串T
void StrCopy(HString &T, HString S)
{
	int i;
	if (T.ch)
		free(T.ch);
	T.ch = (char*)malloc(S.length * sizeof(char));
	if (!T.ch)
		exit(EXIT_FAILURE);
	for (i = 0; i < S.length; i++)
		T.ch[i] = S.ch[i];
	T.length = S.length;
}

Status StrEmpty(HString S)
{
	if (S.length == 0 && S.ch == NULL)
		return true;
	else
		return false;
}

int StrCompare(HString S, HString T)
{
	int i;
	for (i = 0; i < S.length&&i < T.length; ++i)
		if (S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	return S.length - T.length;
}

int StrLength(HString S)
{
	return S.length;
}
//用T返回S1和S2连接而成的长度
void Concat(HString &T, HString S1, HString S2)
{
	int i;
	if (T.ch)
		free(T.ch);
	T.length = S1.length + S2.length;
	T.ch = (char*)malloc(T.length * sizeof(char));
	if (!T.ch)
		exit(EXIT_FAILURE);
	for (i = 0; i < S1.length; i++)
		T.ch[i] = S1.ch[i];
	for (i = 0; i < S2.length; i++)
		T.ch[i+S1.length] = S1.ch[i];
}
//用sub返回串S的第pos个字符起长度为len的子串
Status SubString(HString &Sub, HString S, int pos, int len)
{
	int i;
	if (pos<1 || pos>S.length || len<0 || len>S.length - pos + 1)
		return ERROR;
	if (Sub.ch)
		free(Sub.ch);
	if (!len)//空子串
		InitString(Sub);//初始化空子串
	else
	{
		Sub.ch = (char*)malloc(len * sizeof(char));
		if (!Sub.ch)
			exit(EXIT_FAILURE);
		for (i = 0; i <= len - 1; i++)
			Sub.ch[i] = S.ch[pos - 1 + i];
		Sub.length = len;
	}
	return OK;
}
//在串S的第pos个字符之前插入串T
Status StrInsert(HString &S, int pos, HString T)
{
	int i;
	if (pos<1 || pos>S.length + 1)
		return ERROR;
	if (T.length)
	{
		S.ch = (char*)realloc(S.ch, (S.length + T.length) * sizeof(char));
		if (!S.length)
			exit(EXIT_FAILURE);
		for (i = S.length - 1; i >= pos - 1; --i)
			S.ch[i + T.length] = S.ch[i];
		for (i = 0; i < T.length; i++)
			S.ch[pos - 1 + i] = T.ch[i];
		S.length += T.length;
	}
	return OK;
}
//从串S中删除第pos个字符起长度为len 的子串
Status StrDelete(HString &S, int pos, int len)
{
	int i;
	if (S.length < pos + len - 1)
		return ERROR;
	for (i = pos - 1; i <= S.length - len; i++)
		S.ch[i] = S.ch[i + len];
	S.length -= len;
	S.ch = (char*)realloc(S.ch, S.length * sizeof(char));//重新分配串S的存储空间（减少）
	return OK;
}

void StrPrint(HString S)
{
	int i;
	for (i = 0; i < S.length; i++)
		printf("%c", S.ch[i]);
	printf("\n");
}