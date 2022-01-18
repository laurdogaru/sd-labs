#include <stdio.h>

int produs(int v[], int n)
{
	if( n==1 )
		return v[1];
	else
		return v[n] * produs(v, n-1);
}

int main()
{
	int v[100], n, i;
	scanf("%d", &n);
	for(i = 1; i <= n; i++)
		scanf("%d", &v[i]);

	i = produs(v, n);
	
	printf("%d\n", i);
	return 0;
}