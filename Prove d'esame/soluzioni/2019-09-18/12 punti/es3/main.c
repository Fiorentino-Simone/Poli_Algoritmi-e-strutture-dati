#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int v;
    int w;
    int wt;
} Edge;

// Funzione di supporto per verificare se un dato sottoinsieme di archi rappresenta un albero ricoprente
bool isSpanningTree(Edge *subset, int subsetSize, int nV) {
    // Array per rappresentare la connessione tra i vertici
    int *visited = calloc(nV, sizeof(int));
    int *stack = malloc(nV * sizeof(int));
    int stackSize = 0, visitedCount = 0;

    // Partiamo da un vertice arbitrario (ad esempio il primo vertice del primo arco)
    visited[subset[0].v] = 1;
    stack[stackSize++] = subset[0].v;
    visitedCount++;

    // DFS per verificare la connessione del grafo
    while (stackSize > 0) {
        int current = stack[--stackSize];

        for (int i = 0; i < subsetSize; i++) {
            int neighbor = -1;
            if (subset[i].v == current && !visited[subset[i].w]) {
                neighbor = subset[i].w;
            } else if (subset[i].w == current && !visited[subset[i].v]) {
                neighbor = subset[i].v;
            }

            if (neighbor != -1) {
                visited[neighbor] = 1;
                stack[stackSize++] = neighbor;
                visitedCount++;
            }
        }
    }

    // Verifica che tutti i vertici siano visitati e che ci siano nV-1 archi
    free(stack);
    bool isTree = (visitedCount == nV && subsetSize == nV - 1);
    free(visited);

    return isTree;
}

// Funzione per generare tutte le combinazioni di archi di dimensione k
void combinations(Edge *edges, int nE, Edge *subset, int k, int start, int pos, int *minWeight, int nV) {
    if (pos >= k) {
        // Verifica se il sottoinsieme rappresenta un albero ricoprente
        if (isSpanningTree(subset, k, nV)) {
            // Calcola il peso totale del sottoinsieme
            int weight = 0;
            for (int i = 0; i < k; i++) {
                weight += subset[i].wt;
            }
            // Aggiorna il peso minimo
            if (weight < *minWeight) {
                *minWeight = weight;
            }
        }
        return;
    }

    for (int i = start; i < nE; i++) {
        subset[pos] = edges[i];
        combinations(edges, nE, subset, k, i + 1, pos + 1, minWeight, nV);
    }
}

// Funzione principale per calcolare il peso dell'albero ricoprente minimo
int minimumSpanningTreeWeight(Edge *edges, int nE, int nV) {
    Edge *subset = malloc((nV - 1) * sizeof(Edge));
    int minWeight = __INT_MAX__;

    // Genera tutte le combinazioni di nV-1 archi
    combinations(edges, nE, subset, nV - 1, 0, 0, &minWeight, nV);

    free(subset);
    return minWeight;
}

int main() {
    // Esempio di utilizzo
    int nV = 4; // Numero di vertici
    int nE = 5; // Numero di archi

    Edge edges[] = {
            {0, 1, 1},
            {0, 2, 2},
            {1, 2, 2},
            {1, 3, 1},
            {2, 3, 3}
    };

    int result = minimumSpanningTreeWeight(edges, nE, nV);
    printf("Peso minimo dell'albero ricoprente: %d\n", result);

    return 0;
}
