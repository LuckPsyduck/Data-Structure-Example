#include"Tree2.h"
enum PointTag { Link, Thread };//link(0):指针,Thread(1):线索
struct BiThrNode
{
	TElemType data;//节点的值
	BiThrNode *lchild, *rchild;//左右孩子指针
	PointTag LTag, RTag;//左右标志
};
typedef BiThrNode * BiThrTree;

//先按先序输入线索二叉树中的节点值，构造线索二叉树。0/空格 表示空节点
void CreateBiThrTree(BiThrTree &T)
{
	TElemType ch;
	scanf(form, &ch);
	if (ch == Nil)//节点的值为空
		T = NULL;
	else
	{
		T = (BiThrTree)malloc(sizeof(BiThrNode));//生成根节点
		if (!T)
			exit(EXIT_FAILURE);
		T->data = ch;
		CreateBiThrTree(T->lchild);//递归构造左子树
		if (T->lchild)//有左孩子
			T->LTag = Link;//给左孩子标志赋值（指针）
		CreateBiThrTree(T->rchild);//递归构造右子树
		if (T->rchild)//有右孩子
			T->RTag = Link;//给右孩子标志赋值（指针）
	}
}

BiThrTree pre;//全局变量，始终指向刚刚访问过的

			  /**************通过中序遍历进行中序线索化，线索化之后pre指向最后一个节点****************/
void InThreading(BiThrTree p)
{
	if (p)
	{
		InThreading(p->lchild);//递归左子树线索化
		if (!p->lchild)//没有左孩子
		{
			p->LTag = Thread;//左孩子为线索（前驱）
			p->lchild = pre;//左孩子指针为前驱
		}
		if (!pre->rchild)//前驱没有右孩子
		{
			pre->RTag = Thread;//前驱的右标志为线索（后继）
			pre->rchild = p;//前驱右孩子指针指向其后继（当前节点p）
		}
		pre = p;//保持pre指向p的前驱
		InThreading(p->rchild);//递归右子树线索化
	}
}

/**************中序遍历二叉树T，并将其中序线索化,Thrt指向头节点**************/
void InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))//生成头节点
		exit(EXIT_FAILURE);
	Thrt->LTag = Link;//建立头节点，左标志为指针
	Thrt->RTag = Thread;//右标志为线索
	Thrt->rchild = Thrt;//右孩子指针回指
	if (!T)//诺二叉树T为空，则左孩子指针回指
		Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = T;//头结点的左孩子指针指向根节点
		pre = Thrt;//pre的初值指向头节点
		InThreading(T);//中序遍历进行中序线索化，pre指向中序遍历的最后一个节点
		pre->rchild = Thrt;//最后一个结点的右孩子指针指向头结点
		pre->RTag = Thread;//最后一个结点的右标志为线索
		Thrt->rchild = pre;//头结点的右孩子指针指向中序遍历的最后一个结点
	}
}

/**************中序遍历线索二叉树T的非递归算法**************/
void InOrderTraverse_Thr(BiThrTree T, void(*Visit)(TElemType))
{
	BiThrTree p;
	p = T->lchild;//p指向根节点
	while (p != T)//空树或遍历结束时，P==T
	{
		while (p->LTag == Link)//由根节点一直找到二叉树的最左结点
			p = p->lchild;
		Visit(p->data);//访问结点
		while (p->RTag == Thread&&p->rchild != T)//p->rchild是线索（后继），且不是遍历的最后一个结点
		{
			p = p->rchild;//p指向其后继
			Visit(p->data);//访问后继结点
		}//诺p->rchild不是线索（是右孩子），p指向右孩子，返回循环，找这颗子树中序遍历的第一个结点
		p = p->rchild;
	}
}

/**************通过先序遍历进行线索化****************************************/
void PreThreading(BiThrTree p)//根，左，右
{
	if (!pre->rchild)//p的前驱没有右孩子
	{
		pre->RTag = Thread;//pre的右孩子指针为线索
		pre->rchild = p;//p的前驱的后继指向p
	}
	if (!p->lchild)//p没有左孩子
	{
		p->LTag = Thread;//p的左孩子指针为线索
		p->lchild = pre;//p的左孩子指针指向前驱
	}
	pre = p;
	if (p->LTag == Link)//有左孩子
		PreThreading(p->lchild);
	if (p->RTag == Link)//有右孩子
		PreThreading(p->rchild);
}

/**************先序遍历二叉树T，头结点的右孩子指针指向先序遍历的最后一个结点**************/
void PreOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))//生成头节点
		exit(EXIT_FAILURE);
	Thrt->LTag = Link;//左标志为指针(孩子)
	Thrt->RTag = Thread;//右标志为线索
	Thrt->rchild = Thrt;//右孩子指针回指
	if (!T)//诺二叉树T为空，则左孩子指针回指
		Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = T;//头结点的左孩子指针指向根节点
		pre = Thrt;//pre的初值指向头节点
		PreThreading(T);//中序遍历进行中序线索化，pre指向中序遍历的最后一个节点
		pre->RTag = Thread;//最后一个结点的右标志为线索
		pre->rchild = Thrt;//最后一个结点的右孩子指针指向头结点
		Thrt->rchild = pre;//头结点的右孩子指针指向中序遍历的最后一个结点
	}
}

/**************先序遍历线索二叉树T的非递归算法**************/
void PreOrderTraverse_Thr(BiThrTree T, void(*Visit)(TElemType))
{
	BiThrTree p;
	p = T->lchild;//p指向根节点
	while (p != T)//空树或遍历结束时，P==T
	{
		Visit(p->data);//访问结点
		if (p->LTag == Link)//左孩子
			p = p->lchild;
		else
			p = p->rchild;//p指向右孩子或右继
	}
}

/**************通过后序序遍历进行线索化****************************************/
void PostThreading(BiThrTree p)//根，左，右
{
	if (p)
	{
		PostThreading(p->lchild);
		PostThreading(p->rchild);
		if (!p->lchild)//p没有左孩子
		{
			p->LTag = Thread;//p的左孩子指针为线索
			p->lchild = pre;//p的左孩子指针指向前驱
		}
		if (!pre->rchild)//p的前驱没有右孩子
		{
			pre->RTag = Thread;//pre的右孩子指针为线索
			pre->rchild = p;//p的前驱的后继指向p
		}
		pre = p;
	}
}

/**************后序遍历二叉树T，头结点的右孩子指针指向先序遍历的最后一个结点**************/
void PostOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))//生成头节点
		exit(EXIT_FAILURE);
	Thrt->LTag = Link;//左标志为指针(孩子)
	Thrt->RTag = Thread;//右标志为线索
	Thrt->rchild = Thrt;//右孩子指针回指
	if (!T)//诺二叉树T为空，则左孩子指针回指
		Thrt->lchild = Thrt;
	else
	{
		Thrt->lchild = Thrt->rchild = T;//头结点的左孩子指针指向根节点
		pre = Thrt;//pre的初值指向头节点
		PostThreading(T);//后序遍历进行后序线索化，pre指向后序遍历的最后一个节点
		if (pre->RTag != Link)
		{
			pre->RTag = Thread;//最后一个结点的右标志为线索
			pre->rchild = Thrt;//最后一个结点的右孩子指针指向头结点
		}
	}
}

void PostOrderTraverse_Thr(BiThrTree T, void(*Visit)(TElemType))
{

}
/********************删除二叉树********************************************/
void DestotyBiThree(BiThrTree &T)
{
	if (T)
	{
		if (T->LTag == Link)
			DestotyBiThree(T->lchild);
		if (T->RTag == Link)
			DestotyBiThree(T->rchild);
		free(T);
		T = NULL;
	}
}


/********************删除头结点********************************************/
void DestroyBiThrThree(BiThrTree &Thrt)
{
	if (Thrt)
	{
		if (Thrt->lchild)
			DestotyBiThree(Thrt->lchild);//删除根结点
		free(Thrt);
		Thrt = NULL;
	}
}

