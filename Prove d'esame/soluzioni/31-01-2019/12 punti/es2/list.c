#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct node *link;
struct node
{
  int val;
  link next;
};
struct list
{
  link head;
  int N;
};

static link NEWnode(int val, link next)
{
  link new = malloc(sizeof(*new));
  new->val = val;
  new->next = next;
  return new;
}

list LISTcreate()
{
  list a = malloc(sizeof(*a));
  a->head = NULL;
  a->N = 0;
  return a;
}

void LISTfree(list L)
{
  int i = 0;
  for (link x = L->head, t; i < L->N; i++, x = t)
  {
    t = x->next;
    free(x);
  }
  free(L);
}

link LISTinTail(int val, link h){
    link x;
    if (h == NULL){
        return NEWnode(val, NULL);
    }
    for (x = h; x->next != NULL; x = x->next);
    x->next = NEWnode(val, NULL);
    return h;
}

void LISTload(list L)
{
  int n, val;
  printf("Inserisci il numero di elementi: ");
  scanf("%d", &n);

  printf("\n");

  for (int i = 0; i < n; i++)
  {
    printf("Inserisci il valore: ");
    scanf("%d", &val);
    L->head = LISTinTail(val, L->head);
    L->N++;
  }
}

void splice(list L1, list L2, int start, int num)
{
  int i = 0;
  int *el;

  el = malloc(sizeof(int) * num);

  // estrazione dalla testa e cancellazione da L2
  for (link x = L2->head; i < num; i++, x = x->next){
      el[i] = x->val;
      L2->head = x->next;
      L2->N--;
  }

  i = 0;
  link t;

  // aggiunta nella posizione start dei valori di el
  for (link x = L1->head; x != NULL; i++, x = x->next){
      if(i == start){
          t = x->next;
          for (int j = num-1; j >= 0; j--) {
              x->next = NEWnode(el[j], x->next);
              L1->N++;
          }

          for (int j = 0; j < num; j++) {
              x = x->next;
          }
          x->next = t;
          break;
      }
  }
}

void LISTshow(list l)
{
    int i = 0;
    for (link x = l->head; i < l->N; i++, x = x->next)
    {
        printf("%d", x->val);
    }
}
