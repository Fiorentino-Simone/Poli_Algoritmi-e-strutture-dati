#include <stdio.h>

#define MAXLEN 50

/*
 * il parametro src rappresenta la stringa sorgente in cui cercare.
 * il parametro regexp rappresenta l'espressione regolare da cercare.
 * il valore di ritorno della funzione è un puntatore alla prima occorrenza di regexp in src (NULL se non trovata).
*/
char *cercaRegexp(char *src, char *regexp);

int main() {

    // DICHIARAZIONI
    char src[MAXLEN], regex[MAXLEN];
    char *occorrenza = NULL;

    // INIZIALIZZAZIONE
    printf("Inserisci la stringa str sorgente: ");
    scanf("%s", src);
    printf("\n");
    printf("Inserisci la regex: ");
    scanf("%s", regex);

    occorrenza = cercaRegexp(src, regex);

    if(occorrenza == NULL){
        printf("\n Il valore cercato nella stringa %s non è presente", src);
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    // ai fini dell'esercizio si consideri di valutare solamente stringhe composte da caratteri alfabetici.
    char *occorrenza;
    int i = 0;

    while(regexp[i] != '\0'){

    }

    return occorrenza;
}