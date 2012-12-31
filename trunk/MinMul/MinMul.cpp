#include "MinMul.h"
#include <iostream>
#include <stdio.h>

using namespace std;

CMinMul::CMinMul(double *x,double *y,unsigned int n)//构造函数1
{
	X = new double[n];
	Y = new double[n];
	if(X==NULL||Y==NULL)
	{
		cout<<"CMinMul 构造出错---内存分配失败！"<<endl;
		return;
	}
	nPoint = n;
	for(int i = 0;i<nPoint;i++)
		X[i] = x[i],Y[i] = y[i];
}
CMinMul::CMinMul(unsigned int n)//构造函数2，n为点的个数，以0填充
{
	X = new double[n];
	Y = new double[n];
	if(X==NULL||Y==NULL)
	{
		cout<<"CMinMul 构造出错---内存分配失败！"<<endl;
		return;
	}
	nPoint = n;
	for(int i = 0;i<nPoint;i++)
		X[i] = Y[i] = 0;
}
/*
*文件格式规定:
*如要输入表
*-------------------------------------------------
*|Xi| 1  |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |
*-------------------------------------------------
*|Yi| 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
*-------------------------------------------------
*
*输入格式：
*1,2,3,4,5,6,7,8,9
*11,12,13,14,15,16,17,18,19
*即输入两行，上面一行为X，下面一行为Y
*
*
*/
CMinMul::CMinMul(char *pFile)//构造函数3，通过文件读取构造
{
	CMatrix matrix(pFile);//使用矩阵的文件读
	double *x,*y;
	int n = matrix.GetColumnsNum();
	x = matrix.DeleteRow(0);
	y = matrix.DeleteRow(0);
	CMinMul(x,y,n);
}
CMinMul::CMinMul(const CMinMul& b)//构造函数4,拷贝构造函数
{
	int n = b.getPointNums();
	X = new double[n];
	Y = new double[n];
	if(X==NULL||Y==NULL)
	{
		cout<<"CMinMul 构造出错---内存分配失败！"<<endl;
		return;
	}
	nPoint = n;
	for(int i = 0;i<nPoint;i++)
		X[i] = b.getXat(i),Y[i] = b.getYat(i);
}
CMinMul::~CMinMul()//析构函数
{
	if(X!=NULL)
		delete []X;
	if(Y!=NULL)
		delete []Y;
}
CMinMul& CMinMul::operator = (const CMinMul &b)//重载幅值运算符
{
	if(this->nPoint!=b.getPointNums())
	{
		cout<<"CMinMul “=”运算出错---点数不同！"<<endl;
		return *this;
	}
	for(int i = 0;i<nPoint;i++)
		X[i] = b.getXat(i),Y[i] = b.getYat(i);
	return *this;
}
CVector CMinMul::getCoe(int maxPower)//最小二乘法求解结果(a1,a2,a3,a4...an),maxPower为最高次数
{
	if(!(maxPower<nPoint))
	{
		cout<<"CMinMul getCoe出错---拟合的最高次数>=参数个数！"<<endl;
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
unsigned int CMinMul::getPointNums() const//点的个数
{
	return nPoint;
}
double CMinMul::getXat(int i) const//获取下标为i的X
{
	return X[i];
}
double CMinMul::getYat(int i) const//获取下标为i的Y
{
	return Y[i];
}
void CMinMul::setXat(int i,double b)//设置下标为i的X
{
	X[i] = b;
}
void CMinMul::setYat(int i,double b)//设置下标为i的Y
{
	Y[i] = b;
}