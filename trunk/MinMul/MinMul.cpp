#include "MinMul.h"
#include <iostream>
#include <stdio.h>

using namespace std;

CMinMul::CMinMul(double *x,double *y,unsigned int n)//���캯��1
{
	X = new double[n];
	Y = new double[n];
	if(X==NULL||Y==NULL)
	{
		cout<<"CMinMul �������---�ڴ����ʧ�ܣ�"<<endl;
		return;
	}
	nPoint = n;
	for(int i = 0;i<nPoint;i++)
		X[i] = x[i],Y[i] = y[i];
}
CMinMul::CMinMul(unsigned int n)//���캯��2��nΪ��ĸ�������0���
{
	X = new double[n];
	Y = new double[n];
	if(X==NULL||Y==NULL)
	{
		cout<<"CMinMul �������---�ڴ����ʧ�ܣ�"<<endl;
		return;
	}
	nPoint = n;
	for(int i = 0;i<nPoint;i++)
		X[i] = Y[i] = 0;
}
/*
*�ļ���ʽ�涨:
*��Ҫ�����
*-------------------------------------------------
*|Xi| 1  |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
*-------------------------------------------------
*|Yi| 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
*-------------------------------------------------
*
*�����ʽ��
*1,2,3,4,5,6,7,8,9
*11,12,13,14,15,16,17,18,19
*���������У�����һ��ΪX������һ��ΪY
*
*
*/
CMinMul::CMinMul(char *pFile)//���캯��3��ͨ���ļ���ȡ����
{
	CMatrix matrix(pFile);//ʹ�þ�����ļ���
	double *x,*y;
	int n = matrix.GetColumnsNum();
	x = matrix.DeleteRow(0);
	y = matrix.DeleteRow(0);
	CMinMul(x,y,n);
}
CMinMul::CMinMul(const CMinMul& b)//���캯��4,�������캯��
{
	int n = b.getPointNums();
	X = new double[n];
	Y = new double[n];
	if(X==NULL||Y==NULL)
	{
		cout<<"CMinMul �������---�ڴ����ʧ�ܣ�"<<endl;
		return;
	}
	nPoint = n;
	for(int i = 0;i<nPoint;i++)
		X[i] = b.getXat(i),Y[i] = b.getYat(i);
}
CMinMul::~CMinMul()//��������
{
	if(X!=NULL)
		delete []X;
	if(Y!=NULL)
		delete []Y;
}
CMinMul& CMinMul::operator = (const CMinMul &b)//���ط�ֵ�����
{
	if(this->nPoint!=b.getPointNums())
	{
		cout<<"CMinMul ��=���������---������ͬ��"<<endl;
		return *this;
	}
	for(int i = 0;i<nPoint;i++)
		X[i] = b.getXat(i),Y[i] = b.getYat(i);
	return *this;
}
CVector CMinMul::getCoe(int maxPower)//��С���˷������(a1,a2,a3,a4...an),maxPowerΪ��ߴ���
{
	if(!(maxPower<nPoint))
	{
		cout<<"CMinMul getCoe����---��ϵ���ߴ���>=����������"<<endl;
		return NULL;
	}
	int Column = maxPower+1;
	CMatrix C(nPoint,Column);
	for(int i = 0;i<nPoint;i++)
		C(i,0) = 1;
	for(int j = 1;j<Column;j++)
		for(int i = 0;i<nPoint;i++)
			C(i,j) = X[i] * C(i,j-1);
	CMatrix CT = C.Tranpose();
	CVector vectorY(nPoint,Y);
	CLinearEquation linearEquation(CT*C,CT*vectorY);
	return linearEquation.Gaussian();
}
unsigned int CMinMul::getPointNums() const//��ĸ���
{
	return nPoint;
}
double CMinMul::getXat(int i) const//��ȡ�±�Ϊi��X
{
	return X[i];
}
double CMinMul::getYat(int i) const//��ȡ�±�Ϊi��Y
{
	return Y[i];
}
void CMinMul::setXat(int i,double b)//�����±�Ϊi��X
{
	X[i] = b;
}
void CMinMul::setYat(int i,double b)//�����±�Ϊi��Y
{
	Y[i] = b;
}