#include <stdio.h>
#include <iostream>
#include "Matrix.h"
#include <list>
#include <vector>
#include <math.h>
//#define LOCAL
using namespace std;

void swap(double& i,double& j)
{//交换矩阵元素；
	double temp=i;
	i=j;j=temp;
}


void CMatrix::show()
{
	int tempId = 0;
	for(int i = 0;i<nRow;i++)
	{
		for(int j = 0;j<nColumn;j++)
		{
			//printf("%.5f ",pElement[tempId++]);
			printf("%.5f ",this->operator ()(i,j));
		}
		printf("\n");
	}
}

CMatrix::CMatrix(unsigned int r,unsigned int c)  //构造函数1，由矩阵的行数和列数创建矩阵类对象，并为矩阵元素分配存储空间，将矩阵初始化为单位矩阵；
{
	pElement = NULL;
	if(r<=0||c<=0)
	{
		cout<<"非法行数或列数！"<<endl;
	}
	else
	{
		nRow = r;
		nColumn = c;
		pElement = new double[nRow*nColumn];
		int id = 0;
		for(int i = 0;i<nRow;i++)
		{
			for(int j = 0;j<nColumn;j++)
			{
				pElement[id++] = 0;
			}
		}
	}
}
CMatrix::CMatrix(char *pFileName)
{
	nColumn = 0;
	pElement = NULL;
	FILE *pfile;
	bool stop = false;
	char doubleBuff[60];//一个浮点数缓冲
	int buffIndex = 0;//缓冲指针
	list<double> doubleList;
	list< list<double> > doubleListList;
#ifdef LOCAL
	pfile = stdin;
#else 
	pfile = fopen(pFileName,"r");
#endif

	if(pfile==NULL)
	{
		cout<<"文件打开失败！"<<endl;
		return ;
	}
	char ch = ' ';
	while(1)
	{
		//一直定位到数字开始
		while(1)
		{
			if(buffIndex)//防止重复写
			{
				double d;
				doubleBuff[buffIndex++] = '\0';
				sscanf(doubleBuff,"%lf",&d);
				doubleList.push_back(d);
				buffIndex = 0;
			}
			if(ch>='0'&&ch<='9'||ch=='.'||ch=='-'||ch=='+')break;//是数字
			if((ch==';'||ch=='\n'||ch=='；'||ch==EOF)&&doubleList.size())//注意文件结束的时候也要保存
			{
				//printf("输入一行");
				int size = doubleList.size();
				if(size>nColumn)//取最多的列为列宽
				{
					nColumn = size;
				}
				doubleListList.push_back(doubleList);
				doubleList.clear();				
			}
			if(ch==EOF)
			{
				stop = true;
				break;//文件结束
			}
			ch=fgetc(pfile);
		}
		//开始处理数字
		buffIndex = 0;//缓冲指针清零
		while(1)
		{
			if(!(ch>='0'&&ch<='9'||ch=='.'||ch=='-'||ch=='+'))break;//不是字符交给上面的循环处理，或者是文件结束
			doubleBuff[buffIndex++] = ch;
			ch = fgetc(pfile);
		}
		if(stop)break;//处理结束
	}
	fclose(pfile);
	nRow = doubleListList.size();
	if(nRow<=0||nColumn<=0)
	{
		printf("文件格式错误！\n");
		return ;
	}
	pElement = new double[nRow*nColumn];
	int tempId = 0;
	while(!doubleListList.empty())
	{
		int j = 0;
		list<double> tempList = doubleListList.front();
		doubleListList.pop_front();
		for(j = 0;!tempList.empty();j++)
		{
			double d  = tempList.front();
			tempList.pop_front();
			pElement[tempId++] = d;
			//printf("%.1lf ",d);
		}
		for(;j<nColumn;j++)
		{
			pElement[tempId++] = 0;//自动补全0
			//printf("%.1lf ",0);
		}
		//printf("\n");
	}
}

int CMatrix::GetColumnsNum() const
{
	return nColumn;
}
int CMatrix::GetRowsNum() const
{
	return nRow;
}
CMatrix::CMatrix(const CMatrix& m)
{
	nRow = m.GetRowsNum();
	nColumn = m.GetColumnsNum();
	pElement = new double[nRow*nColumn];
	int tempId = 0;
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
		{
			double b = m.pElement[tempId];
			pElement[tempId] = b;
			tempId++;
		}
}
CMatrix& CMatrix::operator =(CMatrix& m)//重载运算符=,用于矩阵之间相互赋值
{
	if(m.GetColumnsNum()!=nColumn||m.GetRowsNum()!=nRow)
	{
		printf("“=”赋值出错---行数和列数不同");
		return *this;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			pElement[i*nColumn + j] = m(i,j);
	return *this;
}
CMatrix& CMatrix::operator +()//重载一元运算符+,即取矩阵本身
{
	return *(this);
}
CMatrix& CMatrix::operator -()//重载一元运算符-，即矩阵元素取相反数
{
	CMatrix matrix(nRow,nColumn);
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j) = -matrix(i,j);
	return matrix;
}
CMatrix CMatrix::operator +(const CMatrix& m) const//重载二元运算符+,即两个矩阵求和
{
	CMatrix matrix(m);
	if(nRow!=m.GetRowsNum()||nColumn!=m.GetColumnsNum())
	{
		cout<<"执行加法出错---加数行列数不同"<<endl;
		return matrix;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j) = pElement[i*nColumn+j] + matrix(i,j);
	return matrix;
}
CMatrix CMatrix::operator -(const CMatrix& m) const//重载二元运算符-,即两个矩阵求差
{
	CMatrix matrix(m);
	if(nRow!=m.GetRowsNum()||nColumn!=m.GetColumnsNum())
	{
		cout<<"执行加法出错---加数行列数不同"<<endl;
		return matrix;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j) = pElement[i*nColumn+j] - matrix(i,j);
	return matrix;
}
CMatrix CMatrix::operator *(CMatrix& m) const//重载二元运算符*,即两个矩阵求积
{
	int RowCount = nRow,ColumnCount = m.GetColumnsNum();
	CMatrix matrix(RowCount,ColumnCount);
	int middle = nColumn;
	if(nColumn!=m.GetRowsNum())
	{
		cout<<"乘法出错---A的列数与B的行数不同"<<endl;
		return matrix;
	}	
	for(int i = 0;i<RowCount;i++)
	{
		for(int j = 0;j<ColumnCount;j++)
		{
			double sum = 0;
			for(int k = 0;k<middle;k++)
			{
				double d = m(k,j);
				sum += (pElement[i*nColumn+k]) * d;
			}
			matrix(i,j) = sum;	
		}
	}
	return matrix;
}
CMatrix CMatrix::operator *(const double& x) const//重载二元运算符*,即矩阵与数相乘
{
	CMatrix matrix(*this);
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j)*=x;
	return matrix;
}
CMatrix CMatrix::operator /(const double& x ) const//重载二元运算符/,即矩阵与数相除
{
	CMatrix matrix(*this);
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j) /= x;
	return matrix;
}
CMatrix CMatrix::operator ^(const int& t) const//重载二元运算符^,即矩阵求t次幂
{
	CMatrix matrix(nRow,nRow);
	CMatrix Amatrix(*this);//matrix的2的n次方幂的幂
	if(nRow!=nColumn)
	{
		cout<<"幂运算出错---不是方阵"<<endl;
		return matrix;
	}
	for(int i = 0;i<nRow;i++)//先置为单位方阵
		matrix(i,i)=1;
	if(t==0)return matrix;//0次幂，返回单位矩阵
	int t0 = t;
	int length = 0;//log2（t）
	while(t0)t0 = t0>>1,length++;
	for(int j = 0;j<length;j++)
	{
		if(t&(1<<j))
		{
			matrix =  (matrix * Amatrix);
		}
		Amatrix = (Amatrix * Amatrix);
	}
	return matrix;
}
void CMatrix::operator -=(CMatrix& m)//重载二元运算符-=，即自减运算
{
	if(nRow!=m.GetRowsNum()||nColumn!=m.GetColumnsNum())
	{
		cout<<"“-=”运算出错---行数或列数不同"<<endl;
		return ;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			pElement[i*nColumn + j] -= m(i,j);
}
void CMatrix::operator +=(CMatrix& m)//重载二元运算符-=，即自加运算
{
	if(nRow!=m.GetRowsNum()||nColumn!=m.GetColumnsNum())
	{
		cout<<"“+=”运算出错---行数或列数不同"<<endl;
		return ;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			pElement[i*nColumn + j] += m(i,j);
}
void CMatrix::operator *=(CMatrix& m)//重载二元运算符*=，即自乘运算（矩阵）
{
	*this = (*this)*m;
}
void CMatrix::operator *=(double x)//重载二元运算符*=，即自乘运算（数）  
{
	int tempId = 0;
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
		{
			pElement[tempId]*=x;
			tempId++;
		}
}
CMatrix CMatrix::Tranpose() const//求矩阵的转置的函数
{
	CMatrix matrix(nColumn,nRow);
	for(int i = 0;i<nColumn;i++)
		for(int j = 0;j<nRow;j++)
			matrix(i,j) = pElement[j*nColumn+i];
	return matrix;
}

CMatrix CMatrix::Invert() const//求矩阵的逆的函数
{
	CMatrix matrix(nRow,nColumn);
	if(nRow!=nColumn)
	{
		cout<<"矩阵求逆出错---行数不等于列数！"<<endl;
		return matrix;
	}

	double *pMatrix;
	if((pMatrix=new double [2*(nRow+1)*(nRow+1)])==NULL) 		
	{//立即分配一个矩阵2*(M_size+1)*(M_size+1)大小的空间;
		cout<<"矩阵求逆出错---分配内存失败"<<endl;
		exit(1);
	}
	int i;
	for(i=1;i<=nRow;i++)
	{
		for(int j=1;j<=nRow;j++)
		{//初始化矩阵元素;
			pMatrix[i*2*nRow+j] = pElement[(i-1)*nRow+j-1];
			//extended to wide matrix延拓成增广矩阵
			pMatrix[i*2*nRow+j+nRow]=0;
			pMatrix[i*2*nRow+i+nRow]=1;
		}				
	}
		
	//从第i行选取主元;	
	for(i=1;i<=nRow;i++)
	{		
		int maxLine=i;
		double maxMember=pMatrix[i*2*nRow+i];
		for(int x=i;x<=nRow;x++)
		{//选取主元，比较绝对值的大小;		
			if(fabs(pMatrix[x*2*nRow+i])>fabs(maxMember))
			{
				maxLine=x;
				maxMember=pMatrix[x*2*nRow+i];
			}
		}
		if(maxMember==0) 
		{
			cout<<"矩阵求逆出错---原矩阵没有逆矩阵\n";
			exit(-1);
		}
		for(int y=1;y<=2*nRow;y++) 
			swap(pMatrix[maxLine*2*nRow+y],pMatrix[i*2*nRow+y]);
		double temp=pMatrix[i*2*nRow+i]; //将a[i][i]取为主元并化成1
		for(x=1;x<=2*nRow;x++)				
			pMatrix[i*2*nRow+x]=pMatrix[i*2*nRow+x]/temp;
		//将对角线的元素化0	;		
		for(int k=1;k<=nRow;k++)
		{
			if(k==i) k++;
			double temp=pMatrix[k*2*nRow+i];
			for(int x=1;x<=2*nRow;x++)
				pMatrix[k*2*nRow+x]-=pMatrix[i*2*nRow+x]*temp;				
		}					
	}
	for(i=1;i<=nRow;i++)
		for(int j=1;j<=nRow;j++)
			matrix(i-1,j-1) = pMatrix[i*2*nRow+j+nRow];	
	delete []pMatrix;//释放指针
	pMatrix = NULL;
	return matrix;
}
void CMatrix::Zeros()//矩阵归零化，将当前矩阵的所有元素归零
{
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			pElement[i*nColumn+j] = 0;
}
void CMatrix::Unit()//矩阵单元化，将当前矩阵转换为单位矩阵
{
	if(nRow!=nColumn)
	{
		cout<<"矩阵单元化出错---行列数不同"<<endl;
	}
	for(int i = 0;i<nRow;i++)
		for(int j  =0;j<nRow;j++)
			if(i==j)pElement[i*nRow+j] = 1;
			else pElement[i*nRow+j] = 0;
}
int CMatrix::AddRow(double* pe, unsigned int nr)//在矩阵的nr行位置插入一行，数据存放地址为pe，返回行标
{
	//危险操作！没有给出*pe的长度，万一越界的怎么办！！
	if(!(nr<nRow))
	{
		cout<<"插入行出错---插入位置超出最大行数"<<endl;
		return -1;
	}
	double * newMatrix = new double[(nRow+1)*nColumn];
	if(newMatrix==NULL)
	{
		cout<<"插入行出错---分配内存失败！"<<endl;
		return -1;
	}
	nRow++;//行数加一
	int i,j;
	for(i = 0;i<=nr;i++)
		for(j = 0;j<nColumn;j++)
			newMatrix[i*nColumn+j] = pElement[i*nColumn+j];
	for(j = 0;j<nColumn;j++)
		newMatrix[i*nColumn+j] = pe[j];
	i++;
	for(;i<nRow;i++)
		for(j = 0;j<nColumn;j++)
			newMatrix[i*nColumn+j] = pElement[(i - 1)*nColumn+j];
	delete []pElement;
	pElement = newMatrix;
	return nr+1;
}
int CMatrix::AddColumn(double* pe, unsigned int nc)//在矩阵的nc列位置插入一列，数据存放地址为pe，返回列标  
{
	if(!(nc<nColumn))
	{
		cout<<"插入列出错---插入位置超出最大列数"<<endl;
		return -1;
	}
	double *newMatrix = new double[nRow*(nColumn+1)];
	if(newMatrix==NULL)
	{
		cout<<"插入列出错---分配内存失败！"<<endl;
		return -1;
	}
	nColumn++;//列数加一
	int i,j;
	for(j = 0;j<=nc;j++)
		for(i = 0;i<nRow;i++)
			newMatrix[i*nColumn+j] = pElement[i*(nColumn - 1)+j];
	for(i = 0;i<nRow;i++)
		newMatrix[i*nColumn+j] = pe[i];
	j++;
	for(;j<nColumn;j++)
		for(i = 0;i<nRow;i++)
			newMatrix[i*nColumn+j] = pElement[i*(nColumn - 1)+j - 1];
	delete []pElement;
	pElement = newMatrix;
	return nc+1;
	
}
double* CMatrix::DeleteRow(unsigned int nr)//删除矩阵nr行，返回该行元素值（临时存储地址）
{
	if(!(nr<nRow))
	{
		cout<<"删除行出错---删除位置大于最大行数"<<endl;
		return NULL;
	}
	double *returnRow = new double[nColumn];//!!!!!用了之后一定记得delete！！！-----实话说这样传递参数可不科学哈！
	if(returnRow==NULL)
	{
		cout<<"删除行出错---参数内存分配失败！"<<endl;
		return NULL;
	}
	double *newMatrix = new double[(nRow-1)*nColumn];
	if(newMatrix==NULL)
	{
		cout<<"删除行出错---内存分配失败！"<<endl;
		return NULL;
	}
	nRow--;//行数减一
	int i,j;
	for(i = 0;i<nr;i++)
		for(j = 0;j<nColumn;j++)
			newMatrix[i*nColumn+j] = pElement[i*nColumn+j];
	for(j = 0;j<nColumn;j++)
		returnRow[j] = pElement[i*nColumn+j];
	for(;i<nRow;i++)
		for(j = 0;j<nColumn;j++)
			newMatrix[i*nColumn+j] = pElement[(i+1)*nColumn+j];
	delete []pElement;
	pElement=  newMatrix;
	return returnRow;
}
double* CMatrix::DeleteColumn(unsigned int nc)//删除矩阵nc列，返回该列元素值（临时存储地址）
{
	if(!(nc<nColumn))
	{
		cout<<"删除列出错---删除位置大于列数"<<endl;
		return NULL;
	}
	double *returnColumn = new double[nRow];
	if(returnColumn==NULL)
	{
		cout<<"删除列出错---参数内存分配失败！"<<endl;
		return NULL;
	}
	double *newMatrix = new double[nRow*(nColumn-1)];
	if(newMatrix==NULL)
	{
		cout<<"删除列出错---内存分配失败！"<<endl;
		return NULL;
	}
	nColumn--;
	int i,j;
	for(j = 0;j<nc;j++)
		for(i = 0;i<nRow;i++)
			newMatrix[i*nColumn+j] = pElement[i*(nColumn+1)+j];
	for(i = 0;i<nRow;i++)
		returnColumn[i] = pElement[i*(nColumn+1)+j];
	for(;j<nColumn;j++)
		for(i = 0;i<nRow;i++)
			newMatrix[i*nColumn+j] = pElement[i*(nColumn+1) + j+1];
	delete []pElement;
	pElement = newMatrix;
	return returnColumn;
}
int CMatrix::MatOut(char* pFileName) //将矩阵以pFileName为文件名进行文件输出
{
	FILE *pfile = fopen(pFileName,"w");
	if(pfile==NULL)
	{
		cout<<"打开文件失败！"<<endl;
		return -1;
	}
	for(int i = 0;i<nRow;i++)
	{
		for(int j = 0;j<nColumn;j++)
		{
			fprintf(pfile,"%lf ",pElement[i*nColumn+j]);
		}
		fprintf(pfile,"\n");
	}
	fclose(pfile);
	return 0;	
}
double& CMatrix::operator ()(unsigned int r, unsigned int c)
{
	return pElement[r*nColumn+c];
}
CMatrix::~CMatrix()
{
	if(pElement != NULL)
	{
		delete []pElement;//释放空间
	}
}
