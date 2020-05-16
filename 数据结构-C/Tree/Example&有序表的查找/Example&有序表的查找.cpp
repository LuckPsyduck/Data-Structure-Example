#pragma warning (disable:4996)
#include"Staticsearchtable.h"
void main()
{
	SSTable st;
	int i;
	KeyType s;
	Create_SeqFromFile(st, "T.txt");
	printf("有序表为:\n");
	Traverse(st, Visit);
	printf("\n");
	printf("please enter key:\n");
	InputKey(s);
	i = Search_Bin(st, s);
	if (i)
		printf("%d 是第 %d 个数据的关键字\n", st.elem[i].key, i);
	else
		printf("未找到！\n");
	Destroy(st);
}
