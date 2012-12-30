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
CVector::CVector(unsigned int d)//���캯��1����������ά����������������Ԫ��ֵ��ʼ��Ϊ0
{
	nDegree = d;
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector�������---�ڴ����ʧ��"<<endl;
		return ;
	}
	for(int i = 0;i<nDegree;i++)
		pElement[i] = 0;
}
CVector::CVector(unsigned int d, double* pe)//���캯��2����������ά��������Ԫ�����鴴������
{
	nDegree = d;
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector�������---�ڴ����ʧ��"<<endl;
		return ;
	}
	for(int i = 0;i<nDegree;i++)
		pElement[i] = pe[i];
}
CVector::CVector(double x, double y)//���캯��3��������Ԫ�����ɶ�ά����
{
	nDegree = 2;
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector�������---�ڴ����ʧ��"<<endl;
		return ;
	}
	pElement[0] = x;
	pElement[1] = y;
}
CVector::CVector(double x, double y, double z)//���캯��4��������Ԫ��������ά����
{
	nDegree = 3;
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector�������---�ڴ����ʧ��"<<endl;
		return ;
	}
	pElement[0] = x;
	pElement[1] = y;
	pElement[2] = z;
}
CVector::CVector(CVector& v)//���ƹ��캯��
{
	nDegree = v.GetDegree();
	pElement = new double[nDegree];
	if(pElement==NULL)
	{
		cout<<"CVector�������---�ڴ����ʧ��"<<endl;
		return ;
	}
	for(int i = 0;i<nDegree;i++)
		pElement[i] = v[i];
}
CVector::~CVector()//��������
{
	if(pElement!=NULL)
		delete []pElement;
}
CVector& CVector::operator =(CVector& v)
{
	if(nDegree!=v.GetDegree())
	{
		cout<<"��=���������---ά�Ȳ�ͬ��"<<endl;
		return *this;
	}
	
	for(unsigned int i = 0;i<nDegree;i++)
	{
		pElement[i] = v[i];
	}
}
CVector& CVector::operator +(void)//����һԪ�����+
{
	return *this;
}
CVector CVector::operator +(CVector& v) const//���ض�Ԫ�����+
{
	CVector vector(nDegree);
	if(nDegree!=v.GetDegree())
	{
		cout<<"CVector��+������---������ά�Ȳ�ͬ��"<<endl;
		return vector;
	}
	for(int i = 0;i<nDegree;i++)
		vector[i] = v[i] + pElement[i];
	return vector;
}
CVector& CVector::operator -(void)//����һԪ�����-
{
	for(int i = 0;i<nDegree;i++)
		pElement[i] *= -1;
	return *this;
}
CVector CVector::operator -(CVector& v) const//���ض�Ԫ�����-
{
	CVector vector(nDegree);
	if(nDegree!=v.GetDegree())
	{
		cout<<"CVector��-������---������ά�Ȳ�ͬ��"<<endl;
		return vector;
	}
	for(int i = 0;i<nDegree;i++)
		vector[i] = pElement[i] - v[i];
	return vector;
}
CVector CVector::operator *(CVector& v) const//���ض�Ԫ�����*,��ʾ�����Ĳ�ˣ���������
{
	CVector vector(3);	
	if(v.nDegree!=3||nDegree!=3)
	{
		cout<<"Vector��*������---��3ά����"<<endl;
		return vector;
	}
	vector[0] = pElement[1]*v[2]-v[1]*pElement[2];
	vector[1] = pElement[2]*v[0]-pElement[0]*v[2];
	vector[2] = pElement[0]*v[1]-v[0]*pElement[1];
	return vector;
}
double CVector::operator %(CVector& v) const//���ض�Ԫ�����%,��ʾ�����ĵ�ˣ���������
{
	if(nDegree!=v.GetDegree())
	{
		cout<<"CVector��%������---������ά�Ȳ�ͬ��"<<endl;
		return 0;
	}
	double sum = 0;
	for(int i = 0;i<nDegree;i++)
		sum += pElement[i] * v[i];
	return sum;
}
CVector CVector::operator *(const double& d) const//���ض�Ԫ�����*����ʾ����������
{
	CVector vector(nDegree);
	for(int i = 0;i<nDegree;i++)
		vector[i] = d * pElement[i];
	return vector;
}
double& CVector::operator [](const unsigned int & i)//���ز�����[]����ָ������Ԫ�ؽ��в���
{
	return pElement[i];
}
unsigned int CVector::GetDegree() const//��ȡ����ά��
{
	return nDegree;
}
int CVector::AddData(double pe, int n)//��n�����һ�����ݣ�ά�ȼ�һ��-1����ӵ���ǰ�棬���ز����λ��
{
	if(n!=-1&&!(n<nDegree))
	{
		cout<<"Vector����һά����ʧ��---����λ�ô���ά�ȣ�"<<endl;
		return -1;
	}
	double *newVector = new double[nDegree+1];
	if(newVector==NULL)
	{
		cout<<"Vector����һά����ʧ��---�ڴ����ʧ�ܣ�"<<endl;
		return -1;
	}
	int i;
	nDegree++;//ά�ȼ�һ
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
int CVector::DeleteData(unsigned int n)//��n��ɾ��һ�����ݣ�ά�ȼ�һ
{
	if(!(n<nDegree))
	{
		cout<<"CVector DeleteData ����---ɾ��λ�ô���ά��"<<endl;
		return -1;
	}
	double *newVector = new double[nDegree-1];
	if(newVector==NULL)
	{
		cout<<"CVector DeleteData ����---�ڴ����ʧ�ܣ�"<<endl;
		return -1;
	}
	nDegree--;//ά�ȼ�һ
	int i;
	for(i = 0;i<n;i++)
		newVector[i] = pElement[i];
	for(;i<nDegree;i++)
		newVector[i] = pElement[i+1];
	delete []pElement;
	pElement = newVector;
	return 0;
}