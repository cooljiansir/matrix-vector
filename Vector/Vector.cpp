#include "Vector.h"
#include <iostream>
#include <stdio.h>

using namespace std;


CVector::CVector(unsigned int d)//构造函数1，由向量的维数创建向量，向量元素值初始化为0
{

}
CVector::CVector(unsigned int d, double* pe)//构造函数2，由向量的维数和向量元素数组创建数组
{

}
CVector::CVector(double x, double y)//构造函数3，由两个元素生成二维向量
{

}
CVector::CVector(double x, double y, double z)//构造函数4，由三个元素生成三维向量
{

}
CVector::CVector(CVector& v)//复制构造函数
{

}
CVector::~CVector()//析构函数
{

}
CVector CVector::operator =(const CVector& v)
{

}
CVector& CVector::operator +(void)//重载一元运算符+
{

}
CVector CVector::operator +(const CVector& v) const//重载二元运算符+
{

}
CVector& CVector::operator -(void)//重载一元运算符-
{

}
CVector CVector::operator -(const CVector& v) const//重载二元运算符-
{

}
CVector CVector::operator *(const CVector& v) const//重载二元运算符*,表示向量的叉乘（向量积）
{

}
double CVector::operator %(const CVector& v) const//重载二元运算符%,表示向量的点乘（数量积）
{

}
CVector CVector::operator *(const double& d) const//重载二元运算符*，表示向量的数乘
{

}
double& CVector::operator [](const unsigned int & i)//重载操作符[]，对指定向量元素进行操作
{

}
unsigned int CVector::GetDegree() const//获取向量维数
{

}