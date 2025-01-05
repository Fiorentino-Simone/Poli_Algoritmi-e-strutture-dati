#include <stdio.h>

// PROTOTIPI
int gcd(int a, int b);

int main() {
    /* DICHIARAZIONE */
    int a, b, temp, ris;

    printf("Inserisci due numeri interi, separati da spazio: ");
    scanf("%d %d", &a, &b);

    /* SWAP se non viene rispettata la condizione a > b */
    if(a < b){
        temp = a;
        a = b;
        b = temp;
    }

    ris = gcd(a, b);
    printf("Il gcd di %d e %d risulta: %d", a, b, ris);

    return 0;
}

/* FUNCTIONS */
int gcd(int a, int b){
    int temp;

    // CONDIZIONE DI TERMINAZIONE
    if(a == b || b == 0){
        return a;
    }

    // SWAP se non risulta a > b
    if(a < b){
        temp = a;
        a = b;
        b = temp;
    }

    if((a % 2 == 0) && (b % 2 == 0)){
        return 2 * gcd(a/2, b/2);
    }
    else if ((a % 2 != 0) && (b % 2 == 0)){
        return gcd(a, b/2);
    }
    else if((a % 2 != 0) && (b % 2 != 0)){
        return gcd((a-b)/2, b);
    }
    else if((a % 2 == 0) && (b % 2 != 0)){
        return gcd(a/2, b);
    }
    else return gcd(a-b, b);
}