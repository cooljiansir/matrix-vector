#include "Vector.h"
#include <iostream>
#include <stdio.h>

using namespace std;


CVector::CVector(unsigned int d)//���캯��1����������ά����������������Ԫ��ֵ��ʼ��Ϊ0
{

}
CVector::CVector(unsigned int d, double* pe)//���캯��2����������ά��������Ԫ�����鴴������
{

}
CVector::CVector(double x, double y)//���캯��3��������Ԫ�����ɶ�ά����
{

}
CVector::CVector(double x, double y, double z)//���캯��4��������Ԫ��������ά����
{

}
CVector::CVector(CVector& v)//���ƹ��캯��
{

}
CVector::~CVector()//��������
{

}
CVector CVector::operator =(const CVector& v)
{

}
CVector& CVector::operator +(void)//����һԪ�����+
{

}
CVector CVector::operator +(const CVector& v) const//���ض�Ԫ�����+
{

}
CVector& CVector::operator -(void)//����һԪ�����-
{

}
CVector CVector::operator -(const CVector& v) const//���ض�Ԫ�����-
{

}
CVector CVector::operator *(const CVector& v) const//���ض�Ԫ�����*,��ʾ�����Ĳ�ˣ���������
{

}
double CVector::operator %(const CVector& v) const//���ض�Ԫ�����%,��ʾ�����ĵ�ˣ���������
{

}
CVector CVector::operator *(const double& d) const//���ض�Ԫ�����*����ʾ����������
{

}
double& CVector::operator [](const unsigned int & i)//���ز�����[]����ָ������Ԫ�ؽ��в���
{

}
unsigned int CVector::GetDegree() const//��ȡ����ά��
{

}