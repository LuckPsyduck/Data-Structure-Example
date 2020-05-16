// 霍夫曼编码.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define n 5                 // 5个数据 
#define m (2*n)-1           // 循环建立结点，总计为(2*n)-1 
#define maxval 10000.0
#define maxisize 100

typedef struct
{
	char ch;
	float weight;
	int lchild, rchild, parent;
}hufmtree;

typedef struct
{
	char bits[n];
	int start;//编码在位串的起始位置
	char ch;
}codetype;
//建立霍夫曼树
void huffman(hufmtree tree[])
{
	int i, j, p1, p2;
	float small1, small2, f;
	char c;
	for (i = 0; i < m; i++)//初值
	{
		tree[i].parent = 0;
		tree[i].lchild = -1;
		tree[i].rchild = -1;
		tree[i].weight = 0.0;
	}

	printf("请依次输入前%d个结点的字符及权值!\n", n);
	for (i = 0; i < n; i++)
	{
		printf("输入第%d个字符和权值: ", i + 1);
		scanf("%c %f", &c, &f);
		getchar();//去'\n'
		tree[i].ch = c;
		tree[i].weight = f;
	}

	for (i = n; i < m; i++)//进行n-1次合并，产生n-1个新结点
	{
		p1 = 0;
		p2 = 0;
		small1 = maxval;
		small2 = maxval;
		for (j = 0; j < i; j++)//选出权值最小的两个结点
			if(tree[j].parent==0)
				if (tree[j].weight < small1)  //改变最小权、次小权及对应的位置
				{                      
					small2 = small1;
					small1 = tree[j].weight;
					p2 = p1;
					p1 = j;//最小值的下标值
				}
				else
				{
					if (tree[j].weight<small2)
					{
						small2 = tree[j].weight;
						p2 = j;//次小值的下标值
					}
				}
		tree[p1].parent = i;//n到2n-2
		tree[p2].parent = i;
		tree[i].lchild = p1;
		tree[i].rchild = p2;
		tree[i].weight = tree[p1].weight + tree[p2].weight;
	}
}

void huffmancode(codetype code[], hufmtree tree[])
{
	int i, c, p;
	codetype cd;
	for (i = 0; i < n; i++)
	{
		cd.start = n;
		cd.ch = tree[i].ch;
		c = i;
		p = tree[i].parent;//n到2n-2
		while (p!=0)
		{
			cd.start--;
			if (tree[p].lchild == c)
				cd.bits[cd.start] = '0';//最低层的存的下标值大，输出为于右，由上到下排序
			else
				cd.bits[cd.start] = '1';
			c = p;
			p = tree[p].parent;
		}
		code[i] = cd;
	}
}

void decode(hufmtree tree[])
{
	int i, j = 0;
	char b[maxisize];
	char endflag = 'z';
	
	i = m - 1;
	puts("请输入发送的编码:");
	gets_s(b);
	printf("译码后的字符为:");
	while (b[j]!='z')
	{
		if (b[j] == '0')
			i = tree[i].lchild;
		else
			i = tree[i].rchild;
		if (tree[i].lchild == -1)//tree[i]是叶结点
		{
			printf("%c", tree[i].ch);
			i = m - 1;//回到根结点
		}
		j++;
	}
	printf("\n");
	if (tree[i].lchild != -1 && b[j] != 'z') //电文读完，但尚未到叶子结点
		printf("\nerror!\n");
}

int main()
{
	printf("总共有%d个字符\n", n);
	hufmtree tree[m];
	codetype code[m];

	int i, j;
	huffman(tree);
	huffmancode(code, tree);
	printf("输出每个字符的哈夫曼编码:\n");
	for (i = 0; i <n; i++)
	{
		printf("%c:", code[i].ch);
		for (j = code[i].start; j < n; j++)
			printf("%c", code[i].bits[j]);
		printf("\n");
	}
	printf("读入电文，并进行译码:\n");
	decode(tree);
    return 0;
}

