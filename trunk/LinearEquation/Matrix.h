#ifndef __CMATRIX__H
#define __CMATRIX__H

class CMatrix
{
	friend class CLinearEquation;//声明友元类CLinearEquation
	friend class CVector;//声明友元类CVector
private:
	double * pElement;//矩阵元素储存地址
	int nRow;//行数
	int nColumn;//列数
public:
	CMatrix(unsigned int r=0,unsigned int c=0);  //构造函数1，由矩阵的行数和列数创建矩阵类对象，并为矩阵元素分配存储空间，将矩阵初始化为单位矩阵；
	CMatrix(char* pFileName);//构造函数2，由矩阵存储文件名创建矩阵类对象，文件格式可参考附录1，但不限于采用此格式；
	CMatrix(const CMatrix& m);//复制构造函数，由已有矩阵类对象创建新的矩阵类对象；
	~CMatrix();//析构函数，释放存储矩阵元素的空间
	int GetRowsNum() const;//获取矩阵的行数
	int GetColumnsNum() const;//获取矩阵的列数
	double& operator ()(unsigned int r, unsigned int c);//重载运算符()，用于提取指定行(r)列(c)的元素值
	CMatrix& operator =(CMatrix& m);//重载运算符=,用于矩阵之间相互赋值
	CMatrix& operator +();//重载一元运算符+,即取矩阵本身
	CMatrix& operator -();//重载一元运算符-，即矩阵元素取相反数
	CMatrix operator +(const CMatrix& m) const;//重载二元运算符+,即两个矩阵求和
	CMatrix operator -(const CMatrix& m) const;//重载二元运算符-,即两个矩阵求差
	CMatrix operator *(CMatrix& m) const;//重载二元运算符*,即两个矩阵求积
	CMatrix operator *(const double& x) const;//重载二元运算符*,即矩阵与数相乘
	CMatrix operator *(const CVector& v) const;//重载二元运算符*，即矩阵与向量相乘
	CMatrix operator /(const double& x ) const;//重载二元运算符/,即矩阵与数相除
	CMatrix operator ^(const int& t) const;//重载二元运算符^,即矩阵求t次幂
	void operator -=(CMatrix& m);//重载二元运算符-=，即自减运算
	void operator +=(CMatrix& m);//重载二元运算符-=，即自加运算
	void operator *=(CMatrix& m);//重载二元运算符*=，即自乘运算（矩阵）
	void operator *=(double x);//重载二元运算符*=，即自乘运算（数）  
	CMatrix Tranpose() const;//求矩阵的转置的函数
	CMatrix Invert() const;//求矩阵的逆的函数
	void Zeros();//矩阵归零化，将当前矩阵的所有元素归零
	void Unit();//矩阵单元化，将当前矩阵转换为单位矩阵
	int AddRow(double* pe,int nr);//在矩阵的nr行位置插入一行，数据存放地址为pe，返回行标
	int AddColumn(double* pe,int nc);//在矩阵的nc列位置插入一列，数据存放地址为pe，返回列标  
	double* DeleteRow(unsigned int nr);//删除矩阵nr行，返回该行元素值（临时存储地址）
	double* DeleteColumn(unsigned int nc);//删除矩阵nc列，返回该列元素值（临时存储地址）
	int MatOut(char* pFileName); //将矩阵以pFileName为文件名进行文件输出
	
	void show();
};




#endif