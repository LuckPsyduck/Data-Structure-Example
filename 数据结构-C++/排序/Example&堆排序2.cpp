// 堆排序2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include<stdlib.h>
#include<time.h>

using namespace std;

void main()
{
	const int SIZE = 10; int i, a[SIZE];

	srand(time(0));
	for (i = 0; i<SIZE; i++)
		a[i] = rand() % 80;
	vector<signed int>v(a, a + SIZE), v2;

	ostream_iterator<int> output(cout, " ");
	cout << "Vector v before make_heap:\n";
	copy(v.begin(), v.end(), output);
	make_heap(v.begin(), v.end());
	cout << "\nVector v after make_heap:\n";
	copy(v.begin(), v.end(), output);
	sort_heap(v.begin(), v.end());
	cout << "\nVector v after sort_heap:\n";
	copy(v.begin(), v.end(), output);
	// perform the heapsort with push_heap and pop_heap
	cout << "\nArray a contains: ";
	copy(a, a + SIZE, output);
	for (i = 0; i<SIZE; ++i) 
	{
		v2.push_back(a[i]);
		push_heap(v2.begin(), v2.end());//添加范围内结束时将包括在范围的现有堆的元素的元素。
		cout << "\nv2 after push_heap(a[" << i << "]): ";
		copy(v2.begin(), v2.end(), output);
	}
	for (i = 0; i<(int)v2.size(); ++i) 
	{
		cout << "\nv2 after " << v2[0] << " popped from heap\n";
		pop_heap(v2.begin(), v2.end() - i);
		copy(v2.begin(), v2.end(), output);
	}
	cout << endl; 
	cin.get();
}

