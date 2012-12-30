#include "LinearEquation.h"
#include <iostream>
#include <stdio.h>

using namespace std;
//高斯消元法求线性方程组，A为增广矩阵
void line_equations(double A[],double X[],int n=1){
	int i,j,k,s=0;
	double temp;
	if(n==1 && A[0]!=0){
		X[0]=A[1]/A[0];
		return ;
	};
//为一阶时直接求出解
	for(k=0;k<=n-2;k++){
		for(i=k;i<=n;i++){
			if(A[i*(n+1)+k]!=0) break;
		};                         //求出从上往下第一个不为0的行
		if(i>=n){
			cout<<"LinearEquation 解线性方程组出错---原方程无解!"<<endl; 
			return ;
		}; //若在化归上三角矩阵的时候碰到有缺阶数的时候，此时无解或有无穷多解，统一为无解
		if(i!=k){
			for(j=k;j<=n;j++){
				temp=A[k*(n+1)+j];
				A[k*(n+1)+j]=A[i*(n+1)+j];
				A[i*(n+1)+j]=temp;
			};
		};                        //第一个不为0的行来与k行交换，以免除数为0
		for(i=k+1;i<=n-1;i++){
			for(j=k+1;j<=n;j++){
				A[i*(n+1)+j]-=((A[i*(n+1)+k]/A[k*(n+1)+k])*A[k*(n+1)+j]);
			};
			A[i*(n+1)+k]=0;
		};                 //第k次循环时，将第1列化为0
	};
//至此，将方程组的系数增广矩阵化为了上三角阵
	X[n-1]=A[n*n-1+n]/A[n*n+n-2];   //从下向上迭代求出X[k],先求最后一个
	for(i=n-2;i>=0;i--){
		for(j=n-2;j>=i;j--){
			A[i*(n+1)+n]-=X[j+1]*A[i*(n+1)+j+1];
		};
		X[i]=A[i*(n+1)+n]/A[i*(n+1)+i];
	};
//迭代求出X[k]
	return;
}


CLinearEquation::CLinearEquation(CMatrix& coe, CVector& con ):CMatrix(coe)//构造函数1，通过系数矩阵和常数向量创建线性方程组
{
	this->constVector = new CVector(con);
}
/*
*文件格式如下 
*如想要输入方程组：
*   x1 +  2x2 +  3x3 +  4x4 = 1
* 11x1 + 12x2 + 13x3 + 14x4 = 2
* 21x1 + 22x2 + 23x3 + 24x4 = 3
* 31x1 + 32x2 + 33x3 + 34x4 = 4
*文件格式：
* 1 , 2, 3, 4 1
* 11,12,13,14 2
* 21,22,23,24 3
* 31,32,33,34 4
*即输入增广矩阵，每一行使用“，”或空格隔开
*
*/
CLinearEquation::CLinearEquation(char* pFile):CMatrix(pFile)//构造函数2，通过数据文件创建线性方程组
{
	int Row = this->GetRowsNum();
	double *constV = this->DeleteColumn(this->GetColumnsNum()-1);
	this->constVector = new CVector(Row,constV);
	delete []constV;
}
CLinearEquation::CLinearEquation(unsigned int ne, unsigned int nv):CMatrix(ne,nv)//构造函数3，通过方程个数和未知数创建线性方程组
{
	this->constVector = NULL;
}
CLinearEquation::CLinearEquation()//构造函数4，默认构造函数
{
	this->constVector = NULL;
}
CLinearEquation::~CLinearEquation()//析构函数
{
	if(this->constVector!=NULL)
		delete this->constVector;
}
int CLinearEquation::AddVariable(double *pcoe,int pc)
//为方程组增加一个变量，其系数矩阵增加一列，
//pcoe为增加系数地址，pc为增加系数列的序号，
//0为最前面，默认追加在尾部，成功返回未知数个数，否则为-1
{
	if(pc==-1)//默认参数
	{
		if(this->AddColumn(pcoe,this->GetColumnsNum()-1)==-1)//默认追加在尾部
			return -1;
		else return this->GetColumnsNum();
	}
	if(!(pc<=this->GetColumnsNum()))
	{
		cout<<"LinearEquation AddVariable出错---插入位置超过列数！"<<endl;
		return -1;
	}
	if(this->AddColumn(pcoe,pc-1)==-1)
		return -1;
	else return this->GetColumnsNum();
}
int CLinearEquation::AddEquation(double *pcoe, double con,int pr)
//为方程组增加一个方程，其系数矩阵增加一行，
//pcoe为增加系数地址，con为增加方程的常数项，
//pr为增加系数行的序号，0为最前面，默认追加在尾部，成功返回方程个数，否则为-1
{
	if(pr==-1)//默认追加在尾部
	{
		if(this->AddRow(pcoe,this->GetRowsNum()-1)==-1)
			return -1;
		if(constVector->AddData(con,constVector->GetDegree()-1)==-1)
			return -1;
		else return this->GetRowsNum();
	}
	else if(!(pr<=this->GetRowsNum()))
	{
		cout<<"LinearEquation AddEquation 出错---插入位置超过列数！"<<endl;
		return -1;
	}
	if(this->AddRow(pcoe,pr-1)==-1)
	{
		return -1;
	}
	if(this->constVector->AddData(con,pr-1)==-1)
	{
		return -1;
	}
	return this->GetColumnsNum();
}
int CLinearEquation::DeleteVariable(unsigned int pc)//删除方程组中第pc个未知数，并删除其系数列
{
	if(this->DeleteColumn(pc)==NULL)
		return -1;
	else return this->GetColumnsNum();
}
int CLinearEquation::DeleteEquation(unsigned int pr)//删除方程组中第pr个方程
{
	if(this->DeleteRow(pr)==NULL)
		return -1;
	return this->constVector->DeleteData(pr);
}
CVector CLinearEquation::Gaussian()
{
	if(this->GetRowsNum()!=this->GetColumnsNum())
	{
		cout<<"LinearEquation 解线性方程组出错---方程数目不同于未知数个数！"<<endl;
		return NULL;
	}
	int Row = this->GetRowsNum();
	int Column = this->GetColumnsNum()+1;
	double *A = new double[Row*Column];
	double *X = new double[Row];
	if(A==NULL)
	{
		cout<<"LinearEquation 解线性方程组出错---内存分配失败"<<endl;
		return NULL;
	}
	if(X==NULL)
	{
		cout<<"LinearEquation 解线性方程组出错---内存分配失败"<<endl;
		delete []A;
		return NULL;
	}
	int i,j;
	for(j = 0;j<Column-1;j++)
		for(i = 0;i<nRow;i++)
			A[i*Column+j] = pElement[i*(Column-1)+j];
	for(i = 0;i<nRow;i++)
		A[i*Column+j] = constVector->operator [](i);
	line_equations(A,X,Row);
	CVector vector(Row,X);
	delete []A;
	return vector;
}

