#include<stdio.h>
#include<stdlib.h>
/*
小于最小则放到最前面。大于最大则放到最后面，两者之间，则折半查找
*/

void insert_sort(int *arr, int *temp, int n)
{
	int i, first, final, k;
	first = final = 0;
	temp[0] = arr[0];
	for (i = 1; i < n; i++)
	{
		if (arr[i] < temp[first])
		{
			first = (first - 1 + n) % n;//first 前移
			temp[first] = arr[i];//放到最前面
		}
		else if(arr[i]>temp[final])
		{
			final = (final + 1 + n) % n;//final后移
			temp[final] = arr[i];//放到最后面
		}
		else//在first和final之间
		{
			k = (final + 1 + n) % n;//最后一个的下一位
			while (temp[(k - 1 + n) % n] > arr[i])//由后向前找合适的位置
			{
				temp[(k + n) % n] = temp[(k - 1 + n) % n];//后移，为插入做准备
				k = (k - 1 + n) % n;
			}
			temp[(k + n) % n] = arr[i];//插入
			final = (final + 1 + n) % n;//更新最后一位位置
		}
	}
	for (k = 0; k < n; k++)//传回到arr数组中
		arr[k] = temp[(first + k) % n];
}

void main()
{
	int i, n, *arr,*temp;
	printf("input n:\n");
	while (scanf("%d", &n) == 1)
	{
		arr = (int*)malloc(sizeof(int)*n);
		temp = (int *)malloc(sizeof(int)*n);
		printf("arr:\n");
		for (i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		insert_sort(arr, temp, n);
		puts("after sort:");
		for (i = 0; i < n; i++)
			printf("%d ", arr[i]);
		printf("\n");
		free(arr);
		free(temp);
	}
}