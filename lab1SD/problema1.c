#include <stdio.h>

int aparitii(int v[], int a, int n)
{
   if( n==0 && v[n]==a )
   	return 1;
   else if( n==0 && v[n]!=a )
   	return 0;
   else if( v[n]==a )
   	return aparitii(v, a, n-1) + 1;
   else
   	return aparitii(v, a, n-1);
}

int main()
{
	int v[100], n, a, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &v[i]);
	scanf("%d", &a);

	i=aparitii(v, a, n);
	
	printf("%d\n", i);
	return 0;
	
}