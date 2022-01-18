#include <stdio.h>
#include <math.h>

double radical(double n, int k, double low, double high) {
	double m = (low + high ) / 2;
	double r = pow(m, k);

	if( (r - n <= 0.00001 && r - n > 0) || ( n - r <= 0.00001 && n - r > 0) ) {
		return m;
	} else {
		if( pow(m, k) > n )
			return radical(n, k, low, m);
		else
			return radical(n, k, m, high);
	}

}

int main() {
	double n;
	int k;
	scanf("%lf", &n);
	scanf("%d", &k);
	printf("%.3lf\n", radical(n, k, 0, n));
	return 0;
}