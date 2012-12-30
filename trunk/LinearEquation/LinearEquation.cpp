#include "LinearEquation.h"
#include <iostream>
#include <stdio.h>

using namespace std;
//��˹��Ԫ�������Է����飬AΪ�������
void line_equations(double A[],double X[],int n=1){
	int i,j,k,s=0;
	double temp;
	if(n==1 && A[0]!=0){
		X[0]=A[1]/A[0];
		return ;
	};
//Ϊһ��ʱֱ�������
	for(k=0;k<=n-2;k++){
		for(i=k;i<=n;i++){
			if(A[i*(n+1)+k]!=0) break;
		};                         //����������µ�һ����Ϊ0����
		if(i>=n){
			cout<<"LinearEquation �����Է��������---ԭ�����޽�!"<<endl; 
			return ;
		}; //���ڻ��������Ǿ����ʱ��������ȱ������ʱ�򣬴�ʱ�޽���������⣬ͳһΪ�޽�
		if(i!=k){
			for(j=k;j<=n;j++){
				temp=A[k*(n+1)+j];
				A[k*(n+1)+j]=A[i*(n+1)+j];
				A[i*(n+1)+j]=temp;
			};
		};                        //��һ����Ϊ0��������k�н������������Ϊ0
		for(i=k+1;i<=n-1;i++){
			for(j=k+1;j<=n;j++){
				A[i*(n+1)+j]-=((A[i*(n+1)+k]/A[k*(n+1)+k])*A[k*(n+1)+j]);
			};
			A[i*(n+1)+k]=0;
		};                 //��k��ѭ��ʱ������1�л�Ϊ0
	};
//���ˣ����������ϵ���������Ϊ����������
	X[n-1]=A[n*n-1+n]/A[n*n+n-2];   //�������ϵ������X[k],�������һ��
	for(i=n-2;i>=0;i--){
		for(j=n-2;j>=i;j--){
			A[i*(n+1)+n]-=X[j+1]*A[i*(n+1)+j+1];
		};
		X[i]=A[i*(n+1)+n]/A[i*(n+1)+i];
	};
//�������X[k]
	return;
}


CLinearEquation::CLinearEquation(CMatrix& coe, CVector& con ):CMatrix(coe)//���캯��1��ͨ��ϵ������ͳ��������������Է�����
{
	this->constVector = new CVector(con);
}
/*
*�ļ���ʽ���� 
*����Ҫ���뷽���飺
*   x1 +  2x2 +  3x3 +  4x4 = 1
* 11x1 + 12x2 + 13x3 + 14x4 = 2
* 21x1 + 22x2 + 23x3 + 24x4 = 3
* 31x1 + 32x2 + 33x3 + 34x4 = 4
*�ļ���ʽ��
* 1 , 2, 3, 4 1
* 11,12,13,14 2
* 21,22,23,24 3
* 31,32,33,34 4
*�������������ÿһ��ʹ�á�������ո����
*
*/
CLinearEquation::CLinearEquation(char* pFile):CMatrix(pFile)//���캯��2��ͨ�������ļ��������Է�����
{
	int Row = this->GetRowsNum();
	double *constV = this->DeleteColumn(this->GetColumnsNum()-1);
	this->constVector = new CVector(Row,constV);
	delete []constV;
}
CLinearEquation::CLinearEquation(unsigned int ne, unsigned int nv):CMatrix(ne,nv)//���캯��3��ͨ�����̸�����δ֪���������Է�����
{
	this->constVector = NULL;
}
CLinearEquation::CLinearEquation()//���캯��4��Ĭ�Ϲ��캯��
{
	this->constVector = NULL;
}
CLinearEquation::~CLinearEquation()//��������
{
	if(this->constVector!=NULL)
		delete this->constVector;
}
int CLinearEquation::AddVariable(double *pcoe,int pc)
//Ϊ����������һ����������ϵ����������һ�У�
//pcoeΪ����ϵ����ַ��pcΪ����ϵ���е���ţ�
//0Ϊ��ǰ�棬Ĭ��׷����β�����ɹ�����δ֪������������Ϊ-1
{
	if(pc==-1)//Ĭ�ϲ���
	{
		if(this->AddColumn(pcoe,this->GetColumnsNum()-1)==-1)//Ĭ��׷����β��
			return -1;
		else return this->GetColumnsNum();
	}
	if(!(pc<=this->GetColumnsNum()))
	{
		cout<<"LinearEquation AddVariable����---����λ�ó���������"<<endl;
		return -1;
	}
	if(this->AddColumn(pcoe,pc-1)==-1)
		return -1;
	else return this->GetColumnsNum();
}
int CLinearEquation::AddEquation(double *pcoe, double con,int pr)
//Ϊ����������һ�����̣���ϵ����������һ�У�
//pcoeΪ����ϵ����ַ��conΪ���ӷ��̵ĳ����
//prΪ����ϵ���е���ţ�0Ϊ��ǰ�棬Ĭ��׷����β�����ɹ����ط��̸���������Ϊ-1
{
	if(pr==-1)//Ĭ��׷����β��
	{
		if(this->AddRow(pcoe,this->GetRowsNum()-1)==-1)
			return -1;
		if(constVector->AddData(con,constVector->GetDegree()-1)==-1)
			return -1;
		else return this->GetRowsNum();
	}
	else if(!(pr<=this->GetRowsNum()))
	{
		cout<<"LinearEquation AddEquation ����---����λ�ó���������"<<endl;
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
int CLinearEquation::DeleteVariable(unsigned int pc)//ɾ���������е�pc��δ֪������ɾ����ϵ����
{
	if(this->DeleteColumn(pc)==NULL)
		return -1;
	else return this->GetColumnsNum();
}
int CLinearEquation::DeleteEquation(unsigned int pr)//ɾ���������е�pr������
{
	if(this->DeleteRow(pr)==NULL)
		return -1;
	return this->constVector->DeleteData(pr);
}
CVector CLinearEquation::Gaussian()
{
	if(this->GetRowsNum()!=this->GetColumnsNum())
	{
		cout<<"LinearEquation �����Է��������---������Ŀ��ͬ��δ֪��������"<<endl;
		return NULL;
	}
	int Row = this->GetRowsNum();
	int Column = this->GetColumnsNum()+1;
	double *A = new double[Row*Column];
	double *X = new double[Row];
	if(A==NULL)
	{
		cout<<"LinearEquation �����Է��������---�ڴ����ʧ��"<<endl;
		return NULL;
	}
	if(X==NULL)
	{
		cout<<"LinearEquation �����Է��������---�ڴ����ʧ��"<<endl;
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

