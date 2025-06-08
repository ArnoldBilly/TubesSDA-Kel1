#include "farell.h"
#include "hanif.h"


void menuUtama(User** akunHead, Queue* antrean, dataPeserta** pesertaHead) {
    int pilihan;
    char email[MAX_EMAIL], password[MAX_PASSWORD];

        printf("Raih masa depanmu di portal SNBT\n");
        printf("Belum memiliki akun SNBT?\n");
        printf("1. Registrasi\n");
        printf("Sudah memiliki akun SNBT?\n");
        printf("2. Login\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                registrasiAkun(akunHead);
                break;
            case 2:
                prosesLogin(*akunHead, antrean, pesertaHead);
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
}

void tambahAkun(User** head, const char* email, const char* password) {
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->email, email);
    strcpy(newUser->password, password);
    newUser->next = *head;
    *head = newUser;
}

void simpanAkunKeFile(User* head) {
    FILE* file = fopen("akun.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file akun.txt!\n");
        return;
    }
    User* current = head;
    while (current != NULL) {
        fprintf(file, "%s %s\n", current->email, current->password);
        current = current->next;
    }
    fclose(file);
}

void bacaAkunDariFile(User** head) {
    FILE* file = fopen("akun.txt", "r");
    if (file == NULL) {
        printf("File akun.txt tidak ditemukan, membuat file baru.\n");
        file = fopen("akun.txt", "w");
        if (file == NULL) {
            printf("Gagal membuat file akun.txt!\n");
            return;
        }
        fprintf(file, "admin@admin.com admin\n");
        fclose(file);
        file = fopen("akun.txt", "r");
    }
    char email[MAX_EMAIL], password[MAX_PASSWORD];
    while (fscanf(file, "%s %s", email, password) != EOF) {
        tambahAkun(head, email, password);
    }
    fclose(file);
}

void registrasiAkun(User** head) {
    char email[MAX_EMAIL], password[MAX_PASSWORD];
    printf("Registrasi Akun SNBT\n");
    printf("Masukkan email: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strcspn(email, "\n")] = 0;
    printf("Masukkan Password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    User* current = *head;
    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            printf("Email sudah terdaftar!\n");
            return;
        }
        current = current->next;
    }

    tambahAkun(head, email, password);
    simpanAkunKeFile(*head);
    printf("Registrasi berhasil!. Silahkan Login kembali!\n");
}

int loginAkun(User* head, char* email, char* password) {
    User* current = head;
    while (current != NULL) {
        if (strcmp(current->email, email) == 0 && strcmp(current->password, password) == 0) {
            printf("Login berhasil!\n");
            return 1;
        }
        current = current->next;
    }
    printf("Email atau password salah!\n");
    return 0;
}

void isiBiodata(dataPeserta** pesertaHead, char* nisn, Peserta* peserta) {
    dataPeserta* existing = cariPeserta(*pesertaHead, nisn);
    if (existing != NULL) {
        printf("Peserta dengan NISN %s sudah terdaftar!\n", nisn);
        return;
    }

    dataPeserta* newPeserta = (dataPeserta*)malloc(sizeof(dataPeserta));
    if (newPeserta != NULL) {
        strcpy(newPeserta->nisn, nisn);
        strcpy(newPeserta->nama, peserta->namaLengkap); // Ambil nama dari Peserta
        strcpy(newPeserta->status, "Menunggu");
        newPeserta->next = NULL;
        tambahPeserta(pesertaHead, newPeserta);
        printf("Biodata disimpan untuk NISN: %s\n", nisn);
    }
}

void tambahPeserta(dataPeserta** head, dataPeserta* peserta) {
    if (*head == NULL) {
        *head = peserta;
    } else {
        dataPeserta* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = peserta;
    }
}

dataPeserta* cariPeserta(dataPeserta* head, const char* nisn) {
    dataPeserta* current = head;
    while (current != NULL) {
        if (strcmp(current->nisn, nisn) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void enqueuePeserta(Queue* Q, const char* nisn, dataPeserta* pesertaHead, Peserta* pesertaHanif) {
    dataPeserta* peserta = cariPeserta(pesertaHead, nisn);
    if (peserta == NULL) {
        printf("Peserta dengan NISN %s tidak ditemukan!\n", nisn);
        return;
    }
    QueueInfo dataToEnqueue;
    strcpy(dataToEnqueue.nisn, pesertaHanif->nisn);
    strcpy(dataToEnqueue.namaLengkap, pesertaHanif->namaLengkap);
    printf("Antiran peserta: %s (NISN: %s)\n", dataToEnqueue.namaLengkap, dataToEnqueue.nisn);
    EnQueue(Q, dataToEnqueue);
}


dataPeserta* dequeuePeserta(Queue* Q, dataPeserta* pesertaHead) {
    QueueInfo info;
    if (!is_Empty(*Q)) {
        deQueue(Q, &info);
        dataPeserta* peserta = cariPeserta(pesertaHead, info.nisn);
        if (peserta == NULL) {
            printf("Peserta dengan ID %d (NISN %s) tidak ditemukan\n", info.nisn);
        } else {
            printf("Peserta ditemukan dengan NISN %s\n", peserta->nisn);
        }
        return peserta;
    }
    printf("Antrean kosong!\n");
    return NULL;
}

void lihatAntrian(Queue Q, dataPeserta* pesertaHead) {
    if (is_Empty(Q)) {
        printf("=== Daftar Antrian Kosong ===\n");
        printf("Tekan Enter untuk kembali ke menu admin...\n");
        getchar();
        return;
    }
    printf("=== Daftar Antrian Peserta ===\n");
    printf("--------------------------------\n");
    queueAddress current = First(Q.L);
    int i = 1;
    while (current != NULL) {
        QueueInfo info = current->info;
        dataPeserta* peserta = cariPeserta(pesertaHead, info.nisn);
        printf("%d. NISN: %s | Nama: %s | Status: %s\n",
               i++, info.nisn, info.namaLengkap,
               peserta ? peserta->status : "Tidak Diketahui");
        current = current->next;
    }
    printf("--------------------------------\n");
    printf("Tekan Enter untuk kembali ke menu admin...\n");
    getchar();
}

void konfirmasiAntrian(Queue* Q, dataPeserta* pesertaHead) {
    if (is_Empty(*Q)) {
        printf("=== Antrian Kosong ===\n");
        printf("Tidak ada peserta untuk dikonfirmasi.\n");
        printf("Tekan Enter untuk kembali ke menu admin...\n");
        getchar();
        return;
    }

    // Ambil peserta pertama (FIFO)
    queueAddress first = First(Q->L);
    QueueInfo info = first->info;
    dataPeserta* peserta = cariPeserta(pesertaHead, info.nisn);

    if (peserta != NULL) {
        printf("=== Konfirmasi Antrian Peserta ===\n");
        printf("--------------------------------\n");
        printf("Peserta: NISN: %s | Nama: %s | Status: %s\n",
               info.nisn, info.namaLengkap, peserta->status);
        printf("--------------------------------\n");

        char konfirmasi;
        printf("Konfirmasi peserta %s (NISN: %s)? (y/n): ", info.namaLengkap, info.nisn);
        scanf(" %c", &konfirmasi);
        getchar();

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            strcpy(peserta->status, "Dikonfirmasi");
            Q->L.First = first->next;
            printf("Status diperbarui untuk NISN %s: %s\n", peserta->nisn, peserta->status);
            free(first);
            printf("Peserta dengan NISN %s berhasil dikonfirmasi!\n", peserta->nisn);
        } else {
            printf("Konfirmasi dibatalkan untuk peserta %s.\n", info.namaLengkap);
        }
    } else {
        printf("Peserta dengan NISN %s tidak ditemukan dalam data.\n", info.nisn);
    }
    printf("Tekan Enter untuk kembali ke menu admin...\n");
    getchar();
}

void prosesLogin(User* akunHead, Queue* antrean, dataPeserta** pesertaHead) {
    char email[MAX_EMAIL], password[MAX_PASSWORD];
    printf("Login Akun SNBT\n");
    printf("Masukkan email: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strcspn(email, "\n")] = 0;
    printf("Masukkan Password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    if (loginAkun(akunHead, email, password)) {
        if (strcmp(email, "admin@admin.com") == 0) {
            menuAdmin(antrean, *pesertaHead);
        } else {
            printf("Login Berhasil. Selamat datang!.\n");
            return;
        }
    } else {
        printf("Login gagal! Email atau password salah.\n");
    }
}

void menuAdmin(Queue* antrean, dataPeserta* pesertaHead) {
    int pilihan;
    while (1) {
        printf("Selamat Datang Admin\n");
        printf("1. Lihat Antrian\n2. Konfirmasi Antrian\n3. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        getchar();
        if (pilihan == 1) lihatAntrian(*antrean, pesertaHead);
        else if (pilihan == 2) konfirmasiAntrian(antrean, pesertaHead);
        else if (pilihan == 3) break;
        else printf("Pilihan tidak valid!\n");
    }
}

void tampilkanKartuPeserta(Peserta* peserta, Stack* stackProdi, Address lokasiUjian) {
    printf("\n===================================================\n");
    printf("           KARTU PESERTA UTBK-SNBT           \n");
    printf("===================================================\n\n");

    printf("Nama Lengkap    : %s\n", peserta->namaLengkap);
    printf("Tanggal Lahir   : %s\n", peserta->tanggalLahir);
    printf("NISN            : %s\n", peserta->nisn);

    printf("\nPilihan Program Studi:\n");
    if (IsEmpty(*stackProdi)) {
        printf("  Belum ada prodi yang dipilih.\n");
    } else {
        char pilihanUniversitas[4][64];
        char pilihanProdi[4][32];
        int i = 0;

        for (address p = First(stackProdi->Top); p != NULL && i < 4; p = p->next) {
            strcpy(pilihanUniversitas[i], p->info.universitas);
            strcpy(pilihanProdi[i], p->info.prodi);
            i++;
        }

        for (int idx = i - 1, no = 1; idx >= 0; idx--, no++) {
            printf("  Pilihan %d: %s - %s\n", no, pilihanUniversitas[idx], pilihanProdi[idx]);
        }
    }

    printf("\nLokasi Ujian    : %s\n", lokasiUjian ? lokasiUjian->namaUniv : "Belum ditentukan");

    printf("===================================================\n\n");
}