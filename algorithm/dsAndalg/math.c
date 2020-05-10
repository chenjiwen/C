#include "common.h"

/*
 *x^n = (x^2)^(n/2)
 */
unsigned long QickPower(int exp, unsigned long base)
{
	if (exp == 0)
	{
		return 1;
	}
	else if (exp == 1)
	{
		return base;
	}

	if (exp & 0x1)
	{
		return QickPower((exp - 1) >> 1, base * base) * base;
	}
	else
	{
		return QickPower(exp >> 1, base * base);
	}
}

/*
 *m = qn + r
 *
 *gcd(m,n) = gcd(n,r)
 */
int gcd(int m, int n)
{
	int rem = 0;

	if (m < n)
	{
		swap(&m, &n);
	}

	do 
	{
		rem = m % n;
		m = n;
		n = rem;
	} while (rem);

	return m;
}


void math_test() {
	int m = 105, n = 35;

	int div = 0;

	div = gcd(m, n);
}