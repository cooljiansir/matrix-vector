#include <stdio.h>
#include <iostream>
#include "Matrix.h"
#include <list>
#include <vector>
#include <math.h>
//#define LOCAL
using namespace std;

void swap(double& i,double& j)
{//��������Ԫ�أ�
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

CMatrix::CMatrix(unsigned int r,unsigned int c)  //���캯��1���ɾ��������������������������󣬲�Ϊ����Ԫ�ط���洢�ռ䣬�������ʼ��Ϊ��λ����
{
	pElement = NULL;
	if(r<=0||c<=0)
	{
		cout<<"�Ƿ�������������"<<endl;
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
	char doubleBuff[60];//һ������������
	int buffIndex = 0;//����ָ��
	list<double> doubleList;
	list< list<double> > doubleListList;
#ifdef LOCAL
	pfile = stdin;
#else 
	pfile = fopen(pFileName,"r");
#endif

	if(pfile==NULL)
	{
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		return ;
	}
	char ch = ' ';
	while(1)
	{
		//һֱ��λ�����ֿ�ʼ
		while(1)
		{
			if(buffIndex)//��ֹ�ظ�д
			{
				double d;
				doubleBuff[buffIndex++] = '\0';
				sscanf(doubleBuff,"%lf",&d);
				doubleList.push_back(d);
				buffIndex = 0;
			}
			if(ch>='0'&&ch<='9'||ch=='.'||ch=='-'||ch=='+')break;//������
			if((ch==';'||ch=='\n'||ch=='��'||ch==EOF)&&doubleList.size())//ע���ļ�������ʱ��ҲҪ����
			{
				//printf("����һ��");
				int size = doubleList.size();
				if(size>nColumn)//ȡ������Ϊ�п�
				{
					nColumn = size;
				}
				doubleListList.push_back(doubleList);
				doubleList.clear();				
			}
			if(ch==EOF)
			{
				stop = true;
				break;//�ļ�����
			}
			ch=fgetc(pfile);
		}
		//��ʼ��������
		buffIndex = 0;//����ָ������
		while(1)
		{
			if(!(ch>='0'&&ch<='9'||ch=='.'||ch=='-'||ch=='+'))break;//�����ַ����������ѭ�������������ļ�����
			doubleBuff[buffIndex++] = ch;
			ch = fgetc(pfile);
		}
		if(stop)break;//�������
	}
	fclose(pfile);
	nRow = doubleListList.size();
	if(nRow<=0||nColumn<=0)
	{
		printf("�ļ���ʽ����\n");
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
			pElement[tempId++] = 0;//�Զ���ȫ0
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
CMatrix& CMatrix::operator =(CMatrix& m)//���������=,���ھ���֮���໥��ֵ
{
	if(m.GetColumnsNum()!=nColumn||m.GetRowsNum()!=nRow)
	{
		printf("��=����ֵ����---������������ͬ");
		return *this;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			pElement[i*nColumn + j] = m(i,j);
	return *this;
}
CMatrix& CMatrix::operator +()//����һԪ�����+,��ȡ������
{
	return *(this);
}
CMatrix& CMatrix::operator -()//����һԪ�����-��������Ԫ��ȡ�෴��
{
	CMatrix matrix(nRow,nColumn);
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j) = -matrix(i,j);
	return matrix;
}
CMatrix CMatrix::operator +(const CMatrix& m) const//���ض�Ԫ�����+,�������������
{
	CMatrix matrix(m);
	if(nRow!=m.GetRowsNum()||nColumn!=m.GetColumnsNum())
	{
		cout<<"ִ�мӷ�����---������������ͬ"<<endl;
		return matrix;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j) = pElement[i*nColumn+j] + matrix(i,j);
	return matrix;
}
CMatrix CMatrix::operator -(const CMatrix& m) const//���ض�Ԫ�����-,�������������
{
	CMatrix matrix(m);
	if(nRow!=m.GetRowsNum()||nColumn!=m.GetColumnsNum())
	{
		cout<<"ִ�мӷ�����---������������ͬ"<<endl;
		return matrix;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j) = pElement[i*nColumn+j] - matrix(i,j);
	return matrix;
}
CMatrix CMatrix::operator *(CMatrix& m) const//���ض�Ԫ�����*,�������������
{
	int RowCount = nRow,ColumnCount = m.GetColumnsNum();
	CMatrix matrix(RowCount,ColumnCount);
	int middle = nColumn;
	if(nColumn!=m.GetRowsNum())
	{
		cout<<"�˷�����---A��������B��������ͬ"<<endl;
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
CMatrix CMatrix::operator *(const double& x) const//���ض�Ԫ�����*,�������������
{
	CMatrix matrix(*this);
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j)*=x;
	return matrix;
}
CMatrix CMatrix::operator /(const double& x ) const//���ض�Ԫ�����/,�������������
{
	CMatrix matrix(*this);
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			matrix(i,j) /= x;
	return matrix;
}
CMatrix CMatrix::operator ^(const int& t) const//���ض�Ԫ�����^,��������t����
{
	CMatrix matrix(nRow,nRow);
	CMatrix Amatrix(*this);//matrix��2��n�η��ݵ���
	if(nRow!=nColumn)
	{
		cout<<"���������---���Ƿ���"<<endl;
		return matrix;
	}
	for(int i = 0;i<nRow;i++)//����Ϊ��λ����
		matrix(i,i)=1;
	if(t==0)return matrix;//0���ݣ����ص�λ����
	int t0 = t;
	int length = 0;//log2��t��
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
void CMatrix::operator -=(CMatrix& m)//���ض�Ԫ�����-=�����Լ�����
{
	if(nRow!=m.GetRowsNum()||nColumn!=m.GetColumnsNum())
	{
		cout<<"��-=���������---������������ͬ"<<endl;
		return ;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			pElement[i*nColumn + j] -= m(i,j);
}
void CMatrix::operator +=(CMatrix& m)//���ض�Ԫ�����-=�����Լ�����
{
	if(nRow!=m.GetRowsNum()||nColumn!=m.GetColumnsNum())
	{
		cout<<"��+=���������---������������ͬ"<<endl;
		return ;
	}
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			pElement[i*nColumn + j] += m(i,j);
}
void CMatrix::operator *=(CMatrix& m)//���ض�Ԫ�����*=�����Գ����㣨����
{
	*this = (*this)*m;
}
void CMatrix::operator *=(double x)//���ض�Ԫ�����*=�����Գ����㣨����  
{
	int tempId = 0;
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
		{
			pElement[tempId]*=x;
			tempId++;
		}
}
CMatrix CMatrix::Tranpose() const//������ת�õĺ���
{
	CMatrix matrix(nColumn,nRow);
	for(int i = 0;i<nColumn;i++)
		for(int j = 0;j<nRow;j++)
			matrix(i,j) = pElement[j*nColumn+i];
	return matrix;
}

CMatrix CMatrix::Invert() const//��������ĺ���
{
	CMatrix matrix(nRow,nColumn);
	if(nRow!=nColumn)
	{
		cout<<"�����������---����������������"<<endl;
		return matrix;
	}

	double *pMatrix;
	if((pMatrix=new double [2*(nRow+1)*(nRow+1)])==NULL) 		
	{//��������һ������2*(M_size+1)*(M_size+1)��С�Ŀռ�;
		cout<<"�����������---�����ڴ�ʧ��"<<endl;
		exit(1);
	}
	int i;
	for(i=1;i<=nRow;i++)
	{
		for(int j=1;j<=nRow;j++)
		{//��ʼ������Ԫ��;
			pMatrix[i*2*nRow+j] = pElement[(i-1)*nRow+j-1];
			//extended to wide matrix���س��������
			pMatrix[i*2*nRow+j+nRow]=0;
			pMatrix[i*2*nRow+i+nRow]=1;
		}				
	}
		
	//�ӵ�i��ѡȡ��Ԫ;	
	for(i=1;i<=nRow;i++)
	{		
		int maxLine=i;
		double maxMember=pMatrix[i*2*nRow+i];
		for(int x=i;x<=nRow;x++)
		{//ѡȡ��Ԫ���ȽϾ���ֵ�Ĵ�С;		
			if(fabs(pMatrix[x*2*nRow+i])>fabs(maxMember))
			{
				maxLine=x;
				maxMember=pMatrix[x*2*nRow+i];
			}
		}
		if(maxMember==0) 
		{
			cout<<"�����������---ԭ����û�������\n";
			exit(-1);
		}
		for(int y=1;y<=2*nRow;y++) 
			swap(pMatrix[maxLine*2*nRow+y],pMatrix[i*2*nRow+y]);
		double temp=pMatrix[i*2*nRow+i]; //��a[i][i]ȡΪ��Ԫ������1
		for(x=1;x<=2*nRow;x++)				
			pMatrix[i*2*nRow+x]=pMatrix[i*2*nRow+x]/temp;
		//���Խ��ߵ�Ԫ�ػ�0	;		
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
	delete []pMatrix;//�ͷ�ָ��
	pMatrix = NULL;
	return matrix;
}
void CMatrix::Zeros()//������㻯������ǰ���������Ԫ�ع���
{
	for(int i = 0;i<nRow;i++)
		for(int j = 0;j<nColumn;j++)
			pElement[i*nColumn+j] = 0;
}
void CMatrix::Unit()//����Ԫ��������ǰ����ת��Ϊ��λ����
{
	if(nRow!=nColumn)
	{
		cout<<"����Ԫ������---��������ͬ"<<endl;
	}
	for(int i = 0;i<nRow;i++)
		for(int j  =0;j<nRow;j++)
			if(i==j)pElement[i*nRow+j] = 1;
			else pElement[i*nRow+j] = 0;
}
int CMatrix::AddRow(double* pe, unsigned int nr)//�ھ����nr��λ�ò���һ�У����ݴ�ŵ�ַΪpe�������б�
{
	//Σ�ղ�����û�и���*pe�ĳ��ȣ���һԽ�����ô�죡��
	if(!(nr<nRow))
	{
		cout<<"�����г���---����λ�ó����������"<<endl;
		return -1;
	}
	double * newMatrix = new double[(nRow+1)*nColumn];
	if(newMatrix==NULL)
	{
		cout<<"�����г���---�����ڴ�ʧ�ܣ�"<<endl;
		return -1;
	}
	nRow++;//������һ
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
int CMatrix::AddColumn(double* pe, unsigned int nc)//�ھ����nc��λ�ò���һ�У����ݴ�ŵ�ַΪpe�������б�  
{
	if(!(nc<nColumn))
	{
		cout<<"�����г���---����λ�ó����������"<<endl;
		return -1;
	}
	double *newMatrix = new double[nRow*(nColumn+1)];
	if(newMatrix==NULL)
	{
		cout<<"�����г���---�����ڴ�ʧ�ܣ�"<<endl;
		return -1;
	}
	nColumn++;//������һ
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
double* CMatrix::DeleteRow(unsigned int nr)//ɾ������nr�У����ظ���Ԫ��ֵ����ʱ�洢��ַ��
{
	if(!(nr<nRow))
	{
		cout<<"ɾ���г���---ɾ��λ�ô����������"<<endl;
		return NULL;
	}
	double *returnRow = new double[nColumn];//!!!!!����֮��һ���ǵ�delete������-----ʵ��˵�������ݲ����ɲ���ѧ����
	if(returnRow==NULL)
	{
		cout<<"ɾ���г���---�����ڴ����ʧ�ܣ�"<<endl;
		return NULL;
	}
	double *newMatrix = new double[(nRow-1)*nColumn];
	if(newMatrix==NULL)
	{
		cout<<"ɾ���г���---�ڴ����ʧ�ܣ�"<<endl;
		return NULL;
	}
	nRow--;//������һ
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
double* CMatrix::DeleteColumn(unsigned int nc)//ɾ������nc�У����ظ���Ԫ��ֵ����ʱ�洢��ַ��
{
	if(!(nc<nColumn))
	{
		cout<<"ɾ���г���---ɾ��λ�ô�������"<<endl;
		return NULL;
	}
	double *returnColumn = new double[nRow];
	if(returnColumn==NULL)
	{
		cout<<"ɾ���г���---�����ڴ����ʧ�ܣ�"<<endl;
		return NULL;
	}
	double *newMatrix = new double[nRow*(nColumn-1)];
	if(newMatrix==NULL)
	{
		cout<<"ɾ���г���---�ڴ����ʧ�ܣ�"<<endl;
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
int CMatrix::MatOut(char* pFileName) //��������pFileNameΪ�ļ��������ļ����
{
	FILE *pfile = fopen(pFileName,"w");
	if(pfile==NULL)
	{
		cout<<"���ļ�ʧ�ܣ�"<<endl;
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
		delete []pElement;//�ͷſռ�
	}
}
