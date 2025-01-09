#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RecursiveSorting.h"

int main() {
  int N, sw, scelta;
  int *a, *b;

  printf("Inserisci il numero di elementi: ");
  scanf("%d", &N);
  printf("Vuoi riempire l'array con valori casuali? (1/0) ");
  scanf("%d", &sw);

  a = (int *)malloc(N*sizeof(int));
  b = (int *)malloc(N*sizeof(int));

  if (sw) {
    printf("Valori casuali generati\n");
    srand(time(NULL));
    for (int i = 0; i < N; i++)
      a[i] = rand() % 1000;
  }
  else {
    printf("Inserisci i valori\n");
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    printf("\n");
  }

  printf("L'array originale vale\n");
  for (int i = 0; i <N; i++) {
    printf("a[%d] = %d \n", i, a[i]);
  }
  printf("\n");

  printf("\nAlgoritmi di ordinamento ricorsivi\n");
  printf("===============\n");
  printf("1. Merge sort\n");
  printf("2. Quicksort\n");
  printf("3. Esci\n");
  printf("Inserisci la tua scelta: ");
  if(scanf("%d",&scelta)<=0) {
    printf("Inserisci un valore tra 1-3!\n");
    exit(0);
  }
  else {
    switch(scelta) {
      case 1:     
        MergeSort(a, b, N);
        break;
      case 2:     
        QuickSort(a, N);
        break;
      case 3:     
        break;
      default:    
        printf("Opzione non valida\n");
    }
  }
  printf("Array ordinato in ordine crescente\n");
  for (int i = 0; i < N; i++) {
    printf("a[%d] = %d \n", i, a[i]);
  }
  printf("\n");
  return 0;
}
