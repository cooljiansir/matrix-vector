#ifndef __VECTOR__H
#define __VECTOR__H

class CVector
{
private:
	double *pElement;
	unsigned int nDegree;
public:
	CVector(unsigned int d=0);//构造函数1，由向量的维数创建向量，向量元素值初始化为0
	CVector(unsigned int d, double* pe);//构造函数2，由向量的维数和向量元素数组创建数组
	CVector(double x, double y);//构造函数3，由两个元素生成二维向量
	CVector(double x, double y, double z);//构造函数4，由三个元素生成三维向量
	CVector(CVector& v);//复制构造函数
	~CVector();//析构函数
	CVector& operator =(CVector& v);
	CVector& operator +(void);//重载一元运算符+
	CVector operator +(CVector& v) const;//重载二元运算符+
	CVector& operator -(void);//重载一元运算符-
	CVector operator -(CVector& v) const;//重载二元运算符-
	CVector operator *(CVector& v) const;//重载二元运算符*,表示向量的叉乘（向量积）
	double operator %(CVector& v) const;//重载二元运算符%,表示向量的点乘（数量积）
	CVector operator *(const double& d) const;//重载二元运算符*，表示向量的数乘
	double& operator [](const unsigned int & i);//重载操作符[]，对指定向量元素进行操作
	int AddData(double pe, int n);//在n处添加一个数据，维度加一，-1即添加到最前面
	int DeleteData(unsigned int n);//在n处删除一个数据，维度减一
	unsigned int GetDegree() const;//获取向量维数
	void show();//打印信息
};

#endif