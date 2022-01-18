#include <stdio.h>

int fibonnaci_gen(int n, int k)
{
	int i;
	if( n <= 3 )
		return 1;
	else
    {
    	int a = 0;
    	for(i = 1; i <= k; i++)
    		a = a + fibonnaci_gen(n-i, k);
        return a ;
    }
}

int main()
{
	int n,k;
	scanf("%d%d", &n, &k);
	printf("%d\n", fibonnaci_gen(n+1, k));
	return 0;
}