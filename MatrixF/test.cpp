#include "Matrix.h"
#include <iostream>
#include <stdio.h>

using namespace std;


void testConstructFromFile()//���Դ��ļ���ʼ��
{
	char a[] = "test.dat";
	CMatrix matrix(a);
	matrix.show();
}
void testAdd()
{
	CMatrix matrix1("test1.dat");
	CMatrix matrix2("test2.dat");
	CMatrix matrix3 = matrix1 + matrix2;
	cout<<"1:"<<endl;
	matrix1.show();
	cout<<"2:"<<endl;
	matrix2.show();
	cout<<"sum:"<<endl;
	matrix3.show();
	cout<<"sum:(user+=)"<<endl;
	matrix1 +=  matrix2;
	matrix1.show();
}
void testMul()
{
	CMatrix matrix1("test3.dat");
	CMatrix matrix2("test4.dat");
	CMatrix matrix3 = matrix1 * matrix2;
	cout<<"1:"<<endl;
	matrix1.show();
	cout<<"2:"<<endl;
	matrix2.show();
	cout<<"mul:"<<endl;
	matrix3.show();
}
void testMulD()
{
	double d;
	printf("������һ����������\n");
	scanf("%lf",&d);
	CMatrix matrix1("test3.dat");
	CMatrix matrix3 = matrix1 * d;
	cout<<"1:"<<endl;
	matrix1.show();
	cout<<"mul:"<<endl;
	matrix3.show();
}
void testPower()
{
	int t;
	printf("������һ��������\n");
	scanf("%d",&t);
	CMatrix matrix("test5.dat");
	CMatrix matrix2 = matrix^t;
	matrix2.show();	
}
void testTrans()
{
	CMatrix matrix("test1.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"AT:"<<endl;
	matrix.Tranpose().show();
}
void testInvert()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"�棺"<<endl;
	matrix.Invert().show();
}
void testUnit()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"��Ԫ��:"<<endl;
	matrix.Unit();
	matrix.show();
}
void testInsertRow()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"������:"<<endl;
	double row[3] = {111.0,111.1,111.2};
	matrix.AddRow(row,-1);
	matrix.show();
}
void testInsertColumn()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"������:"<<endl;
	double column[3] = {111.0,111.1,111.2};
	matrix.AddColumn(column,-1);
	matrix.show();
}
void testDeleteRow()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"ɾ����:"<<endl;
	double * deleteRow = matrix.DeleteRow(1);
	matrix.show();
	cout<<"ɾ������:"<<endl;
	for(int i = 0;i<matrix.GetColumnsNum();i++)
		printf("%lf ",deleteRow[i]);
	cout<<endl;
	delete []deleteRow;
}
void testDeleteColumn()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"ɾ����:"<<endl;
	double *deleteColumn = matrix.DeleteColumn(1);
	matrix.show();
	cout<<"ɾ������:"<<endl;
	for(int i = 0;i<matrix.GetRowsNum();i++)
		printf("%lf\n",deleteColumn[i]);
	cout<<endl;
}
void testMatOut()
{
	int nRow,nColumn;
	cout<<"������������\n";
	cin>>nRow;
	cout<<"����������"<<endl;
	cin>>nColumn;
	CMatrix matrix(nRow,nColumn);
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			cin>>matrix(i,j);
	if(matrix.MatOut("testout.dat")==0)
	{
		cout<<"�Ѿ��ɹ������"<<endl;
	}
	else 
	{
		cout<<"���ʧ�ܣ�"<<endl;
	}
	
}
void testMulV()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	CVector vector(1.0,1.0,1.0);
	CVector vector2 = matrix*vector;
	cout<<"�����Ļ�"<<endl;
	vector2.show();

}
int main()
{
	testMulV();
	return ;
}