#include <iostream>
#include <stdio.h>

#include "LinearEquation.h"

using namespace std;

void testFile()
{
	cout<<"文件构造函数："<<endl;
	CLinearEquation linearEquation("test1.dat");
	linearEquation.show();
}
void testAddRow()
{
	CLinearEquation linearEquation("test1.dat");
	cout<<"A:"<<endl;
	linearEquation.show();
	cout<<"插入列"<<endl;
	double A[]={11.0,12.0};
	linearEquation.AddVariable(A,1);
	linearEquation.show();
}
void testGaussion()
{
	CMatrix matrix("test1.dat");
	cout<<"原增广矩阵："<<endl;
	matrix.show();
	CLinearEquation linearEquation("test1.dat");
	CVector vector = linearEquation.Gaussian();
	cout<<"解为："<<endl;
	vector.show();
}
int main()
{
	testGaussion();
	return 0;
}