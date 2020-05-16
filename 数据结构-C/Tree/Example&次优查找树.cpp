// 次优查找树.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef struct TreeNode
{
	char data;
	int weight;
	struct TreeNode *lchild, *rchild;	
}TreeNode;

void init_tree(TreeNode *root)
{
	root = NULL;
	printf("init success!\n");
}

TreeNode *SecondOptimal(TreeNode *root, char R[], int sw[], int low, int high)
{
	int i = low;
	int min = fabs(sw[high] - sw[low]);//计算公式
	int dw = sw[high] + sw[low - 1];//初值
	int j=0;
	for (j = low + 1; j <= high; ++j)
		if (fabs(dw - sw[j] - sw[j - 1]) < min)
		{
			i = j;//最小的索引值
			min = fabs(dw - sw[j] - sw[j - 1]);
		}

	root = (TreeNode *)malloc(sizeof(TreeNode));
	root->data = R[i];
	if (i == low)
		root->lchild = NULL;
	else
		root->lchild = SecondOptimal(root->lchild, R, sw,low, i - 1);//左子树建立,向左边查找
	if (i == high)
		root->rchild = NULL;
	else
		root->rchild= SecondOptimal(root->lchild, R, sw, i+1, high);
	return root;
}

void pre_order(TreeNode *root)
{
	if (root)
	{
		putchar(root->data);
		pre_order(root->lchild);
		pre_order(root->rchild);
	}
}

void in_order(TreeNode *root)
{
	if (root)
	{
		in_order(root->lchild);
		putchar(root->data);
		in_order(root->rchild);
	}
}

void post_order(TreeNode *root)
{
	if (root)
	{
		post_order(root->lchild);
		post_order(root->rchild);
		putchar(root->data);
	}
}

int search_tree(TreeNode *root, char key)
{
	if (root == NULL)
		return 0;
	else
	{
		if (root->data == key)
			return 1;
		else
		{
			if (search_tree(root->lchild, key) || search_tree(root->rchild, key))
				return 1;
			else
				return 0;
		}
	}
}

int main()
{
	TreeNode *root=NULL;
	int low = 1; int high = 10;
	int *weight, *sw;
	char *R;
	int i, j;
	char ch;
	init_tree(root);
	R = (char *)malloc(high * sizeof(char));
	for (i = low; i < high; i++)
		R[i] = 'A' + i - 1;
	printf("构造次优查找树的点R[]:\n");
	for (i = low; i < high; i++)
		printf("%-5c", R[i]);
	printf("\n");
	weight = (int*)malloc(high * sizeof(int));
	weight[0] = 0;//没有实际意义
	weight[1] = 1;
	weight[2] = 1;
	weight[3] = 2;
	weight[4] = 5;
	weight[5] = 3;
	weight[6]=  4;
	weight[7] = 4;
	weight[8] = 3;
	weight[9] = 5;
	printf("构造次优查找树的权值weight[]:\n");
	for (i = low; i < high; i++)
		printf("%-5d", weight[i]);
	printf("\n");

	sw = (int *)malloc(sizeof(int)*high);
	sw[0] = 0;
	for (i = low; i < high; i++)
		sw[i] = sw[i - 1] + weight[i];
	printf("构造次优查找树的点的累计权值sw[]:\n");
	for (i = low; i < high; i++)
		printf("%-5d", sw[i]);

	root = SecondOptimal(root, R, sw, low, high - 1);
	printf("\n前序遍历序列是:\n");
	pre_order(root);
	printf("\n");
	printf("中序遍历序列是:\n");
	in_order(root);
	printf("\n");
	printf("后序遍历序列是:\n");
	post_order(root);
	printf("\n");

	printf("输入要查找的元素!\n");

	scanf("%c",&ch);
	if (search_tree(root, ch) == 1)
		printf("yes!\n");
	else
		printf("no!\n");
    return 0;
}

