// 字符串匹配的类定义.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iomanip>
#include<string>
#include<stdlib.h>

class String 
{
private:
	char *str;
	int len;
public:
	friend class string;

	String(char S[]);

	~String() { delete[] str; }

	int IndexBF(char T[], int pos);

	void GetNext(int next[]);

	int IndexKMP(char T[], int next[], int pos);
};

String::String(char S[])
{
	len = strlen(S);
	str = new char[len + 1];
	if (str == NULL)
		exit(1);
	for (int i = 0; i<len; i++) 
		str[i] = S[i];
	str[len] = '\0';
}

int String::IndexBF(char T[], int pos)//重pos个位置开始匹配
{
	int i, j, r, n;
	i = pos; j = 0;
	n = strlen(T);
	while ((i<len - 1 || j<n - 1) && str[j] != '\0'&&T[j] != '\0')
	{
		if (str[i] == T[j])
		{
			++i; 
			++j;
		}
		else 
		{ 
			i = i - j + 1; //重S的下一个位置开始匹配,每次从上一个开始的地方后移一位
			j = 0; //重新从T的第一个元素开始匹配
		}
	}
	if (j >= n - 1)//匹配成功
		r = i - n + 1;
	else 
		r = -1;
	return r;
}

void String::GetNext(int next[])//得到Next数组，装的是下一个需要匹配的元素位置，相当于下标
{
	int j = 0, k = -1; next[0] = -1;
	while (j<len - 1)
	{
		if (k == -1 || str[j] == str[k])
		{
			j++; //j为后缀
			k++; //k为前缀
			next[j] = k;//匹配成功则+1，后移，
		}
		else 
			k = next[k];//回溯回前缀
	}
	for (j = 0; j<len; j++)
	{
		printf("%s%d%s%d ", "next[", j, "]=", next[j]);
		if ((j + 1) % 5 == 0) 
			printf("\n");
	}
	printf("\n");
}
//注意数组的起始下标
int String::IndexKMP(char T[], int next[], int pos)//从pos处开始匹配
{
	int i, j, r, n;
	i = pos; j = 0;
	n = strlen(T); T[n] = '\0';
	while ((i<len - 1 || j<n - 1) && str[j] != '\0'&&T[j] != '\0')
	{
		if (j == 0 || str[i] == T[j])
		{
			++i;
			++j;
		}
		else 
			j = next[j];
	}
	if (j >= n - 1)
		r = i - n + 1;//返回匹配成功后，S对应的下标值
	else 
		r = -1;
	return r;
}

//串模式匹配的测试
void main()
{
	printf("%s\n", "FindSub.cpp运行结果:");
	int Index, next[30] = { 0 };
	char s1[30], t1[28];
	printf("%s\n", "GetNext-IndexKMP的结果:");
	printf("%s", "输入主串s1:");
	scanf("%s", s1);
	printf("%s", "输入模式串t1:");
	scanf("%s", t1);
	String s(s1), t(t1);
	printf("%s%d\n", "主串s1长=", strlen(s1));
	printf("%s%d\n", "模式串t1长=", strlen(t1));
	t.GetNext(next);
	Index = s.IndexKMP(t1, next, 0);
	if (Index != -1)
		printf("%s%d%s\n", "模式串在主串的位置从第", Index, "个字符开始");
	else 
		printf("%s\n", "主串s中不含模式串t");
	printf("%s\n", "IndexBF的结果:");
	Index = s.IndexBF(t1, 0);
	if (Index)
		printf("%s%d%s\n", "模式串t在主串s中的位置从第", Index, "个字符开始");
	else 
		printf("%s\n", "主串s中不含模式串t");
}



