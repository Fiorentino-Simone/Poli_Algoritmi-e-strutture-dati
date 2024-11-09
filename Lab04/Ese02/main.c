#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 50
#define COD 6

// TYPEDEF
typedef enum {
    r_leggiInput, r_leggiFile, r_ricercaCodice, r_cancellazioneCod, r_cancellazioneRange, r_stampaFile, r_fine, r_err
} comando_e;

typedef struct {
    int gg;
    int mm;
    int aaaa;
} Date;

typedef struct anagrafica {
    char codice[COD];
    char nome[MAXL];
    char cognome[MAXL];
    char data_di_nascita_out[MAXL]; // Campo data utilizzata per la stampa
    Date data_di_nascita; // Campo data di nascita usata per i confronti
    char via[MAXL];
    char citta[MAXL];
    int cap;
} Anagrafica;

typedef struct nodo *link;
typedef struct nodo {
    Anagrafica val;
    link next;
} node_t;

// PROTOTIPI
void leggi_dati(char *filename, link *head);
comando_e leggi_comando();

void stampa_lista(link lista);
void stampa_record(Anagrafica val);

void manageDate(char date[], Date *field);
int compareDate(Date d1, Date d2);

void inserisci_da_tastiera(link *head);
link ricerca_codice(link lista, char codice[]);
link elimina_codice(link head, link temp);
link ricerca_data(link lista, Date data);
link elimina_from_date(link head, link temp, link end);

link inserimento_in_testa_anagrafica(link head, Anagrafica anagrafica);
link aggiunta_nodo(link head, Anagrafica anagrafica);

int main() {
    // DICHIARAZIONI
    int continua = 1;
    comando_e comando;
    char filename[MAXL], codice[COD], data1_in[MAXL], data2_in[MAXL];
    Date data1, data2;

    link head, temp, end;

    head = temp = end = NULL;

    while(continua){
        comando = leggi_comando();
        switch (comando) {
            case r_leggiInput:
                inserisci_da_tastiera(&head);
                break;
            case r_leggiFile:
                printf("Inserisci il nome del file: ");
                scanf("%s", filename);
                leggi_dati(filename, &head);
                break;
            case r_ricercaCodice:
                printf("Inserisci il codice da ricercare: ");
                scanf("%s", codice);
                temp = ricerca_codice(head, codice);
                if(temp != NULL) {
                    stampa_record(temp->val);
                } else {
                    printf("Il codice %s non e' presente nella lista!", codice);
                }
                break;
            case r_cancellazioneCod:
                printf("Inserisci il codice da ricercare: ");
                scanf("%s", codice);
                temp = ricerca_codice(head, codice);
                if(temp != NULL) {
                    stampa_record(temp->val);
                    head = elimina_codice(head, temp);
                } else {
                    printf("Il codice %s non e' presente nella lista!", codice);
                }
                break;
            case r_cancellazioneRange:
                printf("Inserisci il range di date (gg/mm/aaaa gg/mm/aaaa): ");
                scanf("%s %s", data1_in, data2_in);
                manageDate(data1_in, &data1);
                manageDate(data2_in, &data2);
                temp = ricerca_data(head, data1);
                end = ricerca_data(head, data2);
                if(temp != NULL && end != NULL) {
                    head = elimina_from_date(head, temp, end);
                } else {
                    printf("Il range di date inserito non è corretto!");
                }
            case r_stampaFile:
                stampa_lista(head);
                break;
            case r_fine: continua = 0; break;
            default: printf("Comando errato!"); break;
        }
        printf("\n");
    }

    return 0;
}

// FUNCTIONS
comando_e leggi_comando(){
    comando_e c;
    char cmd[MAXL];
    char tabella[r_err][20] = {
            "leggi_input",
            "leggi_file",
            "ricerca_codice",
            "cancellazione_cod",
            "cancellazione_range",
            "stampa_file",
            "fine"
    };

    printf("Inserisci uno tra questi comandi (leggi_input, leggi_file, ricerca_codice, cancellazione_cod, cancellazione_range, stampa_file, fine): ");
    scanf("%s", cmd);
    strlwr(cmd);
    printf("\n");

    c = r_leggiInput;
    while (c < r_err && strcmp(tabella[c], cmd) != 0){
        c++;
    }
    return c;
}

void leggi_dati(char *filename, link *head){
    Anagrafica new_anagrafica;
    FILE *fin;

    fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(-1);
    }

    while(!feof(fin)){
        fscanf(fin, "%s%s%s%s%s%s%d",
               new_anagrafica.codice,
               new_anagrafica.nome,
               new_anagrafica.cognome,
               new_anagrafica.data_di_nascita_out,
               new_anagrafica.via,
               new_anagrafica.citta,
               &new_anagrafica.cap);

        manageDate(new_anagrafica.data_di_nascita_out, &new_anagrafica.data_di_nascita);

        (*head) = inserimento_in_testa_anagrafica(*head, new_anagrafica);
    }
    fclose(fin);
}

void inserisci_da_tastiera(link *head){
    Anagrafica new_anagrafica;

    printf("Inserisci il codice: ");
    scanf("%s", new_anagrafica.codice);

    // Controllo del codice siccome deve essere univoco
    if(ricerca_codice(*head, new_anagrafica.codice) != NULL){
        printf("Il codice inserito e' gia' presente nella lista!");
        return;
    }

    printf("Inserisci il nome: ");
    scanf("%s", new_anagrafica.nome);
    printf("Inserisci il cognome: ");
    scanf("%s", new_anagrafica.cognome);
    printf("Inserisci la data di nascita (gg/mm/aaaa): ");
    scanf("%s", new_anagrafica.data_di_nascita_out);
    printf("Inserisci la via: ");
    scanf("%s", new_anagrafica.via);
    printf("Inserisci la citta: ");
    scanf("%s", new_anagrafica.citta);
    printf("Inserisci il cap: ");
    scanf("%d", &new_anagrafica.cap);

    manageDate(new_anagrafica.data_di_nascita_out, &new_anagrafica.data_di_nascita);

    (*head) = inserimento_in_testa_anagrafica(*head, new_anagrafica);
}

link ricerca_codice(link lista, char codice[]){
    while(lista != NULL){
        if(strcmp(lista->val.codice, codice) == 0){
            return lista;
        }
        lista = lista->next;
    }
    return NULL;
}

link elimina_codice(link head, link temp){
    link x, p;
    int ok = 0;

    x = head;
    p = NULL;

    while(x != NULL && ok != 1){
        if(x == temp){
            if(p == NULL){
                head = x->next;
            } else {
                p->next = x -> next;
            }
            free(temp);
            ok = 1;
        }
        p = x;
        x = x->next;
    }

    return head;
}

link ricerca_data(link lista, Date data){
    while(lista != NULL){
        if(compareDate(lista->val.data_di_nascita, data) == 0){
            return lista;
        }
        lista = lista->next;
    }
    return NULL;
}

link elimina_from_date(link head, link temp, link end){
    // TODO: gestire l'elimina dal range delle date
}

link inserimento_in_testa_anagrafica(link head, Anagrafica anagrafica){
    link x,p;

    if((head) == NULL || compareDate(head->val.data_di_nascita, anagrafica.data_di_nascita) > 0){
      return aggiunta_nodo(head, anagrafica);
    }

    for (x = (head)->next, p = (head);
        x != NULL && compareDate(anagrafica.data_di_nascita, x->val.data_di_nascita) > 0;
        p = x, x = x->next); // trovare il puntatore alla posizione in cui aggiungere il nodo
    p -> next = aggiunta_nodo(x, anagrafica);
    return head;
}

link aggiunta_nodo(link head, Anagrafica anagrafica){
    link new_node;

    new_node = malloc(sizeof(node_t));
    new_node->val = anagrafica;
    new_node->next = (head);

    return new_node;
}

void manageDate(char date[], Date *field){
    sscanf(date, "%d/%d/%d", &field->gg, &field->mm, &field->aaaa);
}

int compareDate(Date d1, Date d2) {
    if (d1.aaaa != d2.aaaa)
        return (d1.aaaa-d2.aaaa);
    else if (d1.mm != d2.mm)
        return (d1.mm-d2.mm);
    else if (d1.gg != d2.gg)
        return (d1.gg-d2.gg);
    else return 0;
}

void stampa_lista(link lista){
    printf("\n");

    if(lista == NULL){
        printf("La lista risulta vuota!");
    } else {
        while(lista != NULL){
            printf("%s %s %s %s %s %s %d\n",
                   lista->val.codice,
                   lista->val.nome,
                   lista->val.cognome,
                   lista->val.data_di_nascita_out,
                   lista->val.via,
                   lista->val.citta,
                   lista->val.cap);
            lista = lista->next;
        }
    }
}

void stampa_record(Anagrafica val){
    printf("%s %s %s %s %s %s %d\n",
       val.codice,
       val.nome,
       val.cognome,
       val.data_di_nascita_out,
       val.via,
       val.citta,
       val.cap);
}
