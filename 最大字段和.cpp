#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
void main()
{
	int i = 0, n;
	int sum1 = 0, sum = 0;
	int a[100];
	printf("������Ԫ�ظ���");
	cin >> n;
	printf("������Ԫ��");
	for (i = 0; i < n; i++) {
		cin>>a[i];
		sum1 += a[i];
		if (sum1 > sum) {
			sum = sum1;
		}
		else if (sum1 < 0)
			sum1 = 0;
	}
	cout <<"�����������ֶκ�Ϊ"<< sum<<endl;
	system("pause");
}