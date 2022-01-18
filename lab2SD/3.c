#include <stdio.h>
#include <stdlib.h>

int nr_elemente;
int *vector;

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
	aux = *a;
}

int partitie(int left, int right, int pivot) {
	int leftPtr = left -1;
	int rightPtr = right;
	while(1) {
		while( vector[++leftPtr] < pivot)
			;
		while( rightPtr > 0 && vector[--rightPtr] > pivot )
			;
		if( leftPtr >= rightPtr ) {
			break;
		} else
			swap( &vector[leftPtr], &vector[rightPtr] );
	}
	swap( &vector[leftPtr], &vector[right] );
	return leftPtr;
}

void recQuickSort(int left, int right) {
	if( right - left <= 0) {
		return;
	} else {
		int pivot = vector[right];
		int partition = partitie(left, right, pivot);
		recQuickSort(left, partition-1);
		recQuickSort(partition+1, right);
	}
}

void QuickSort() {
	recQuickSort(0, nr_elemente-1);
}

int main() {
	int pivot,i;
	printf("Dimensiunea vectorului=");
	scanf("%d", &nr_elemente);
	vector=(int *)malloc(nr_elemente *sizeof(int));
	printf("Introduceti vectorul:\n");

    for(i=0; i < nr_elemente; i++) {
    	scanf("%d", &vector[i]);
    }
    QuickSort();
    printf("Vectorul sortat este:\n");
    for(i=0;i<nr_elemente;i++) {
    	printf("%d ",bvector[i]);
    }
    printf("\n");
    return 0;

}