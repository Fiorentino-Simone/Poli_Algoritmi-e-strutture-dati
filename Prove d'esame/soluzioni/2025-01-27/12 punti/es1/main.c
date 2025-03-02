#include <stdio.h>

/*
 * Sono dati due vettori di interi a, b (non ordinati e contenenti eventualmente dati ripetuti), di dimensione
 * rispettivamente na e nb. Si scriva una funzione che verifichi se il primo vettore sia una sotto-sequenza del
 * secondo. La funzione deve poter essere chiamata come
 * ris = subSeq(a,na,b,nb);
 */

int subSeq(int a[], int na, int b[], int nb);

int main() {
    int ris;
    int a[] = {3,6,5,10,21};
    int b[] = { 1,3,6,7,2,-4,10,21,5};

    int na = sizeof(a) / sizeof(a[0]);
    int nb = sizeof(b) / sizeof(b[0]);


    ris = subSeq(a,na,b,nb);
    if(ris){
        printf("il vettore a risulta sottosequenza di b");
    } else{
        printf("il vettore a NON risulta sottosequenza di b");
    }

    return 0;
}

int subSeq(int a[], int na, int b[], int nb){
    int exit = 1;
    int index = 0;
    for (int i = 0; i < na; i++) {
        exit = 1;
        for (int j = index; j < nb; ++j) {
            if(a[i] == b[j]){
                exit = 0;
                index = j;
                break;
            }
        }
        if(exit){
            return 0;
        }
    }
    return 1;
}
