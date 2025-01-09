#include <stdlib.h>
#include <stdio.h>

#include "RecursiveSorting.h"

void Merge(int *A, int *B, int l, int q, int r) {
  int i, j, k;
  i = l;
  j = q+1;

  // For per copiare A in B (dove verrà fatta la fusione fra sottovettori ordinati)
  for(k = l; k <= r; k++){
    if (i > q)
      B[k] = A[j++];
    else if (j > r)
      B[k] = A[i++];
    else if (A[i] <= A[j])
      B[k] = A[i++];
    else
      B[k] = A[j++];
  }

  // For per copiare B in A
  for ( k = l; k <= r; k++)
    A[k] = B[k];
}

void MergeSortR(int *A, int *B, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSortR(A, B, l, q);
  MergeSortR(A, B, q+1, r);
  Merge(A, B, l, q, r);
}

void MergeSort(int *A, int *B, int N) {
  int l = 0, r = N-1;
  MergeSortR(A, B, l, r);
}

void Swap(int *v, int n1, int n2) {
  int	temp;
  temp  = v[n1];
  v[n1] = v[n2];
  v[n2] = temp;
  return;
}


int partition (int *A, int l, int r) {
  int i, j;
  int x = A[r];

  printf("pivot = ");
  printf("%d", x);
  printf("\n");
  i = l-1;
  j = r;

  for ( ; ; ) {
    while(A[++i] < x);
    while(A[--j] > x);
    if (i >= j)
      break;
    Swap(A, i, j);
  }
  Swap(A, i, r);
  return i;
}

void QuickSortR(int *A, int l, int r) {
  int q;
  int i;

  if (r <= l)
    return;

  q = partition(A, l, r);

  printf("partioning result\n");
  for (i=l; i <= r; i++)
    printf("%d", A[i]);
  printf("\n");

  QuickSortR(A, l, q-1);
  QuickSortR(A, q+1, r);
  return;
}

void QuickSort(int *A, int N) {
  int l=0, r=N-1;
  QuickSortR(A, l, r);
}
