#include "Item.h"

typedef struct heap *Heap;

Heap HEAPinit(int maxN);
void HEAPfree(Heap h);

void HEAPfill(Heap h, Item val);
void HEAPdisplay(Heap h);

void HEAPify(Heap h, int i);
void HEAPbuild(Heap h);

void HEAPsort(Heap h);