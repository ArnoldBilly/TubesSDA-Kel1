#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define MAX_LINE 256

typedef struct TreeNode* Address;

typedef struct TreeNode {
    char namaUniv[100];
    int kapasitas;
    int jumlahPeserta;
    Address parent;
    Address firstChild;
    Address nextSibling;
    Address prevSibling;
} TreeNode;

Address newNode(const char* nama);
void addChild(Address parent, Address child);
void simpanTreeKeFile(Address root, FILE *f, int level);
Address bacaTreeDariFile(FILE *f);
void loadAtauInit(Address *j, Address *s, Address *k, Address *u, Address *p);
void printTree(Address root, int level);
void showTree(Address root, int level);
Address findUniv(Address root, const char* target);
Address daftarUniv(Address root, const char* target);
void rekomendasiAlternatif(Address root, const char* target);
Address initTreeJawa();
Address initTreeSumatera();
Address initTreeKalimantan();
Address initTreeSulawesi();
Address initTreePapua();

#endif