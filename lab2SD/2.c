#include <stdio.h>
#include <stdlib.h>

int *v;

int fib_mem(int n) {
	if(n <= 2) {
		return 1;
	} else if( v[n-1] != 0 && v[n-2] != 0 && v[n-3] != 0 ) {
		return v[n-1] + v[n-2] + v[n-3];
	} else {
		v[n] = fib_mem(n-1) + fib_mem(n-2) + fib_mem(n-3);
		return v[n];
	}
}


int main() {
	int n;
	scanf("%d", &n);
	v=(int *) calloc(n, sizeof(int));
	printf("%d\n", fib_mem(n));
    return 0;
}