#include "farell.h"


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
    printf("Registrasi berhasil!\n");
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

void isiBiodata(dataPeserta** pesertaHead, char* nisn) {
    dataPeserta* peserta = (dataPeserta*)malloc(sizeof(dataPeserta));
    char nisnTruncated[5] = {0};
    for (int i = 0; i < 4 && nisn[i] != '\0'; i++) {
        nisnTruncated[i] = nisn[i];
    }
    strcpy(peserta->nisn, nisnTruncated);
    printf("Pengisian Biodata\n");
    printf("Nama: ");
    fgets(peserta->nama, MAX_NAMA, stdin);
    peserta->nama[strcspn(peserta->nama, "\n")] = 0;
    strcpy(peserta->status, "Menunggu");
    peserta->next = NULL;
    tambahPeserta(pesertaHead, peserta);
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

dataPeserta* cariPeserta(dataPeserta* head, char* nisn) {
    dataPeserta* current = head;
    while (current != NULL) {
        if (strcmp(current->nisn, nisn) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void enqueuePeserta(Queue* Q, const char* nisn, dataPeserta* pesertaHead) {
    dataPeserta* peserta = cariPeserta(pesertaHead, (char*)nisn);
    if (peserta == NULL) {
        printf("Peserta dengan NISN %s tidak ditemukan!\n", nisn);
        return;
    }
    int id = atoi(nisn);
    printf("Enqueuing ID: %d for NISN: %s\n", id, nisn);
    infotype dataToEnqueue;
    strcpy(dataToEnqueue.prodi, nisn);
    EnQueue(Q, dataToEnqueue);
}


dataPeserta* dequeuePeserta(Queue* Q, dataPeserta* pesertaHead) {
    infotype id;
    if (!is_Empty(*Q)) {
        deQueue(Q, &id);
        char nisn[5];
        sprintf(nisn, "%d", id);
        printf("Debug: Dequeuing ID %d, searching NISN %s\n", id, nisn);
        dataPeserta* peserta = cariPeserta(pesertaHead, nisn);
        if (peserta == NULL) {
            printf("Warning: No matching peserta for ID %d (NISN %s)\n", id, nisn);
        } else {
            printf("Debug: Found peserta with NISN %s\n", peserta->nisn);
        }
        return peserta;
    }
    printf("Antrean kosong!\n");
    return NULL;
}

void lihatAntrian(Queue Q, dataPeserta* pesertaHead) {
    if (is_Empty(Q)) {
        printf("Antrean kosong!\n");
        return;
    }
    printf("Daftar Antrian:\n");
    address current = First(Q.L);
    int i = 1;
    int found = 0;
    while (current != NULL) {
        char nisn[5];
        sprintf(nisn, "%d", Info(current));
        dataPeserta* peserta = cariPeserta(pesertaHead, nisn);
        if (peserta != NULL) {
            printf("%d. NISN: %s, Nama: %s, Status: %s\n", i++, peserta->nisn, peserta->nama, peserta->status);
            found = 1;
        } else {
            printf("Debug: No peserta found for ID %d\n", Info(current));
        }
        current = Next(current);
    }
    if (!found) {
        printf("Tidak ada data peserta yang dapat ditampilkan untuk antrean saat ini.\n");
    }
}

void konfirmasiAntrian(Queue* Q, dataPeserta* pesertaHead) {
    dataPeserta* peserta = dequeuePeserta(Q, pesertaHead);
    if (peserta != NULL) {
        strcpy(peserta->status, "Dikonfirmasi");
        printf("Pendaftar dengan NISN %s dikonfirmasi!\n", peserta->nisn);
    }
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