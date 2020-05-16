//有序表查找

#include<stdio.h>
#include<stdlib.h>

#define ERROR -1
#define OK 1

typedef int Status;

/****************************数值比较的约定*******************************/
#define EQ(a,b)((a)==(b))
#define LT(a,b)((a)<(b))
#define LQ(a,b)((a)<=(b))
/*************************************************************************/


/******************************数据元素的定义及操作***********************/
typedef int KeyType;

struct ElemType
{
	KeyType key;//仅有关键字域
};

void Visit(ElemType c)
{
	printf("%3d", c.key);
}

void InputFormFile(FILE *f, ElemType &c)
{
	fscanf(f, "%d", &c.key);
}

void InputKey(KeyType &k)
{
	scanf("%d", &k);
}
/************************************************************************************/

/*****************静态查找表的基本操作****************/
struct SSTable
{
	ElemType *elem;//结构体指针
	int length;//表长度
};

/*由数据文件构造静态顺序查找表*/
void Create_SeqFromFile(SSTable &ST, char *filename)
{
	int i;
	FILE *f;
	f = fopen(filename, "r");
	fscanf(f, "%d", &ST.length);//读出长度到ST.length
	ST.elem = (ElemType *)calloc(ST.length + 1, sizeof(ElemType));//（0号单元不用）
	if (!ST.elem)
		exit(EXIT_FAILURE);
	for (i = 1; i <= ST.length; i++)
		InputFormFile(f, ST.elem[i]);//读入到结构体变量中,存于结构体数组
	fclose(f);
}

/*重建静态查找为按关键字非降序排列*/
void Ascend(SSTable &ST)
{
	int i, j, k;
	for (i = 1; i < ST.length; i++)//排序算法(车轮比较)
	{
		k = i;//k存当前关键字最小的元素
		ST.elem[0] = ST.elem[i];//当前待比较的元素存于0号元素
		for (j = i + 1; j <= ST.length; j++)
			if LT(ST.elem[j].key, ST.elem[0].key)
			{
				k = j;//将当前的最小值序号存于k
				ST.elem[0] = ST.elem[j];//最小值赋给0号元素
			}
		if (k != i)//当前待比较的元素不是最小的，则交换元素
		{
			ST.elem[k] = ST.elem[i];
			ST.elem[i] = ST.elem[0];
		}
	}
}

//由含n个数据元素的数组r构造按关键字非降序查找表ST
void Create_OrdFile(SSTable &ST, char *filename)
{
	Create_SeqFromFile(ST, filename);
	Ascend(ST);
}

Status Destroy(SSTable &ST)
{
	free(ST.elem);
	ST.elem = NULL;
	ST.length = 0;
	return OK;
}

/*************查找其关键字等于key的数据元素，返回下标************/
int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	ST.elem[0].key = key;
	for (i = ST.length; !EQ(ST.elem[i].key, key); i--);
	return i;
}

//折半查找元素等于key的数据元素
int Search_Bin(SSTable ST, KeyType key)
{
	int mid, low = 1, high = ST.length;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if EQ(key, ST.elem[mid].key)
			return mid;
		else if LT(key, ST.elem[mid].key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return 0;
}

void Traverse(SSTable ST, void(*Visit)(ElemType))
{
	int i;
	ElemType *p = ++ST.elem;
	for (i = 1; i <= ST.length; i++)
		Visit(*p++);
}
/************************************************************************************/