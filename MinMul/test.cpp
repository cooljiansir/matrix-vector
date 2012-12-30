#include <math.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////////////////////////
//矩阵结构体
struct Matrix
{
 int m,n;//m为行数,n为列数
 double **pm;//指向矩阵二维数组的指针
};
//初始化矩阵mt，并置矩阵的行为m，列为n
void InitMatrix(struct Matrix *mt,int m,int n)
{
 int i;
 //指定矩阵的行和列
 mt->m=m;
 mt->n=n;
 //为矩阵分配内存
 mt->pm=new double *[m];
 for(i=0;i<m;i++)
 {
  mt->pm[i]=new double[n];
 }
}
//用0初始化矩阵mt，并置矩阵的行为m，列为n
void InitMatrix0(struct Matrix *mt,int m,int n)
{
 int i,j;
    InitMatrix(mt,m,n);
 for(i=0;i<m;i++)
  for(j=0;j<n;j++) mt->pm[i][j]=0.0;
}
//销毁矩阵mt
void DestroyMatrix(struct Matrix *mt)
{
 int i;
 //释放矩阵内存
 for(i=0;i<mt->m;i++)
 {
  delete []mt->pm[i];
 }
 delete []mt->pm;
}
//矩阵相乘mt3=mt1*mt2
//成功返回1，失败返回0
int MatrixMul(Matrix *mt1,Matrix *mt2,Matrix *mt3)
{
 int i,j,k;
 double s;
 //检查行列号是否匹配
 if(mt1->n!=mt2->m||mt1->m!=mt3->m||mt2->n!=mt3->n) return 0;
 for(i=0;i<mt1->m;i++)
  for(j=0;j<mt2->n;j++)
  {
            s=0.0;
   for(k=0;k<mt1->n;k++) s=s+mt1->pm[i][k]*mt2->pm[k][j];
   mt3->pm[i][j]=s;
  }
  return 1;
}
//矩阵转置mt2=T(mt1)
//成功返回1，失败返回0
int MatrixTran(Matrix *mt1,Matrix *mt2)
{
 int i,j;
 //检查行列号是否匹配
 if(mt1->m!=mt2->n||mt1->n!=mt2->m) return 0;
 for(i=0;i<mt1->m;i++)
  for(j=0;j<mt1->n;j++) mt2->pm[j][i]=mt1->pm[i][j];
  return 1;
}
//控制台显示矩阵mt
void ConsoleShowMatrix(Matrix *mt)
{
 int i,j;
 for(i=0;i<mt->m;i++)
 {
  printf("\n");
  for(j=0;j<mt->n;j++) printf("%2.4f ",mt->pm[i][j]);
 }
 printf("\n");
}
//////////////////////////////////////////////////////////////////////////////////////////
//Guass列主元素消元法求解方程Ax=b,a=(A,b)
int Guassl(double **a,double *x,int n)
{
 int i,j,k,numl,*h,t;
    double *l,max;
 l=new double[n];
 h=new int[n];
 for(i=0;i<n;i++) h[i]=i;//行标
 for(i=1;i<n;i++)
 {
  max=fabs(a[h[i-1]][i-1]);
  numl=i-1;
  //列元的最大值
  for(j=i;j<n;j++)
  {
   if(fabs(a[h[j]][i-1])>max)
   {
    numl=h[j];
    max=fabs(a[h[j]][i-1]);
   }
  }
  if(max<0.00000000001) return 0;
  //交换行号
  if(numl>i-1)
  {
   t=h[i];
   h[i]=h[numl];
   h[numl]=t;
  }
  for(j=i;j<n;j++) l[j]=a[h[j]][i-1]/a[h[i-1]][i-1];
  for(j=i;j<n;j++)
            for(k=i;k<n+1;k++) a[h[j]][k]=a[h[j]][k]-l[j]*a[h[i-1]][k];
 }
 
 for(i=n-1;i>=0;i--)
 {
        x[i]=a[h[i]][n];
        for(j=i+1;j<n;j++) x[i]=x[i]-a[h[i]][j]*x[j];
        x[i]=x[i]/a[h[i]][i];
 }
 
 //清除临时数组内存
 delete []l;
 delete []h;
 return 1;
}
///////////////////////////////////////////////////////////////////////////////////////////
//最小二乘法求解矩阵Ax=b
int MinMul(Matrix A,Matrix b,double *x)
{
 int i,j;
 if(b.n!=1) return 0;
 if(A.m!=b.m) return 0;
 Matrix TranA;//定义A的转置
 InitMatrix0(&TranA,A.n,A.m);
    MatrixTran(&A,&TranA);
 Matrix TranA_A;//定义A的转置与A的乘积矩阵
 InitMatrix0(&TranA_A,A.n,A.n);
    MatrixMul(&TranA,&A,&TranA_A);//A的转置与A的乘积
 Matrix TranA_b;//定义A的转置与b的乘积矩阵
 InitMatrix0(&TranA_b,A.n,1);
 MatrixMul(&TranA,&b,&TranA_b);//A的转置与b的乘积
 DestroyMatrix(&TranA);//释放A的转置的内存
 Matrix TranA_A_b;//定义增广矩阵
 InitMatrix0(&TranA_A_b,TranA_A.m,TranA_A.m+1);
 //增广矩阵赋值
 for(i=0;i<TranA_A_b.m;i++)
 {
  for(j=0;j<TranA_A_b.m;j++) TranA_A_b.pm[i][j]=TranA_A.pm[i][j];
        TranA_A_b.pm[i][TranA_A_b.m]=TranA_b.pm[i][0];
 }
 DestroyMatrix(&TranA_A);
 DestroyMatrix(&TranA_b);
 //Guass列主消元法求解
 Guassl(TranA_A_b.pm,x,TranA_A_b.m);
 DestroyMatrix(&TranA_A_b);
 return 1;
}
int MinMul(double **A,double *b,int m,int n,double *x)
{
 int r,i;
 Matrix Al,bl;
 Al.pm=new double *[m];
 Al.m=m;
 Al.n=n;
 InitMatrix(&bl,m,1);
 for(i=0;i<m;i++)
 {
  Al.pm[i]=A[i];
  bl.pm[i][0]=b[i];
 }
 r=MinMul(Al,bl,x);
 delete []Al.pm;
 DestroyMatrix(&bl);
 return r;
} 
