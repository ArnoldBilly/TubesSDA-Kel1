#include "test.h"

int main() {
    srand(time(NULL));
    int pilih;
    char namaUNIV[50], pulau[15];
    printf("Pilih pulau:\n");
    printf("1. Jawa\n2. Sumatera\n3. Kalimantan\n4. Sulawesi\n5. Papua\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &pilih);

    pilih--;
    Address root = NULL;
    switch (pilih) {
        case 0: 
        root = initTreeJawa(); 
        strcpy(pulau, "Jawa");
        printTree(root, 0);
        break;
        case 1: 
        root = initTreeSumatera();
        strcpy(pulau, "Sumatera");
        printTree(root, 0);
        break;
        case 2: 
        root = initTreeKalimantan();
        strcpy(pulau, "Kalimantan");
        printTree(root, 0);
        break;
        case 3: 
        root = initTreeSulawesi();
        strcpy(pulau, "Sulawesi");
        printTree(root, 0);
        break;
        case 4: 
        root = initTreePapua();
        strcpy(pulau, "Papua");
        printTree(root, 0);
        break;
        default: printf("Pilihan tidak valid\n"); return 1;
    }
    getchar();
    while (1)
    {
    printf("\nDaftar Universitas yang ada di pulau %s:\n", pulau);
    showTree(root, 0);
    printf("Masukkan nama universitas tempat ujian: ");
    fgets(namaUNIV, sizeof(namaUNIV), stdin);
    namaUNIV[strcspn(namaUNIV, "\n")] = '\0';
    daftarUniv(root, namaUNIV);
    printf("\n");
    printTree(root, 0);
    }
}