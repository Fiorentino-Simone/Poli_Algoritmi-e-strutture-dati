#ifndef ESE01_QUOTAZIONI_H
#define ESE01_QUOTAZIONI_H

#include "datetime.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    Datetime data;
    float valore;
    int quantita;
} Quotazione; // Quasi ADT

typedef struct binarysearchtree *BST; // ADT di 1^classe

// PROTITPI

// Quotazioni
Quotazione QuotazionesetNull();
Quotazione QuotazioneScan(FILE *fp);

void QuotazioneStore(Quotazione val);

// BST
BST BSTinit();
void BSTfree(BST bst);

BST BSTreadFile(FILE *fp, BST bst);
void BSTprint(BST bst);

void BSTinsert_leafR(BST bst, Quotazione x);
Quotazione BSTnodeUpdate(Quotazione item, Quotazione k);
Quotazione BSTsearch(BST bst);

void searchBSTQuotationMINMAXFromRangeDate(BST bst);
void searchBSTQuotationMINMAXFromAllPeriod(BST bst);

void BSTbalance(BST bst);
int AltezzaAlberoMassimaWrapper(BST bst);
int AltezzaAlberoMinimaWrapper(BST bst);

#endif // ESE01_QUOTAZIONI_H
