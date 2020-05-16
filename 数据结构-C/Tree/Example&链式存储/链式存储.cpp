#include"BinaryTree.h"
#define CHAR 1
//#define CHAR 0

void visit(TElemType e)
{
	printf("%2c", e);
}

void main()
{
	int i;
	BiTree T, p, c;
	TElemType e1, e2;
	InitBiTree(T);

	printf("构造空二叉树后，树空否？%d(1 空 0 否)。树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
	e1 = Root(T);
	if (e1 != Nil)
		printf("二叉树的根为%c\n", e1);
	else
		printf("树空，无根\n");
#if CHAR
	printf("请按先序输入二叉树：\n");//char
#else
	printf("请按先序输入二叉树：\n");//int
#endif

	CreateBiTree(T);
	printf("建立二叉树后，树为空否？%d(1 空 0 非空)。树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
	e1 = Root(T);
	if (e1 != Nil)
		printf("二叉树的根为%c\n", e1);
	else
		printf("树空，无根\n");

	printf("中序遍历二叉树:\n");
	InOrderTraverse(T, visit);

	printf("\n后序遍历二叉树:\n");
	PostOrderTraverse(T, visit);
	printf("\n");

	printf("请输入一个结点的值:");
	getchar();
	scanf("%c", &e1);
	p = Point(T, e1);

	printf("结点的值为 %c \n", Value(p));

	printf("欲改变此结点的值，请输入新值:");
	getchar();
	scanf("%c", &e2);
	getchar();
	Assign(p, e2);

	printf("层遍历二叉树:\n");
	LevelOrderTraverse(T, visit);

	e1 = Parent(T, e2);
	if (e1 != Nil)
		printf("%c的双亲是%c ", e2, e1);
	else
		printf("%c没有双亲 ", e2);
	e1 = LeftChild(T, e2);
	if (e1 != Nil)
		printf("左孩子是%c ", e1);
	else
		printf("没有左孩子");

	e1 = RightChild(T, e2);
	if (e1 != Nil)
		printf("右孩子是%c ", e1);
	else
		printf("没有右孩子 ");

	e1 = LeftSibling(T, e2);
	if (e1 != Nil)
		printf("左兄弟是%c ", e1);
	else
		printf("没有左兄弟 ");

	e1 = RightSibling(T, e2);//右子树的结果有问题
	if (e1 != Nil)
		printf("右兄弟是%c ", e1);
	else
		printf("没有右兄弟 ");

	InitBiTree(c);
	printf("\n");
	printf("请构造一个右子树为空的二叉树c:\n");
#if CHAR
	printf("请按先序输入二叉树(空格):\n");
#else
	printf("请按先序输入二叉树(0):\n");
#endif

	CreateBiTree(c);
	printf("中序递归遍历二叉树c:\n");
	InOrderTraverse(c, visit);
	printf("\n");

	printf("树c插到树T中，请输入T中树c的双亲结点左（0）右（1）子树:");
	getchar();
	scanf("%c %d", &e1, &i);
	getchar();
	p = Point(T, e1);

	InsertChild(p, i, c);
	printf("先序递归遍历二叉树:\n ");
	PreOrderTraverse(T, visit);
	printf("\n");

	printf("删除子树，请输入待删除子树的双亲结点，左（0）右（1）子树:");
	//getchar();
	scanf("%c %d", &e1, &i);
	p = Point(T, e1);
	DeleteChild(p, i);

	printf("先序递归遍历二叉树:\n");
	PreOrderTraverse(T, visit);
	printf("\n");
	printf("中序非递归遍历二叉树:\n");
	InOrderTraverse1(T, visit);
	printf("\n");
	printf("中序非递归遍历二叉树:\n");
	InOrderTraverse2(T, visit);
	DestroyBiTree(T);
}