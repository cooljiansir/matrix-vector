#ifndef __VECTOR__H
#define __VECTOR__H

class CVector
{
private:
	double *pElement;
	unsigned int nDegree;
public:
	CVector(unsigned int d=0);//���캯��1����������ά����������������Ԫ��ֵ��ʼ��Ϊ0
	CVector(unsigned int d, double* pe);//���캯��2����������ά��������Ԫ�����鴴������
	CVector(double x, double y);//���캯��3��������Ԫ�����ɶ�ά����
	CVector(double x, double y, double z);//���캯��4��������Ԫ��������ά����
	CVector(CVector& v);//���ƹ��캯��
	~CVector();//��������
	CVector operator =(const CVector& v);
	CVector& operator +(void);//����һԪ�����+
	CVector operator +(const CVector& v) const;//���ض�Ԫ�����+
	CVector& operator -(void);//����һԪ�����-
	CVector operator -(const CVector& v) const;//���ض�Ԫ�����-
	CVector operator *(const CVector& v) const;//���ض�Ԫ�����*,��ʾ�����Ĳ�ˣ���������
	double operator %(const CVector& v) const;//���ض�Ԫ�����%,��ʾ�����ĵ�ˣ���������
	CVector operator *(const double& d) const;//���ض�Ԫ�����*����ʾ����������
	double& operator [](const unsigned int & i);//���ز�����[]����ָ������Ԫ�ؽ��в���
	unsigned int GetDegree() const;//��ȡ����ά��
};

#endif