#include <stdio.h>
#include "nbtrees.h"

void Create_tree(Isi_Tree X, int Jml_Node){
	for (int i = 1; i <= jml_maks; i++) {
	    X[i].info = '\0';
	    X[i].FirstSon = -1;
	    X[i].NextBrother = -1;
	    X[i].Parent = -1;
	}

    //Index 1
    X[1].info='A';
    X[1].FirstSon=2;
    X[1].NextBrother=-1;
    X[1].Parent=-1;

    //Index 2
    X[2].info='B';
    X[2].FirstSon=4;
    X[2].NextBrother=3;
    X[2].Parent=1;

    //Index 3
    X[3].info='C';
    X[3].FirstSon=6;
    X[3].NextBrother=-1;
    X[3].Parent=1;

    //Index 4
    X[4].info='D';
    X[4].FirstSon=-1;
    X[4].NextBrother=5;
    X[4].Parent=2;

    //Index 5
    X[5].info='E';
    X[5].FirstSon=9;
    X[5].NextBrother=-1;
    X[5].Parent=2;

    //Index 6
    X[6].info='F';
    X[6].FirstSon=-1;
    X[6].NextBrother=7;
    X[6].Parent=3;

    //Index 7
    X[7].info='G';
    X[7].FirstSon=-1;
    X[7].NextBrother=8;
    X[7].Parent=3;

    //Index 8
    X[8].info='H';
    X[8].FirstSon=-1;
    X[8].NextBrother=-1;
    X[8].Parent=3;

    //Index 9
    X[9].info='I';
    X[9].FirstSon=-1;
    X[9].NextBrother=10;
    X[9].Parent=5;

    //Index 10
    X[10].info='J';
    X[10].FirstSon=-1;
    X[10].NextBrother=-1;
    X[10].Parent=5;
}

boolean IsEmpty (Isi_Tree P){
    return Root(P) == -1;
}

void PrintTree (Isi_Tree P){
    for (int i = 1; i <= jml_maks; i++) {
    if (P[i].info != '\0') {
        printf("--> Indeks ke-%d\n", i);
        printf("-----------------------------------\n");
        printf("info array ke %d         : %c\n", i, P[i].info);
        printf("first son array ke %d    : %d\n", i, P[i].FirstSon);
        printf("next brother array ke %d : %d\n", i, P[i].NextBrother);
        printf("parent array ke %d       : %d\n", i, P[i].Parent);
        printf("\n");
    }
}

}

int Root(Isi_Tree P) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].Parent == -1 && P[i].info != '\0') { 
            return i;
        }
    }
    return -1;
}


void InOrderRek(Isi_Tree P, int idx){
    if (idx == - 1 || idx < 1 || idx > jml_maks) return;
    int child = P[idx].FirstSon;
    if (child != -1){
        InOrderRek(P, child);
    }
    printf("%c", P[idx].info);
    child = P[idx].FirstSon;
    if (child != -1){
        child = P[child].NextBrother;
        while (child != -1){
            InOrderRek(P, child);
            child = P[child].NextBrother;
        }
    }
}

void InOrder(Isi_Tree P){
    int root = Root(P);
    InOrderRek (P, root);
    printf("\n");
}

boolean Search (Isi_Tree P, infotype X){
    for (int i = 1; i <= jml_maks; i++){
        if (P[i].info == X) return true;
    }
    return false;
}

int nbElmt(Isi_Tree P) {
    int count = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0') count++;
    }
    return count; 
}



int nbDaun(Isi_Tree P){
    int daun = 0;
    for (int i = 1; i <= jml_maks; i++){
        if (P[i].info != '\0' && P[i].FirstSon == -1)daun++;
    }
    return daun;
}

void LevelOrder(Isi_Tree P, int Maks_node) {
    int queue[jml_maks];
    int front = 0, rear = 0;

    int root = Root(P);
    if (root == -1) return;

    queue[rear++] = root;

    while (front < rear && rear <= jml_maks) {
        int curr = queue[front++];
        if (curr < 1 || curr > jml_maks) {
            printf("Error: Invalid curr index %d\n", curr);
            return;
        }
        printf("%c ", P[curr].info);
        int child = P[curr].FirstSon;
        while (child != -1 && rear < jml_maks) {
            if (child < 1 || child > jml_maks) {
                printf("Error: Invalid child index %d\n", child);
                return;
            }
            queue[rear++] = child;
            child = P[child].NextBrother;
        }
    }
    printf("\n");
}

void PreOrderRek(Isi_Tree P, int idx) {
    if (idx == -1) return;
	
    printf("%c", P[idx].info);

    int child = P[idx].FirstSon;
    while (child != -1) {
        PreOrderRek(P, child);
        child = P[child].NextBrother;
    }
}


void PreOrder(Isi_Tree P) {
    int root = Root(P);
    if (root == -1) {
        printf("Tree kosong\n");
        return;
    }
    PreOrderRek(P, root);
    printf("\n");
}


void PostOrderRek(Isi_Tree P, int idx){
    if (idx == -1) return;

    int child = P[idx].FirstSon;

    while (child != -1){
        PostOrderRek(P, child); // ke semua child dulu
        child = P[child].NextBrother;
    }

    printf("%c", P[idx].info); // ke parent setelah semua child
}

void PostOrder(Isi_Tree P){
    int root = Root(P);
    PostOrderRek(P, root);
    printf("\n");
}

int Level(Isi_Tree P, infotype X) {
    int queue[jml_maks], level[jml_maks];
    int front = 0, rear = 0;

    int root = Root(P);
    if (root == -1) return 0;

    queue[rear] = root;
    level[rear++] = 0;

    while (front < rear) {
        int curr = queue[front++];
        if (curr < 1 || curr > jml_maks) {
            printf("Error: Invalid curr index %d\n", curr);
            return 0;
        }

        if (P[curr].info == X) {
            return level[front - 1]; 
        }

        int child = P[curr].FirstSon;
        while (child != -1 && rear < jml_maks) {
            if (child < 1 || child > jml_maks) {
                printf("Error: Invalid child index %d\n", child);
                return 0;
            }
            queue[rear] = child;
            level[rear++] = level[front - 1] + 1; 
            child = P[child].NextBrother;
        }
    }
    return 0; 
}

int DepthRek(Isi_Tree P, int idx){
    if (idx == -1) return -1;

    int maxDepth = -1;
    int child = P[idx].FirstSon;

    while (child != -1){
        int childDepth = DepthRek(P, child);
        if (childDepth > maxDepth) maxDepth = childDepth;
        child = P[child].NextBrother;
    }

    return maxDepth + 1;
}

int Depth(Isi_Tree P){
    int root = Root(P);
    if (root == -1) return 0;
    return DepthRek(P, root);
}

int Max(infotype Data1, infotype Data2){
    return (Data1 > Data2) ? Data1 : Data2;
}

