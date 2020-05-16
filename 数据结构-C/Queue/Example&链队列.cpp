#include"Queue.h"

void print(QElemType c)
{
	printf("%3d", c);
}
void main()
{
	int i;
	QElemType d;
	LinkQueue q;
	InitQueue(q);
	printf("成功地构造了一个空队列\n");
	printf("是否空队列？%d(1 空 0 非空),", QueueEmpty(q));
	printf("队列的长度为%d\n", QueueLength(q));

	EnQueue(q, -5);
	EnQueue(q, 5);
	EnQueue(q, 10);

	printf("插入3个元素(-5,5,10)后，队列的长度为:%3d\n", QueueLength(q));
	printf("是否空队列?%d(1 空 0 非空),", QueueEmpty(q));
	printf("队列的元素依次为\n");

	QueueTraverse(q, print);
	i = GetHead(q, d);
	if (i == OK)
		printf("队头元素是%d", d);

	ClearQueue(q);
	printf("清空队列后，q.front=%p,q.rear=%p,q.front->next=%p\n", q.front, q.rear, q.front->next);

	DestroyQueue(q);
	printf("销毁队列后，q.front=%p,q.rear=%p\n", q.front, q.rear);
}