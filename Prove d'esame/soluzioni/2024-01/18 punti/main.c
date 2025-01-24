#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main() {
    GRAPH graph;
    char stringa[] = {"salepepe"};

    graph = GRAPHload();

    //GRAPHprint(graph);

    checkString(graph, stringa);

    GRAPHfree(graph);
    return 0;
}
