#include <stdio.h>
#include <stdlib.h>
/*
 * Sia data una matrice
M
di dimensione
r x c
contenente elementi interi.
Scrivere una funzione che generi una matrice
M'
di dimensione
r x c
derivata da
M
in cui ogni elemento
[i][j]
assume il valore dellasomma cumulata di tutti gli elementi sulla medesima diagonale e antidiagonale, considerando solo elementi il cui indice di colonna siamaggiore o uguale all'elemento preso in considerazione. Il contributo dell'elemento
[i][j]
originale è contato una singola volta.
La matrice
M'
sia allocata dentro alla funzione.
Completare opportunamente il prototipo in modo che la nuova matrice sia disponibile al chiamante.
void f(int **M, int r, int c, ...);
 */

void f(int **M,int r,int c,int ***newM);

int main()
{
    int **M;
    int r,c;
    int i,j;
    int **newM;

    printf("Inseerisci r: ");
    scanf("%d",&r);
    printf("Inserisci c: ");
    scanf("%d",&c);

    M=malloc(r*sizeof(int *));
    for(i=0;i<r;i++)
        M[i]=malloc(c*sizeof(int));

    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            scanf("%d",&M[i][j]);
    }


    f(M,r,c,&newM);



    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            printf("%d ",newM[i][j]);
        printf("\n");
    }

    for(i=0;i<r;i++){
        free(M[i]);
        free(newM[i]);
    }

    free(M);
    free(newM);

    return 0;
}


void f(int **M,int r,int c,int ***newM){
    int i,j,somma,k,t;

    (*newM)=malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        (*newM)[i]=malloc(c*sizeof(int));


    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            somma=M[i][j];

            // somma sulla diagonale
            // M[k][t] con k > i e t > j
            for(k=i+1,t=j+1;k<r && t<c;k++,t++){
                somma+=M[k][t];
            }

            //antidiagonale
            // il primo for è per la somma degli elementi sopra M[i][j]
            for(k=j,t=i;k<i && t>=0;k++,t--)
                if(t>j) // controllo degli elementi presi a destra dell'elemento M[i][j]
                    somma+=M[k][t];
            // il secondo for è per la somma degli elementi sotto M[i][j]
            for(k=j-1,t=i+1;k>=0 && t<c;k--,t++)
                if(t>j)
                    somma+=M[k][t];

            (*newM)[i][j]=somma;
        }
    }
}