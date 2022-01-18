#include <stdio.h>


int fib(int n) {
	if(n <= 2)
		return 1;
	else
		return fib(n-1) + fib(n-2) + fib(n-3);
}

int main() {
	int n, i;
	scanf("%d", &n);
	printf("%d\n", fib(n));
	return 0;
}
/*Pentru a afla complexitatea, se rezolva ecuatia
caracteristica x^3 = x^2 + x + 1, a carei singura solutie
reala este aproximativ 1,839 => complexitatea este 
O(n) = 2^n*/