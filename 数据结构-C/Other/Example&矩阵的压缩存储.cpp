// 矩阵的压缩存储.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Matrix.h"


int main()
{
	TSMtrix A, B, C;
	printf("创建矩阵A: ");
	CreateSMatrix(A);
	PrintSMatrix(A);
	CopySMatrix(A, B);
	printf("由矩阵A复制矩阵B:\n");
	PrintSMatrix(B);

	DestroySMatrix(B);
	printf("销毁矩阵B后: \n");
	PrintSMatrix(B);

	printf("创建矩阵B2:(与矩阵A的行，列数相同，行，列分别为%d,%d)\n", A.mu, A.nu);
	CreateSMatrix(B);
	PrintSMatrix(B);

	AddSMatrix(A, B, C);
	printf("矩阵C1(A+B):\n");
	PrintSMatrix(C);
	SubSMatrix(A, B, C);
	printf("矩阵C2(A-B):\n");
	PrintSMatrix(C);

	TransposeSMatrix(A, C);
	printf("矩阵C3(A的转置):\n");
	PrintSMatrix(C);

	printf("创建矩阵A2: ");
	CreateSMatrix(A);
	PrintSMatrix(A);

	printf("创建矩阵B3:(行数应与矩阵A2的列数相同=%d)\n", A.nu);
	CreateSMatrix(B);
	PrintSMatrix(B);

#ifndef FLAG
	MultSMatrix(A, B, C);
#else
	MultSMatrix1(A, B, C);
#endif // !FLAG
	printf("矩阵C5(A*B):\n");
	PrintSMatrix(C);
    return 0;
}

