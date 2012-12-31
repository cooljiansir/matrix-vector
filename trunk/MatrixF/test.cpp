#include "Matrix.h"
#include <iostream>
#include <stdio.h>

using namespace std;


void testConstructFromFile()//测试从文件初始化
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
	printf("请输入一个浮点数：\n");
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
	printf("请输入一个整数：\n");
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
	cout<<"逆："<<endl;
	matrix.Invert().show();
}
void testUnit()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"单元化:"<<endl;
	matrix.Unit();
	matrix.show();
}
void testInsertRow()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"插入行:"<<endl;
	double row[3] = {111.0,111.1,111.2};
	matrix.AddRow(row,-1);
	matrix.show();
}
void testInsertColumn()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"插入列:"<<endl;
	double column[3] = {111.0,111.1,111.2};
	matrix.AddColumn(column,-1);
	matrix.show();
}
void testDeleteRow()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	cout<<"删除行:"<<endl;
	double * deleteRow = matrix.DeleteRow(1);
	matrix.show();
	cout<<"删除的行:"<<endl;
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
	cout<<"删除列:"<<endl;
	double *deleteColumn = matrix.DeleteColumn(1);
	matrix.show();
	cout<<"删除的列:"<<endl;
	for(int i = 0;i<matrix.GetRowsNum();i++)
		printf("%lf\n",deleteColumn[i]);
	cout<<endl;
}
void testMatOut()
{
	int nRow,nColumn;
	cout<<"请输入行数：\n";
	cin>>nRow;
	cout<<"请输入列数"<<endl;
	cin>>nColumn;
	CMatrix matrix(nRow,nColumn);
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			cin>>matrix(i,j);
	if(matrix.MatOut("testout.dat")==0)
	{
		cout<<"已经成功输出！"<<endl;
	}
	else 
	{
		cout<<"输出失败！"<<endl;
	}
	
}
void testMulV()
{
	CMatrix matrix("test6.dat");
	cout<<"A:"<<endl;
	matrix.show();
	CVector vector(1.0,1.0,1.0);
	CVector vector2 = matrix*vector;
	cout<<"向量的积"<<endl;
	vector2.show();

}
int main()
{
	testMulV();
	return ;
}