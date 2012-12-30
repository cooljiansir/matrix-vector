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
	CVector& operator =(CVector& v);
	CVector& operator +(void);//����һԪ�����+
	CVector operator +(CVector& v) const;//���ض�Ԫ�����+
	CVector& operator -(void);//����һԪ�����-
	CVector operator -(CVector& v) const;//���ض�Ԫ�����-
	CVector operator *(CVector& v) const;//���ض�Ԫ�����*,��ʾ�����Ĳ�ˣ���������
	double operator %(CVector& v) const;//���ض�Ԫ�����%,��ʾ�����ĵ�ˣ���������
	CVector operator *(const double& d) const;//���ض�Ԫ�����*����ʾ����������
	double& operator [](const unsigned int & i);//���ز�����[]����ָ������Ԫ�ؽ��в���
	int AddData(double pe, int n);//��n�����һ�����ݣ�ά�ȼ�һ��-1����ӵ���ǰ��
	int DeleteData(unsigned int n);//��n��ɾ��һ�����ݣ�ά�ȼ�һ
	unsigned int GetDegree() const;//��ȡ����ά��
	void show();//��ӡ��Ϣ
};

#endif