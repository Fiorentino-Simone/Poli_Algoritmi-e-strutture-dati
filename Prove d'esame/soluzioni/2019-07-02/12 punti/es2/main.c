#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node {
    char item;
    link next;
};

// Prototipi delle funzioni
void printList(link head);
link appendTail(link head, char item);
link purgeList(link head1);

int main() {
    link head1 = NULL;
    char input[] = "ab(acg)be()a(xx)f";

    for (int i = 0; input[i] != '\0'; i++) {
        head1 = appendTail(head1, input[i]);
    }

    printf("Lista originale:\n");
    printList(head1);

    link head2 = purgeList(head1);

    printf("Lista modificata:\n");
    printList(head2);

    return 0;
}

static link newNode(char item) {
    link n = malloc(sizeof(*n));
    n->item = item;
    n->next = NULL; // aggiunto in coda
    return n;
}

// Restituisce la testa della lista, dopo aver aggiunto in coda l'elemento
link appendTail(link head, char item) {
    link node = newNode(item);
    if (head == NULL) {
        return node;
    }

    link temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = node;
    return head;
}

link purgeList(link head1) {
    link head2 = NULL;
    link tail = NULL;  // Puntatore all'ultimo nodo della nuova lista
    int inside_parentheses = 0;

    while (head1) {
        if (head1->item == '(') {
            inside_parentheses = 1;

            if (head2 == NULL) {
                head2 = newNode('(');
                tail = head2; // aggiorno la coda puntando alla testa
            } else {
                tail->next = newNode('(');
                tail = tail->next;
            }
        } else if (head1->item == ')') {
            if (inside_parentheses) {
                inside_parentheses = 0;
                tail->next = newNode('*');
                tail = tail->next;
            }
            tail->next = newNode(')');
            tail = tail->next;
        } else if (!inside_parentheses) {
            if (head2 == NULL) {
                head2 = newNode(head1->item);
                tail = head2;
            } else {
                tail->next = newNode(head1->item);
                tail = tail->next;
            }
        }
        head1 = head1->next;
    }

    return head2;
}

// Funzione per stampare la lista
void printList(link head) {
    while (head) {
        printf("%c ", head->item);
        head = head->next;
    }
    printf("\n");
}
