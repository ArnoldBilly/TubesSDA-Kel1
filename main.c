#include "farell.h"
#include "hanif.h"
#include "test.h"


int main() {
    srand(time(NULL));
    User* akunHead = NULL;
    Queue antrean;
    CreateQueue(&antrean);
    dataPeserta* pesertaHead = NULL;
    Stack stack;
    CreateEmpty(&stack);

    Peserta peserta;
    User user;
    Address rootjawa, rootsumatera, rootkalimantan, rootsulawesi, rootpapua;

    int pilihan;
    char email[MAX_EMAIL], password[MAX_PASSWORD];
    char namaUNIV[50], pulau[15];
    loadAtauInit(&rootjawa, &rootsumatera, &rootkalimantan, &rootsulawesi, &rootpapua);
    bacaAkunDariFile(&akunHead);

    while (1) {
        system("cls");
        printf("Raih masa depanmu di portal SNBT\n");
        printf("Belum memiliki akun SNBT?\n1. Registrasi\n");
        printf("Sudah memiliki akun SNBT?\n2. Login\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        if (pilihan == 1) {
            registrasiAkun(&akunHead);
        } else if (pilihan == 2) {
            printf("Login Akun SNBT\n");
            printf("Masukkan email: ");
            fgets(email, MAX_EMAIL, stdin);
            email[strcspn(email, "\n")] = 0;
            printf("Masukkan Password: ");
            fgets(password, MAX_PASSWORD, stdin);
            password[strcspn(password, "\n")] = 0;

            if (loginAkun(akunHead, email, password)) {
                if (strcmp(email, "admin@admin.com") == 0) {
                    // Ini admin //
                    while (1) {
                        printf("Selamat Datang Admin\n");
                        printf("1. Lihat Antrian\n2. Konfirmasi Antrian\n3. Lihat Kapasitas Kampus\n4. Keluar\n");
                        printf("Masukkan pilihan: ");
                        scanf("%d", &pilihan);
                        getchar();
                        if (pilihan == 1) lihatAntrian(antrean, pesertaHead);
                        else if (pilihan == 2) konfirmasiAntrian(&antrean, pesertaHead);
                        else if (pilihan == 3) {
                            int piluniv;
                            printf("Pilih pulau:\n1. Jawa\n2. Sumatera\n3. Kalimantan\n4. Sulawesi\n5. Papua\n");
                            printf("Masukkan pilihan (1-5): ");
                            scanf("%d", &piluniv);
                            getchar();
                            Address root = NULL;
                            switch (piluniv) {
                                case 1: root = rootjawa; strcpy(pulau, "Jawa"); break;
                                case 2: root = rootsumatera; strcpy(pulau, "Sumatera"); break;
                                case 3: root = rootkalimantan; strcpy(pulau, "Kalimantan"); break;
                                case 4: root = rootsulawesi; strcpy(pulau, "Sulawesi"); break;
                                case 5: root = rootpapua; strcpy(pulau, "Papua"); break;
                                default: printf("Pilihan tidak valid\n"); continue;
                            }
                            printTree(root, 0);
                            getchar();
                        }break;
                    }
                } else {
                    // Ini user //
                    char nisn[MAX_NISN];
                    printf("Masukkan NISN: ");
                    fgets(nisn, MAX_NISN, stdin);
                    nisn[strcspn(nisn, "\n")] = 0;

                    // Pr nya kayanya dari sini rel //
                    dataPeserta* pesertaExist = cariPeserta(pesertaHead, nisn);
                    if (pesertaExist == NULL) {
                        isiBiodata(&pesertaHead, nisn);
                        enqueuePeserta(&antrean, nisn, pesertaHead);
                        printf("Pendaftaran berhasil, menunggu konfirmasi admin.\n");
                    } else {
                        printf("NISN sudah terdaftar!\n");
                    }

                    // Hanif mulai dari sini //
                    strcpy(user.email, email);
                    strcpy(user.password, password);
                    printf("\n=== Masukkan Data Peserta ===\n");
                    displayBioPeserta(&peserta);
                    addPeserta(&peserta, &user);
                    printf("\n=== Lanjut ke Pemilihan Program Studi ===\n");
                    displayPemilihanProdi(&stack);
                    printf("\nPemilihan prodi selesai. Berikut pilihan Anda:\n");
                    printStack(stack);

                    
                    int pilih, ulangi = 1;

                    printf("Pilih pulau:\n1. Jawa\n2. Sumatera\n3. Kalimantan\n4. Sulawesi\n5. Papua\n");
                    printf("Masukkan pilihan (1-5): ");
                    scanf("%d", &pilih);
                    getchar();

                    // Ini mulai modul gweh (billy) //
                    Address root = NULL;
                    switch (pilih) {
                        case 1: root = rootjawa; strcpy(pulau, "Jawa"); break;
                        case 2: root = rootsumatera; strcpy(pulau, "Sumatera"); break;
                        case 3: root = rootkalimantan; strcpy(pulau, "Kalimantan"); break;
                        case 4: root = rootsulawesi; strcpy(pulau, "Sulawesi"); break;
                        case 5: root = rootpapua; strcpy(pulau, "Papua"); break;
                        default: printf("Pilihan tidak valid\n"); continue;
                    }

                    while (ulangi) {
                        printTree(root, 0);
                        printf("\nDaftar Universitas di pulau %s:\n", pulau);
                        showTree(root, 0);
                        printf("Masukkan nama universitas tempat ujian: ");
                        fgets(namaUNIV, sizeof(namaUNIV), stdin);
                        namaUNIV[strcspn(namaUNIV, "\n")] = 0;

                        Address hasil = daftarUniv(root, namaUNIV);
                        if (hasil == NULL || hasil->jumlahPeserta >= hasil->kapasitas) {
                            char jawaban[10];
                            printf("Apakah ingin daftar ke rekomendasi? (Ya/Tidak): ");
                            fgets(jawaban, sizeof(jawaban), stdin);
                            jawaban[strcspn(jawaban, "\n")] = 0;
                            if (strcmp(jawaban, "ya") == 0 || strcmp(jawaban, "Ya") == 0) {
                                printf("Masukkan nama universitas dari rekomendasi: ");
                                fgets(namaUNIV, sizeof(namaUNIV), stdin);
                                namaUNIV[strcspn(namaUNIV, "\n")] = 0;
                                Address daftarUlang = findUniv(root, namaUNIV);
                                if (daftarUlang && daftarUlang->jumlahPeserta < daftarUlang->kapasitas) {
                                    daftarUlang->jumlahPeserta++;
                                    printf("Kamu berhasil mendaftar di %s\n", daftarUlang->namaUniv);
                                    ulangi = 0;
                                }
                            } else {
                                printf("Silakan pilih universitas lain.\n");
                            }
                        } else {
                            hasil->jumlahPeserta++;
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
                }
            } else {
                printf("Email atau password salah.\n");
            }
        } else {
            printf("Pilihan tidak valid!\n");
        }
    }

    // dealokasi //
    User* currentUser = akunHead;
    while (currentUser != NULL) {
        User* temp = currentUser;
        currentUser = currentUser->next;
        free(temp);
    }
    dataPeserta* currentPeserta = pesertaHead;
    while (currentPeserta != NULL) {
        dataPeserta* temp = currentPeserta;
        currentPeserta = currentPeserta->next;
        free(temp);
    }

    return 0;
}