#include <stdio.h>
#include <math.h>

long mx(long a, long b) {
	if(a > b)
		return a;
	else
		return b;
}

int nr_cifre(long n) {
	int count = 0;
	while(n != 0)
	{
		count++;
		n = n / 10;
	}
	return count;
}

long karatsuba(long a, long b) {
	if( a < 10 && b < 10) {
		return a * b ; 
	}
	int n = mx(nr_cifre(a) , nr_cifre(b));

    long p = (long) pow(10, n/2);
    long x = (long) ( a / p );
    long y = a % p;
    long c = (long)( b / p );
    long d = b % p;

    long xc = karatsuba(x, c);
    long yd = karatsuba(y, d);
    long z = karatsuba(x + y, c + d) - xc - yd;

    return (long) (pow(10, 2*n/2) * xc + pow(10, n/2) * z + yd);

}


int main() {
	long a,b;
	scanf("%ld", &a);
	scanf("%ld", &b);
	printf("%ld\n", karatsuba(a, b));
	return 0;
}