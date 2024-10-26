#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 100

/* PROTOTIPI */
char *cercaRegexp(char *src, char *regex);

int main() {
    char src[MAXL];
    char regex[MAXL];

    printf("Inserisci la stringa sorgente: ");
    scanf("%s", src);

    printf("Inserisci l'espressione regolare: ");
    scanf("%s", regex);

    char *result = cercaRegexp(src, regex);
    if (result != NULL) {
        printf("Occorrenza trovata: %s\n", result);
    } else {
        printf("Nessuna occorrenza trovata.\n");
    }

    return 0;
}

//FUNCTIONS
char *cercaRegexp(char *src, char *regex) {

    /* ELENCO METACARATTERI:
     * '.' corrisponde a qualsiasi carattere
     * [^] corrisponde ad una sequenza di caratteri che non deve avere
     * '\a' corrisponde a un carattere minuscolo
     * '\A' corrisponde a un carattere maiuscolo
    */

    int len_src, len_regexp, found;

    len_src = strlen(src);
    len_regexp = strlen(regex);

    for (int i = 0; i < len_src; i++) {
        int j = 0;
        int k = i;
        found = 1;

        while (k < len_src && j < len_regexp && found) {
            if (regex[j] == '.') {
                j++;
                k++;
            } else if (regex[j] == '[') {
                int flag_match = 0;
                int negazione = (regex[j + 1] == '^');
                int p = negazione ? j + 2 : j + 1;

                while (regex[p] != ']' && regex[p] != '\0') {
                    if (regex[p] == src[k]) {
                        flag_match = 1;
                    }
                    p++;
                }

                // Se è presente la negazione neghiamo il match (caso in cui: [^xxx])
                if (negazione) flag_match = !flag_match;
                if (!flag_match) found = 0;

                j = (regex[p] == ']') ? p + 1 : p; // Aggiornamento indice con quello successivo a ']' senno p
                k++;
            } else if (regex[j] == '\\') { // Controllo degli escape
                if (regex[j + 1] == 'a') {
                    if (!islower(src[k])) found = 0;
                    j += 2; k++;
                } else if (regex[j + 1] == 'A') {
                    if (!isupper(src[k])) found = 0;
                    j += 2; k++;
                } else {
                    if (regex[j + 1] != src[k]) found = 0;
                    j += 2; k++;
                }
            } else {
                if (regex[j] != src[k]) found = 0;
                j++; k++;
            }
        }

        // Caso di terminazione: la sequenza è stata controllata tutta
        if (j == len_regexp) {
            return &src[i];
        }
    }

    // Caso di terminazione: non ha trovato nessuna occorrenza
    return NULL;
}