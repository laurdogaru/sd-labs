#include <stdio.h>

int putere(int a, int n)
{
	if( n==1 )
		return a;
	else if( n%2 == 1 && n > 1 )
		return putere(a, n/2) * putere(a, n/2) * a;
    else if( n%2 == 0 && n>1 )
    	return putere(a, n/2) * putere(a, n/2);
}

int main()
{
	int a,n;
	scanf("%d%d", &a, &n);
	printf("%d\n",putere(a, n));
	return 0;
}