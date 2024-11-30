#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINE
#define MAXL 50
#define COD 6

// TYPEDEF
typedef enum
{
    r_leggiInput,
    r_leggiFile,
    r_ricercaCodice,
    r_cancellazioneCod,
    r_cancellazioneRange,
    r_stampaFile,
    r_stampa,
    r_fine,
    r_err
} comando_e;

typedef struct
{
    int gg;
    int mm;
    int aaaa;
} Date;

typedef struct anagrafica
{
    char codice[COD];
    char nome[MAXL];
    char cognome[MAXL];
    char data_di_nascita_out[MAXL]; // Campo data utilizzata per la stampa
    Date data_di_nascita;           // Campo data di nascita usata per i confronti
    char via[MAXL];
    char citta[MAXL];
    int cap;
} Anagrafica;

typedef struct node_t *link;
typedef struct
{
    Anagrafica val;
    link next;
} node_t;

// PROTOTIPI
void leggi_dati(char *filename, node_t **head);
comando_e leggi_comando();

void stampa_lista(node_t *lista);
void stampa_lista_file(node_t *head);

void stampa_record(Anagrafica val);

void manage_date(char date[], Date *field);
int compare_date(Date d1, Date d2);

void inserisci_da_tastiera(node_t **head);
node_t* ricerca_codice(node_t *lista, char codice[]);
node_t* elimina_codice(node_t *head, node_t *temp);
node_t* ricerca_data(node_t *lista, Date data);
node_t* elimina_from_date(node_t *head, node_t *temp, node_t *end);

node_t* inserimento_in_anagrafica_ordinata(node_t *head, Anagrafica anagrafica);
node_t* aggiunta_nodo(node_t *nodo, Anagrafica anagrafica);

void dealloca_lista(node_t *head);

int main()
{
    // DICHIARAZIONI
    int continua;
    comando_e comando;
    char filename[MAXL], codice[COD], data1_in[MAXL], data2_in[MAXL];
    Date data1, data2;
    node_t *head, *temp, *temp2, *end;

    head = temp = end = NULL;
    continua = 1;

    while (continua)
    {
        comando = leggi_comando();
        switch (comando)
        {
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
                if (temp != NULL)
                {
                    stampa_record(temp->val);
                }
                else
                {
                    printf("Il codice %s non e' presente nella lista!", codice);
                }
                break;
            case r_cancellazioneCod:
                printf("Inserisci il codice da eliminare: ");
                scanf("%s", codice);
                temp = ricerca_codice(head, codice);
                if (temp != NULL)
                {
                    stampa_record(temp->val);
                    head = elimina_codice(head, temp);
                }
                else
                {
                    printf("Il codice %s non e' presente nella lista!", codice);
                }
                break;
            case r_cancellazioneRange:
                printf("Inserisci il range di date (gg/mm/aaaa gg/mm/aaaa): ");
                scanf("%s %s", data1_in, data2_in);
                manage_date(data1_in, &data1);
                manage_date(data2_in, &data2);
                temp = ricerca_data(head, data1);
                end = ricerca_data(head, data2);
                if (temp != NULL && end != NULL)
                {
                    temp2 = temp;
                    while (temp2 != end)
                    {
                        stampa_record(temp2->val);
                        temp2 = temp2->next;
                    }
                    stampa_record(end->val);
                    head = elimina_from_date(head, temp, end);
                }
                else
                {
                    printf("Il range di date inserito non è corretto!");
                }
                break;
            case r_stampaFile:
                stampa_lista_file(head);
                break;
            case r_stampa:
                stampa_lista(head);
                break;
            case r_fine:
                continua = 0;
                break;
            default:
                printf("Comando errato!");
                break;
        }
        printf("\n");
    }

    dealloca_lista(head);

    return 0;
}

// FUNCTIONS
comando_e leggi_comando()
{
    comando_e c;
    char cmd[MAXL];
    char tabella[r_err][25] = {
        "leggi_input",
        "leggi_file",
        "ricerca_codice",
        "cancellazione_cod",
        "cancellazione_range",
        "stampa_lista_su_file",
        "stampa_lista",
        "fine"
    };

    printf("Inserisci uno tra questi comandi \n(leggi_input, \nleggi_file, \nricerca_codice, \ncancellazione_cod, \ncancellazione_range, \nstampa_lista_su_file, \nstampa_lista, \nfine): ");
    scanf("%s", cmd);
    strlwr(cmd);
    printf("\n");

    c = r_leggiInput;
    while (c < r_err && strcmp(tabella[c], cmd) != 0)
    {
        c++;
    }
    return c;
}

void leggi_dati(char *filename, node_t **head)
{
    Anagrafica new_anagrafica;
    FILE *fin;

    fin = fopen(filename, "r");
    if (fin == NULL)
    {
        printf("Errore nella lettura del file!");
        exit(1);
    }

    while (!feof(fin))
    {
        fscanf(fin, "%s%s%s%s%s%s%d",
            new_anagrafica.codice,
            new_anagrafica.nome,
            new_anagrafica.cognome,
            new_anagrafica.data_di_nascita_out,
            new_anagrafica.via,
            new_anagrafica.citta,
            &new_anagrafica.cap);

        manage_date(new_anagrafica.data_di_nascita_out, &new_anagrafica.data_di_nascita);

        (*head) = inserimento_in_anagrafica_ordinata(*head, new_anagrafica);
    }
    fclose(fin);
}

void inserisci_da_tastiera(node_t **head)
{
    Anagrafica new_anagrafica;

    printf("Inserisci il codice: ");
    scanf("%s", new_anagrafica.codice);

    // Controllo del codice siccome deve essere univoco
    if (ricerca_codice(*head, new_anagrafica.codice) != NULL)
    {
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

    manage_date(new_anagrafica.data_di_nascita_out, &new_anagrafica.data_di_nascita);

    (*head) = inserimento_in_anagrafica_ordinata(*head, new_anagrafica);
}

node_t* ricerca_codice(node_t *lista, char codice[])
{
    while (lista != NULL)
    {
        if (strcmp(lista->val.codice, codice) == 0)
        {
            return lista;
        }
        lista = lista->next;
    }
    return NULL;
}

node_t* elimina_codice(node_t *head, node_t *temp)
{
    node_t *x, *p;
    int ok = 0;

    p = NULL;
    x = head;

    while (x != NULL && ok != 1)
    {
        if (x == temp)
        {
            if (p == NULL)
            {
                head = x->next;
            }
            else
            {
                p->next = x->next;
            }
            free(temp);
            ok = 1;
        }
        p = x;
        x = x->next;
    }

    return head;
}

node_t* ricerca_data(node_t *lista, Date data)
{
    while (lista != NULL)
    {
        if (compare_date(lista->val.data_di_nascita, data) == 0)
        {
            return lista;
        }
        lista = lista->next;
    }
    return NULL;
}

node_t* elimina_from_date(node_t *head, node_t *temp, node_t *end)
{
    node_t *x, *p;
    int ok = 0;

    p = NULL;
    x = head;

    while (x != NULL && ok != 1)
    {
        if (x == temp)
        {
            if (p == NULL)
            {
                head = end->next;
            }
            else
            {
                p->next = end->next;
            }
            free(temp);
            ok = 1;
        }
        p = x;
        x = x->next;
    }

    return head;
}

node_t* inserimento_in_anagrafica_ordinata(node_t *head, Anagrafica anagrafica)
{
    node_t *x, *p;

    if ((head) == NULL || compare_date(head->val.data_di_nascita, anagrafica.data_di_nascita) > 0)
    {
        return aggiunta_nodo(head, anagrafica);
    }

    for (x = (head)->next, p = (head);
            x != NULL && compare_date(anagrafica.data_di_nascita, x->val.data_di_nascita) > 0;
            p = x, x = x->next); // trovare il puntatore alla posizione in cui aggiungere il nodo in modo ordinato
    p->next = aggiunta_nodo(x, anagrafica);
    return head;
}

node_t* aggiunta_nodo(node_t *nodo, Anagrafica anagrafica)
{
    node_t *new_node;

    new_node = (node_t *) malloc(sizeof(node_t));
    new_node->val = anagrafica;
    new_node->next = (nodo);

    return new_node;
}

void manage_date(char date[], Date *field)
{
    sscanf(date, "%d/%d/%d", &field->gg, &field->mm, &field->aaaa);
}

int compare_date(Date d1, Date d2)
{
    if (d1.aaaa != d2.aaaa)
        return (d1.aaaa - d2.aaaa);
    else if (d1.mm != d2.mm)
        return (d1.mm - d2.mm);
    else if (d1.gg != d2.gg)
        return (d1.gg - d2.gg);
    else
        return 0;
}

void stampa_lista(node_t *lista)
{
    printf("\n");

    if (lista == NULL)
    {
        printf("La lista risulta vuota!");
    }
    else
    {
        while (lista != NULL)
        {
            stampa_record(lista->val);
            lista = lista->next;
        }
    }
}

void stampa_lista_file(node_t *head){
    char filename[MAXL];
    FILE *fout;

    printf("Inserisci il nome del file su cui stampare: ");
    scanf("%s", filename);

    fout = fopen(filename, "w");
    if (fout == NULL)
    {
        printf("Errore nell'apertura del file!");
        exit(1);
    }

    while (head != NULL)
    {
        fprintf(fout, "%s %s %s %s %s %s %d\n",
            head->val.codice,
            head->val.nome,
            head->val.cognome,
            head->val.data_di_nascita_out,
            head->val.via,
            head->val.citta,
            head->val.cap);
        head = head->next;
    }

    fclose(fout);
}

void stampa_record(Anagrafica val)
{
    printf("%s %s %s %s %s %s %d\n",
        val.codice,
        val.nome,
        val.cognome,
        val.data_di_nascita_out,
        val.via,
        val.citta,
        val.cap);
}

void dealloca_lista(node_t *head){
    node_t *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}