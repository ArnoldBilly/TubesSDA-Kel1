#include <stdio.h>
#include <stdlib.h>
#include "NbTree.h"

void Create_tree(Isi_Tree X, int Jml_Node) {
    // Node ke-1
    X[0].info = 'A';
    X[0].FirstSon = 1;
    X[0].NextBrother = nil;
    X[0].Parents = nil;

    // Node ke-2
    X[1].info = 'B';
    X[1].FirstSon = 3;
    X[1].NextBrother = 2;
    X[1].Parents = 0;

    // Node ke-3
    X[2].info = 'C';
    X[2].FirstSon = 5;
    X[2].NextBrother = nil;
    X[2].Parents = 0;

    // Node ke-4
    X[3].info = 'D';
    X[3].FirstSon = nil;
    X[3].NextBrother = 4;
    X[3].Parents = 1;

    // Node ke-5
    X[4].info = 'E';
    X[4].FirstSon = 8;
    X[4].NextBrother = nil;
    X[4].Parents = 1;

    // Node ke-6
    X[5].info = 'F';
    X[5].FirstSon = nil;
    X[5].NextBrother = 6;
    X[5].Parents = 2;

    // Node ke-7
    X[6].info = 'G';
    X[6].FirstSon = nil;
    X[6].NextBrother = 7;
    X[6].Parents = 2;

    // Node ke-8
    X[7].info = 'H';
    X[7].FirstSon = nil;
    X[7].NextBrother = nil;
    X[7].Parents = 2;

    // Node ke-9
    X[8].info = 'I';
    X[8].FirstSon = nil;
    X[8].NextBrother = 9;
    X[8].Parents = 4;

    // Node ke-10
    X[9].info = 'J';
    X[9].FirstSon = nil;
    X[9].NextBrother = nil;
    X[9].Parents = 4;
}


boolean IsEmpty (Isi_Tree P) {
    return P[0].info == '\0';
}

void PreOrder (Isi_Tree P) {
    static int index = 0;
    if (P[index].info == '\0') return;
    printf("%c ", P[index].info);
    int current = index;
    if (P[current].FirstSon != nil) {
        index = P[current].FirstSon;
        PreOrder(P);
    }
    if (P[current].NextBrother != nil) {
        index = P[current].NextBrother;
        PreOrder(P);
    }
    if (current == 0) index = 0;
}

void InOrder (Isi_Tree P) {
    int current = 1;
    boolean resmi = true;
    while(current != nil){
        while(P[current].FirstSon != nil && resmi){
            current = P[current].FirstSon;
        }
        if(resmi){
            printf("%c ", P[current].info);
        }
        if(P[P[current].Parents].FirstSon == current){
            printf("%c ", P[P[current].Parents].info);
        }
        if(P[current].NextBrother != nil){
            current = P[current].NextBrother;
            resmi = true;
        }else {
            current = P[current].Parents;
            resmi = false;
        }
    }
}

void PostOrder (Isi_Tree P) {
    int current = 1;
    boolean resmi = true;
    if(P[current].FirstSon != nil){
        current = P[current].FirstSon;
        while(P[current].Parents != nil){
            while(P[current].FirstSon != nil && resmi){
                current = P[current].FirstSon;   
            }
            if(P[current].FirstSon == nil && resmi){
                printf("%c ", P[current].info);
            }
            if(P[current].NextBrother != nil){
                current = P[current].NextBrother;
                resmi = true;
            }else {
                current = P[current].Parents;
                printf("%c ", P[current].info);
                resmi = false;
            }
        }
        printf("\n");
    }
}

void Level_order(Isi_Tree X, int Maks_node) {
        if (IsEmpty(X)) return;
    
        int queue[jml_maks];
        int head = 0, tail = 0;
    
        queue[tail++] = 0; // Mulai dari root (indeks 0)
    
        while (head < tail) {
            int current = queue[head++];
            printf("%c ", X[current].info);
    
            int child = X[current].FirstSon;
            while (child != nil) {
                queue[tail++] = child;
                child = X[child].NextBrother;
            }
        }
    } // Penggambarannya seperti saat mengambi A, cetak dan ambil B dan C kemudian saat mengambil B maka ambil maka first son pertamanya adalah D dan selanjutnya nb dari D adlaah E dan first sonnya adalah E dan kemudian nbnya adalah J begitu terus pada interasi yang terjadi pada J. Sebenarnya konsep seperti ini sudah di pahami secara basicnya cuman aku hanya memastikan saja.
    

    void PrintTree(Isi_Tree P) {
        int i;
        printf("Seluruh node pada binary tree: \n");
        for (i = 0; i < 10; i++) {
            if (P[i].info != '\0') {
                printf("--> indeks ke-%d\n", i);
                printf("------------------------------------\n");
                printf("Info array ke-%d            : %c\n", i, P[i].info);
                printf("First son array ke-%d       : %d\n", i, P[i].FirstSon);
                printf("Next brother array ke-%d    : %d\n", i, P[i].NextBrother);
                printf("Parent array ke-%d          : %d\n", i, P[i].Parents);
                printf("------------------------------------\n\n");
            }
        }
    }
    

    boolean Search(Isi_Tree P, infotype X) {
        for (int i = 0; i < jml_maks; i++) {
            if (P[i].info != '\0' && P[i].info == X) {
                return true;
            }
        }
        return false;
    }
    

int nbElmt (Isi_Tree P) {
    int count = 0;
    int i;
    for (i = 0; i < 10; i++) {
        if (P[i].info != '\0') count++;
    }
    return count;
}

int nbDaun (Isi_Tree P) {
        int count = 0;
        for (int index = 0; index < jml_maks; index++) {
            if (P[index].info != '\0') {
                if (P[index].FirstSon == nil) {      // Tidak punya anak
                    count++;
                }
            }
        }
    
        return count;
    
}

int Level (Isi_Tree P, infotype X) {
    int index = -1;
    for (int i = 0; i < jml_maks; i++) {
        if (P[i].info != '\0' && P[i].info == X) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return -1; // Node tidak ditemukan
    }

    int level = 0;
    while (P[index].Parents != nil) {
        index = P[index].Parents;
        level++;
    }

    return level;
}

int Depth (Isi_Tree P) {
    int maxDepth = 0;
	int i;
    for (i = 0; i < 10; i++) {
        if (P[i].info != '\0') {
            int depth = 0;
            address curr = i;
            while (P[curr].Parents != nil) {
                curr = P[curr].Parents;
                depth++;
            }
            if (depth > maxDepth) {
                maxDepth = depth;
            }
        }
    }

    return maxDepth;
}

int Max (infotype Data1, infotype Data2) {
    return (Data1 > Data2) ? Data1 : Data2;
}