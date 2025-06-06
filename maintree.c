#include "tree.h"

int main() {
    srand(time(NULL));
    int pilih;
    char namaUNIV[50], pulau[15];
    
    printf("Pilih pulau:\n");
    printf("1. Jawa\n2. Sumatera\n3. Kalimantan\n4. Sulawesi\n5. Papua\n");
    printf("Masukkan pilihan (1-5): ");
    scanf("%d", &pilih);
    getchar();
    
    pilih--;
    Address root = NULL;
    switch (pilih) {
        case 0: root = initTreeJawa(); strcpy(pulau, "Jawa"); break;
        case 1: root = initTreeSumatera(); strcpy(pulau, "Sumatera"); break;
        case 2: root = initTreeKalimantan(); strcpy(pulau, "Kalimantan"); break;
        case 3: root = initTreeSulawesi(); strcpy(pulau, "Sulawesi"); break;
        case 4: root = initTreePapua(); strcpy(pulau, "Papua"); break;
        default: printf("Pilihan tidak valid\n"); return 1;
    }

    printTree(root, 0);

    while (1) {
        printf("\nDaftar Universitas yang ada di pulau %s:\n", pulau);
        showTree(root, 0);
        printf("Masukkan nama universitas tempat ujian (Pastikan sesuai dengan daftar diatas): ");
        fgets(namaUNIV, sizeof(namaUNIV), stdin);
        namaUNIV[strcspn(namaUNIV, "\n")] = '\0';

        Address hasil = daftarUniv(root, namaUNIV);

        if (hasil == NULL || hasil->jumlahPeserta > hasil->kapasitas) {
            char jawaban[4];
            printf("Apakah kamu ingin mendaftar ke salah satu rekomendasi? (Ya/Tidak): ");
            fgets(jawaban, sizeof(jawaban), stdin);
            jawaban[strcspn(jawaban, "\n")] = '\0';
            if (strcmp(jawaban, "ya") == 0 || strcmp(jawaban, "Ya") == 0) {
                printf("Masukkan nama universitas dari rekomendasi: ");
                fgets(namaUNIV, sizeof(namaUNIV), stdin);
                namaUNIV[strcspn(namaUNIV, "\n")] = '\0';
                Address daftarUlang = findUniv(root, namaUNIV);
                if (daftarUlang && daftarUlang->jumlahPeserta < daftarUlang->kapasitas) {
                    daftarUlang->jumlahPeserta++;
                    printf("Kamu berhasil mendaftar di %s\n", daftarUlang->namaUniv);
                    printf("Silahkan lanjut ke tahap selanjutnya\n");
                }
            } else {
                printf("Silakan pilih universitas lain.\n");
            }
        }

        printf("\nStatus Pendaftaran:\n");
        printTree(root, 0);
    }
}
