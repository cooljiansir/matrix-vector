#ifndef __MIN_MUL__H
#define __MIN_MUL__H

#include "LinearEquation.h"

class CMinMul
{
private:
	double *X;//X����
	double *Y;//Y����
	unsigned int nPoint;//�����
public:
	CMinMul(double *x,double *y,unsigned int n);//���캯��1
	CMinMul(unsigned int n);//���캯��2��nΪ��ĸ�������0���
	CMinMul(char *pFile);//���캯��3��ͨ���ļ���ȡ����
	CMinMul(const CMinMul& b);//���캯��4,�������캯��
	~CMinMul();//��������
	CMinMul& operator = (const CMinMul &b);//���ط�ֵ�����
	CVector getCoe(int maxPower);
	//��С���˷������(a0,a1,a2,a3,a4...an),maxPowerΪ��ߴ���n
	unsigned int getPointNums()const;//��ĸ���
	double getXat(int i) const;//��ȡ�±�Ϊi��X
	double getYat(int i) const;//��ȡ�±�Ϊi��Y
	void setXat(int i,double b);//�����±�Ϊi��X
	void setYat(int i,double b);//�����±�Ϊi��Y
};

#endif