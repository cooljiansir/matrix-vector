#ifndef __CMATRIX__H
#define __CMATRIX__H

class CMatrix
{
	friend class CLinearEquation;//������Ԫ��CLinearEquation
	friend class CVector;//������Ԫ��CVector
private:
	double * pElement;//����Ԫ�ش����ַ
	int nRow;//����
	int nColumn;//����
public:
	CMatrix(unsigned int r=0,unsigned int c=0);  //���캯��1���ɾ��������������������������󣬲�Ϊ����Ԫ�ط���洢�ռ䣬�������ʼ��Ϊ��λ����
	CMatrix(char* pFileName);//���캯��2���ɾ���洢�ļ�����������������ļ���ʽ�ɲο���¼1���������ڲ��ô˸�ʽ��
	CMatrix(const CMatrix& m);//���ƹ��캯���������о�������󴴽��µľ��������
	~CMatrix();//�����������ͷŴ洢����Ԫ�صĿռ�
	int GetRowsNum() const;//��ȡ���������
	int GetColumnsNum() const;//��ȡ���������
	double& operator ()(unsigned int r, unsigned int c);//���������()��������ȡָ����(r)��(c)��Ԫ��ֵ
	CMatrix& operator =(CMatrix& m);//���������=,���ھ���֮���໥��ֵ
	CMatrix& operator +();//����һԪ�����+,��ȡ������
	CMatrix& operator -();//����һԪ�����-��������Ԫ��ȡ�෴��
	CMatrix operator +(const CMatrix& m) const;//���ض�Ԫ�����+,�������������
	CMatrix operator -(const CMatrix& m) const;//���ض�Ԫ�����-,�������������
	CMatrix operator *(CMatrix& m) const;//���ض�Ԫ�����*,�������������
	CMatrix operator *(const double& x) const;//���ض�Ԫ�����*,�������������
	CMatrix operator *(const CVector& v) const;//���ض�Ԫ�����*�����������������
	CMatrix operator /(const double& x ) const;//���ض�Ԫ�����/,�������������
	CMatrix operator ^(const int& t) const;//���ض�Ԫ�����^,��������t����
	void operator -=(CMatrix& m);//���ض�Ԫ�����-=�����Լ�����
	void operator +=(CMatrix& m);//���ض�Ԫ�����-=�����Լ�����
	void operator *=(CMatrix& m);//���ض�Ԫ�����*=�����Գ����㣨����
	void operator *=(double x);//���ض�Ԫ�����*=�����Գ����㣨����  
	CMatrix Tranpose() const;//������ת�õĺ���
	CMatrix Invert() const;//��������ĺ���
	void Zeros();//������㻯������ǰ���������Ԫ�ع���
	void Unit();//����Ԫ��������ǰ����ת��Ϊ��λ����
	int AddRow(double* pe,int nr);//�ھ����nr��λ�ò���һ�У����ݴ�ŵ�ַΪpe�������б�
	int AddColumn(double* pe,int nc);//�ھ����nc��λ�ò���һ�У����ݴ�ŵ�ַΪpe�������б�  
	double* DeleteRow(unsigned int nr);//ɾ������nr�У����ظ���Ԫ��ֵ����ʱ�洢��ַ��
	double* DeleteColumn(unsigned int nc);//ɾ������nc�У����ظ���Ԫ��ֵ����ʱ�洢��ַ��
	int MatOut(char* pFileName); //��������pFileNameΪ�ļ��������ļ����
	
	void show();
};




#endif