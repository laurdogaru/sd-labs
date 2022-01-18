#include <stdio.h>
#include <stdlib.h>

int primul_cautarebinara(int elemCautat, int left, int right,i nt *a)  {
	int mijloc = (left + right) / 2;
	if (a[mijloc] == elemCautat) {
       while( a[--mijloc] == elemCautat )
       	;
       return mijloc+1;
	}else {
		if (a[mijloc] < elemCautat) {
			return primul_cautarebinara(elemCautat, mijloc + 1, right, a);
		} else {
			return primul_cautarebinara(elemCautat, left, mijloc - 1, a);  
		}
	}
}

int ultimul_cautarebinara(int elemCautat, int left, int right, int *a) {
	int mijloc = (left + right) / 2;
	if (a[mijloc] == elemCautat) {
       while( a[++mijloc]== elemCautat )
       	;
       return mijloc-1;
	} else {
		if (a[mijloc] < elemCautat) {
			return ultimul_cautarebinara(elemCautat, mijloc + 1, right, a);
		} else {
			return ultimul_cautarebinara(elemCautat, left, mijloc - 1, a);  
		}
	}
}

int main() {
	int i,n,*v,elemCautat;

	scanf("%d", &n);
	scanf("%d", &elemCautat);
	v = (int*)malloc(n * sizeof(int));

    for(i=0; i < n; i++) {
    	scanf("%d", &v[i]);
    }

    i = ultimul_cautarebinara(elemCautat, 0,n , v) - primul_cautarebinara(elemCautat, 0, n, v) + 1;

    printf("%d\n", i);
    
    return 0;

}