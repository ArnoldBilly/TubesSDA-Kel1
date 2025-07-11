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
    Address hasil;

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
            Sleep(3000);
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
                        system("cls");
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
                    system("cls");
                    pilihan = 0;
                    printf("Selamat datang di portal SNBT\n");
                    printf("1. Daftar UTBK\n");
                    printf("2. Lihat Kartu Peserta UTBK\n");
                    printf("Masukkan pilihan: ");
                    scanf("%d", &pilihan);
                    getchar();
                    if (pilihan == 1)
                    {
                        strcpy(peserta.nisn, email);
                        strcpy(peserta.namaLengkap, "");
                        displayBioPeserta(&peserta);
                        dataPeserta* pesertaExist = cariPeserta(pesertaHead, peserta.nisn);
                        if (pesertaExist == NULL) {
                            isiBiodata(&pesertaHead, peserta.nisn, &peserta);
                            enqueuePeserta(&antrean, peserta.nisn, pesertaHead,&peserta);
                            printf("Pendaftaran berhasil, menunggu konfirmasi admin.\n");
                        } else {
                            printf("NISN sudah terdaftar!\n");
                        }
                        strcpy(user.email, email);
                        strcpy(user.password, password);
                        printf("\n=== Lanjut ke Pemilihan Program Studi ===\n");
                        displayPemilihanProdi(&stack);
                        printf("\nPemilihan prodi selesai. Berikut pilihan Anda:\n");
                        printStack(stack);

                        
                        int pilih, ulangi = 1;

                        system("cls");
                        printf("===================================================\n");
                        printf("                  Pilih Pusat UTBK                  \n");
                        printf("===================================================\n\n");
                        printf("Pilih pulau lokasi pusat UTBK:\n1. Jawa\n2. Sumatera\n3. Kalimantan\n4. Sulawesi\n5. Papua\n");
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

                            hasil = daftarUniv(root, namaUNIV);
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
                        
                        printf("\nPendaftaran selesai. Apa yang ingin Anda lakukan?\n");
                        printf("1. Logout\n2. Keluar dari program\n");
                        printf("Masukkan pilihan: ");
                        scanf("%d", &pilih);
                        getchar();
                        if (pilih == 1) {
                            printf("Anda telah logout. Kembali ke menu utama...\n");
                            continue;
                        }else if (pilih == 2){
                            break;
                        }
                    }else if (pilihan == 2)
                    {
                        if (strlen(peserta.namaLengkap) == 0)
                        {
                            printf("Belum bisa melihat kartu UTBK. Daftar terlebih dahulu.\n");
                            printf("Tekan enter untuk logout.");
                            getchar();
                        } else {
                            tampilkanKartuPeserta(&peserta, &stack, hasil);
                            printf("Tekan enter untuk logout.");
                            getchar();                            
                        }
                    }
                    
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