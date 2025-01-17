
typedef struct list *list;

list LISTcreate();
void LISTfree(list l);

void LISTload(list L);

void LISTshow(list l);
void splice(list L1, list L2, int start, int num);