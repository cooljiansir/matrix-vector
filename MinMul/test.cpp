#include <math.h>
#include <stdio.h>
#include "MinMul.h"
void testMinMul()
{
	double x[]={0.5,1.0,1.5,2.0,2.5,3.0};
	double y[]={1.75,2.45,3.81,4.80,7.00,8.60};
	CMinMul c(x,y,6);
	c.getCoe(2).show();
}
int main()
{
	testMinMul();
	return 0;
}