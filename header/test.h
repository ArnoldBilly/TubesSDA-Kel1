#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TreeNode* Address;

typedef struct TreeNode {
    char namaUniv[100];
    int kapasitas;
    int jumlahPeserta;
    Address firstChild;
    Address nextSibling;
} TreeNode;

Address newNode(const char* nama);
void addChild(Address parent, Address child);
void printTree(Address root, int level);
void showTree(Address root, int level);
Address findUniv(Address root, const char* target);
Address daftarUniv(Address root, const char* target);
Address initTreeJawa();
Address initTreeSumatera();
Address initTreeKalimantan();
Address initTreeSulawesi();
Address initTreePapua();
#endif