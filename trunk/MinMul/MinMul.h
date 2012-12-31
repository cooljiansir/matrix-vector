#ifndef __MIN_MUL__H
#define __MIN_MUL__H

#include "LinearEquation.h"

class CMinMul
{
private:
	double *X;//X序列
	double *Y;//Y序列
	unsigned int nPoint;//点个数
public:
	CMinMul(double *x,double *y,unsigned int n);//构造函数1
	CMinMul(unsigned int n);//构造函数2，n为点的个数，以0填充
	CMinMul(char *pFile);//构造函数3，通过文件读取构造
	CMinMul(const CMinMul& b);//构造函数4,拷贝构造函数
	~CMinMul();//析构函数
	CMinMul& operator = (const CMinMul &b);//重载幅值运算符
	CVector getCoe(int maxPower);
	//最小二乘法求解结果(a0,a1,a2,a3,a4...an),maxPower为最高次数n
	unsigned int getPointNums()const;//点的个数
	double getXat(int i) const;//获取下标为i的X
	double getYat(int i) const;//获取下标为i的Y
	void setXat(int i,double b);//设置下标为i的X
	void setYat(int i,double b);//设置下标为i的Y
};

#endif