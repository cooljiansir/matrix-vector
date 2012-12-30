#ifndef __LINEAR_EQUATION__H
#define __LINEAR_EQUATION__H

#include "Matrix.h"
#include "Vector.h"

class CLinearEquation:public CMatrix
{
private:
	//������ϵ�����󣬼̳г�Ա�����ɼ�
	CVector *constVector;//������ĳ���������������Ա
	//�������з��̸������̳г�Ա���������������ɼ�
	//	��������δ֪���������̳г�Ա���������������ɼ�
public:
	CLinearEquation(CMatrix& coe, CVector& con );
	//���캯��1��ͨ��ϵ������ͳ��������������Է�����
	CLinearEquation(char* pFile);
	//���캯��2��ͨ�������ļ��������Է�����
	CLinearEquation(unsigned int ne, unsigned int nv);
	//���캯��3��ͨ�����̸�����δ֪���������Է�����
	CLinearEquation();
	//���캯��4��Ĭ�Ϲ��캯��
	~CLinearEquation();
	//��������
	int AddVariable(double *pcoe,int pc = -1);
	//Ϊ����������һ����������ϵ����������һ�У�pcoeΪ����ϵ����ַ��pcΪ����ϵ���е���ţ�0Ϊ��ǰ�棬Ĭ��׷����β�����ɹ�����δ֪������������Ϊ-1
	int AddEquation(double *pcoe, double con,int pr=-1);
	//Ϊ����������һ�����̣���ϵ����������һ�У�pcoeΪ����ϵ����ַ��conΪ���ӷ��̵ĳ����prΪ����ϵ���е���ţ�0Ϊ��ǰ�棬Ĭ��׷����β�����ɹ����ط��̸���������Ϊ-1
	int DeleteVariable(unsigned int pc);
	//ɾ���������е�pc��δ֪������ɾ����ϵ����
	int DeleteEquation(unsigned int pr);
	//ɾ���������е�pr������
	CVector Gaussian();
	//��˹��Ԫ�������Է�����
};
#endif