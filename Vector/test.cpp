#include "Vector.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void testInsert()
{
	double D[3] = {1.0,1.1,1.2};
	CVector vector(3,D);
	cout<<"A:"<<endl;
	vector.show();
	vector.AddData(11.11,-1);
	cout<<"插入一维数据"<<endl;
	vector.show();
}
void testDeleteData()
{
	double D[3] = {1.0,1.1,1.2};
	CVector vector(3,D);
	cout<<"A:"<<endl;
	vector.show();
	vector.DeleteData(2);
	cout<<"删除一维数据"<<endl;
	vector.show();
}
int main()
{
	testDeleteData();

	return 0;
}