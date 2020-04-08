#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
void main()
{
	int i = 0, n;
	int sum1 = 0, sum = 0;
	int a[100];
	printf("请输入元素个数");
	cin >> n;
	printf("请输入元素");
	for (i = 0; i < n; i++) {
		cin>>a[i];
		sum1 += a[i];
		if (sum1 > sum) {
			sum = sum1;
		}
		else if (sum1 < 0)
			sum1 = 0;
	}
	cout <<"该数组的最大字段和为"<< sum<<endl;
	system("pause");
}