#ifndef __LINEAR_EQUATION__H
#define __LINEAR_EQUATION__H

#include "Matrix.h"
#include "Vector.h"

class CLinearEquation:public CMatrix
{
private:
	//方程组系数矩阵，继承成员，不可见
	CVector *constVector;//方程组的常数向量，新增成员
	//方程组中方程个数，继承成员，矩阵行数，不可见
	//	方程组中未知数个数，继承成员，矩阵列数，不可见
public:
	CLinearEquation(CMatrix& coe, CVector& con );
	//构造函数1，通过系数矩阵和常数向量创建线性方程组
	CLinearEquation(char* pFile);
	//构造函数2，通过数据文件创建线性方程组
	CLinearEquation(unsigned int ne, unsigned int nv);
	//构造函数3，通过方程个数和未知数创建线性方程组
	CLinearEquation();
	//构造函数4，默认构造函数
	~CLinearEquation();
	//析构函数
	int AddVariable(double *pcoe,int pc = -1);
	//为方程组增加一个变量，其系数矩阵增加一列，pcoe为增加系数地址，pc为增加系数列的序号，0为最前面，默认追加在尾部，成功返回未知数个数，否则为-1
	int AddEquation(double *pcoe, double con,int pr=-1);
	//为方程组增加一个方程，其系数矩阵增加一行，pcoe为增加系数地址，con为增加方程的常数项，pr为增加系数行的序号，0为最前面，默认追加在尾部，成功返回方程个数，否则为-1
	int DeleteVariable(unsigned int pc);
	//删除方程组中第pc个未知数，并删除其系数列
	int DeleteEquation(unsigned int pr);
	//删除方程组中第pr个方程
	CVector Gaussian();
	//高斯消元法解线性方程组
};
#endif