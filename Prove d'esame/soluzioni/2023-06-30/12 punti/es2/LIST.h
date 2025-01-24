#ifndef ES2_LIST_H
#define ES2_LIST_H

typedef struct list *LIST;

LIST LISTinit();
void LISTpopolate(LIST list);
void LISTprint(LIST list);
void f(LIST l);
void LISTfree(LIST list);

#endif //ES2_LIST_H
