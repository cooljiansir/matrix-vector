#include <iostream>
#include <stdio.h>

#include "LinearEquation.h"

using namespace std;

void testFile()
{
	cout<<"�ļ����캯����"<<endl;
	CLinearEquation linearEquation("test1.dat");
	linearEquation.show();
}
void testAddRow()
{
	CLinearEquation linearEquation("test1.dat");
	cout<<"A:"<<endl;
	linearEquation.show();
	cout<<"������"<<endl;
	double A[]={11.0,12.0};
	linearEquation.AddVariable(A,1);
	linearEquation.show();
}
void testGaussion()
{
	CMatrix matrix("test1.dat");
	cout<<"ԭ�������"<<endl;
	matrix.show();
	CLinearEquation linearEquation("test1.dat");
	CVector vector = linearEquation.Gaussian();
	cout<<"��Ϊ��"<<endl;
	vector.show();
}
int main()
{
	testGaussion();
	return 0;
}