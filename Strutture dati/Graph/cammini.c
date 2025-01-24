#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

// CAMMINO SEMPLICE A PESO MASSIMO
void GRAPHlongestPath(Graph G, int pos)
{

    /* 
        pos = indice del nodo di partenza
        dato ad esempio da un codice simile:
        pos = STsearch(G->tab, label);
        GRAPHlongestPath(G, pos);
    */

    int i, *visited, len = -1, weight = 0;
    Edge *path, *bestPath;

    path = malloc(G->E * sizeof(Edge));
    bestPath = malloc(G->E * sizeof(Edge));
    visited = calloc(G->V, sizeof(int));

    allPathsR(G, pos, path, visited, 0, 0, bestPath, &len, &weight);

    #pragma region Stampa del cammino
    if (path != NULL && len > 0)
    {
        for (i = 0; i < len; i++)
            fprintf(stdout, "%s -- <w=%d> -- %s\n",
                    STsearchByIndex(G->tab, path[i].v), path[i].wt,
                    STsearchByIndex(G->tab, path[i].w));
        fprintf(stdout, "Total weight: %d\n", weight);
    }
    else
        printf("No path found...\n");

    free(visited);
    free(path);
    free(bestPath);
    #pragma endregion
}

static void allPathsR(Graph G, int pos, Edge *path, int *visited, int curLen, int curW, Edge *bestPath, int *bestLen, int *bestW)
{
    int i, terminal = 1;
    link t;
    visited[pos] = 1;

    for (t = G->ladj[pos]; t != G->z; t = t->next){
        if (visited[t->v] == 0)
        {
            path[curLen] = EDGEcreate(pos, t->v, t->wt);
            allPathsR(G, (t->v), path, visited, (curLen + 1), (curW + t->wt), bestPath, bestLen, bestW);
            terminal = 0;
        }
    }

    if (terminal == 1){
        if (*bestW < curW || *bestLen == -1)
        {
            *bestW = curW;
            *bestLen = curLen;
            for (i = 0; i < curLen; i++)
                bestPath[i] = path[i];
        }
    }

    visited[pos] = 0; // backtracking
}

