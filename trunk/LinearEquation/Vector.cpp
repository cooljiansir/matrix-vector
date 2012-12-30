#include "Vector.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void CVector::show()
{
	for(int i = 0;i<nDegree;i++)
		printf("%lf ",pElement[i]);
	printf("\n");
}
CVector::CVector(unsigned int d)//构造函数1，由向量的维数创建向量，向量元素值初始化为0
{
	nDegree = d;
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector构造出错---内存分配失败"<<endl;
		return ;
	}
	for(int i = 0;i<nDegree;i++)
		pElement[i] = 0;
}
CVector::CVector(unsigned int d, double* pe)//构造函数2，由向量的维数和向量元素数组创建数组
{
	nDegree = d;
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector构造出错---内存分配失败"<<endl;
		return ;
	}
	for(int i = 0;i<nDegree;i++)
		pElement[i] = pe[i];
}
CVector::CVector(double x, double y)//构造函数3，由两个元素生成二维向量
{
	nDegree = 2;
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector构造出错---内存分配失败"<<endl;
		return ;
	}
	pElement[0] = x;
	pElement[1] = y;
}
CVector::CVector(double x, double y, double z)//构造函数4，由三个元素生成三维向量
{
	nDegree = 3;
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector构造出错---内存分配失败"<<endl;
		return ;
	}
	pElement[0] = x;
	pElement[1] = y;
	pElement[2] = z;
}
CVector::CVector(CVector& v)//复制构造函数
{
	nDegree = v.GetDegree();
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector构造出错---内存分配失败"<<endl;
		return ;
	}
	for(int i = 0;i<nDegree;i++)
		pElement[i] = v[i];
}
CVector::~CVector()//析构函数
{
	if(pElement!=NULL)
		delete []pElement;
}
CVector& CVector::operator =(CVector& v)
{
	if(nDegree!=v.GetDegree())
	{
		cout<<"“=”运算出错---维度不同！"<<endl;
		return *this;
	}
	
	for(unsigned int i = 0;i<nDegree;i++)
	{
		pElement[i] = v[i];
	}
}
CVector& CVector::operator +(void)//重载一元运算符+
{
	return *this;
}
CVector CVector::operator +(CVector& v) const//重载二元运算符+
{
	CVector vector(nDegree);
	if(nDegree!=v.GetDegree())
	{
		cout<<"CVector“+”出错---加数的维度不同！"<<endl;
		return vector;
	}
	for(int i = 0;i<nDegree;i++)
		vector[i] = v[i] + pElement[i];
	return vector;
}
CVector& CVector::operator -(void)//重载一元运算符-
{
	for(int i = 0;i<nDegree;i++)
		pElement[i] *= -1;
	return *this;
}
CVector CVector::operator -(CVector& v) const//重载二元运算符-
{
	CVector vector(nDegree);
	if(nDegree!=v.GetDegree())
	{
		cout<<"CVector“-”出错---减数的维度不同！"<<endl;
		return vector;
	}
	for(int i = 0;i<nDegree;i++)
		vector[i] = pElement[i] - v[i];
	return vector;
}
CVector CVector::operator *(CVector& v) const//重载二元运算符*,表示向量的叉乘（向量积）
{
	CVector vector(3);	
	if(v.nDegree!=3||nDegree!=3)
	{
		cout<<"Vector“*”出错---非3维向量"<<endl;
		return vector;
	}
	vector[0] = pElement[1]*v[2]-v[1]*pElement[2];
	vector[1] = pElement[2]*v[0]-pElement[0]*v[2];
	vector[2] = pElement[0]*v[1]-v[0]*pElement[1];
	return vector;
}
double CVector::operator %(CVector& v) const//重载二元运算符%,表示向量的点乘（数量积）
{
	if(nDegree!=v.GetDegree())
	{
		cout<<"CVector“%”出错---向量的维度不同！"<<endl;
		return 0;
	}
	double sum = 0;
	for(int i = 0;i<nDegree;i++)
		sum += pElement[i] * v[i];
	return sum;
}
CVector CVector::operator *(const double& d) const//重载二元运算符*，表示向量的数乘
{
	CVector vector(nDegree);
	for(int i = 0;i<nDegree;i++)
		vector[i] = d * pElement[i];
	return vector;
}
double& CVector::operator [](const unsigned int & i)//重载操作符[]，对指定向量元素进行操作
{
	return pElement[i];
}
unsigned int CVector::GetDegree() const//获取向量维数
{
	return nDegree;
}
int CVector::AddData(double pe, int n)//在n处添加一个数据，维度加一，-1即添加到最前面，返回插入的位置
{
	if(n!=-1&&!(n<nDegree))
	{
		cout<<"Vector插入一维数据失败---插入位置大于维度！"<<endl;
		return -1;
	}
	double *newVector = new double[nDegree+1];
	if(newVector==NULL)
	{
		cout<<"Vector插入一维数据失败---内存分配失败！"<<endl;
		return -1;
	}
	int i;
	nDegree++;//维度加一
	for(i = 0;i<=n;i++)
		newVector[i] = pElement[i];
	newVector[i] = pe;
	i++;
	for(;i<nDegree;i++)
		newVector[i] = pElement[i-1];
	delete []pElement;
	pElement = newVector;
	return n+1;
}
int CVector::DeleteData(unsigned int n)//在n处删除一个数据，维度减一
{
	if(!(n<nDegree))
	{
		cout<<"CVector DeleteData 出错---删除位置大于维度"<<endl;
		return -1;
	}
	double *newVector = new double[nDegree-1];
	if(newVector==NULL)
	{
		cout<<"CVector DeleteData 出错---内存分配失败！"<<endl;
		return -1;
	}
	nDegree--;//维度减一
	int i;
	for(i = 0;i<n;i++)
		newVector[i] = pElement[i];
	for(;i<nDegree;i++)
		newVector[i] = pElement[i+1];
	delete []pElement;
	pElement = newVector;
	return 0;
}