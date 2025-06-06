#include "test.h"

int main() {
    srand(time(NULL));
    int pilih, ulangi = 1;
    char namaUNIV[50], pulau[15];
    Address rootjawa, rootsumatera, rootkalimantan, rootsulawesi, rootpapua;
    loadAtauInit(&rootjawa, &rootsumatera, &rootkalimantan, &rootsulawesi, &rootpapua);

    printf("Pilih pulau:\n");
    printf("1. Jawa\n2. Sumatera\n3. Kalimantan\n4. Sulawesi\n5. Papua\n");
    printf("Masukkan pilihan (1-5): ");
    scanf("%d", &pilih);
    getchar();

    pilih--;
    Address root = NULL;
    switch (pilih) {
        case 0: root = rootjawa; strcpy(pulau, "Jawa"); break;
        case 1: root = rootsumatera; strcpy(pulau, "Sumatera"); break;
        case 2: root = rootkalimantan; strcpy(pulau, "Kalimantan"); break;
        case 3: root = rootsulawesi; strcpy(pulau, "Sulawesi"); break;
        case 4: root = rootpapua; strcpy(pulau, "Papua"); break;
        default: printf("Pilihan tidak valid\n"); return 1;
    }

    while (ulangi) {
        printTree(root, 0);
        printf("\nDaftar Universitas yang ada di pulau %s:\n", pulau);
        showTree(root, 0);
        printf("Masukkan nama universitas tempat ujian (Pastikan sesuai dengan daftar diatas): ");
        fgets(namaUNIV, sizeof(namaUNIV), stdin);
        namaUNIV[strcspn(namaUNIV, "\n")] = '\0';
        Address hasil = daftarUniv(root, namaUNIV);
        if (hasil == NULL || hasil->jumlahPeserta >= hasil->kapasitas) {
            char jawaban[10];
            printf("Universitas tidak ditemukan atau sudah penuh.\n");
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
                    ulangi = 0;
                } else {
                    printf("Universitas rekomendasi tidak ditemukan atau penuh.\n");
                }
            } else {
                printf("Silakan pilih universitas lain.\n");
            }
        } else {
            hasil->jumlahPeserta++;
            printf("Kamu berhasil mendaftar di %s\n", hasil->namaUniv);
            printf("Silahkan lanjut ke tahap selanjutnya\n");
            ulangi = 0;
        }
    }

    FILE *f = fopen("datauniv.txt", "w");
    fprintf(f, "#JAWA\n"); simpanTreeKeFile(rootjawa, f, 0);
    fprintf(f, "#SUMATERA\n"); simpanTreeKeFile(rootsumatera, f, 0);
    fprintf(f, "#KALIMANTAN\n"); simpanTreeKeFile(rootkalimantan, f, 0);
    fprintf(f, "#SULAWESI\n"); simpanTreeKeFile(rootsulawesi, f, 0);
    fprintf(f, "#PAPUA\n"); simpanTreeKeFile(rootpapua, f, 0);
    fclose(f);

    printTree(root, 0);
}