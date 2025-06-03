#include "sda.h"

int main() {
    User* akunHead = NULL;
    Queue antrean;
    CreateQueue(&antrean);
    dataPeserta* pesertaHead = NULL; // Linked List untuk menyimpan data peserta
    int pilihan;
    char email[MAX_EMAIL], password[MAX_PASSWORD];

    bacaAkunDariFile(&akunHead);

    while (1) {
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
                registrasiAkun(&akunHead);
                break;
            case 2:
                printf("Login Akun SNBT\n");
                printf("Masukkan email: ");
                fgets(email, MAX_EMAIL, stdin);
                email[strcspn(email, "\n")] = 0;
                printf("Masukkan Password: ");
                fgets(password, MAX_PASSWORD, stdin);
                password[strcspn(password, "\n")] = 0;

                if (loginAkun(akunHead, email, password)) {
                    if (strcmp(email, "admin@admin.com") == 0) {
                        while (1) {
                            printf("Selamat Datang Admin\n");
                            printf("1. Lihat Antrian\n2. Konfirmasi Antrian\n3. Keluar\n");
                            printf("Masukkan pilihan: ");
                            scanf("%d", &pilihan);
                            getchar();
                            if (pilihan == 1) lihatAntrian(antrean, pesertaHead);
                            else if (pilihan == 2) konfirmasiAntrian(&antrean, pesertaHead);
                            else if (pilihan == 3) break;
                        }
                    } else {
                        char nisn[MAX_NISN];
                        printf("Masukkan NISN: ");
                        fgets(nisn, MAX_NISN, stdin);
                        nisn[strcspn(nisn, "\n")] = 0;
                        dataPeserta* peserta = cariPeserta(pesertaHead, nisn);
                        if (peserta == NULL) {
                            isiBiodata(&pesertaHead, nisn);
                            enqueuePeserta(&antrean, nisn, pesertaHead);
                            printf("Pendaftaran berhasil, menunggu konfirmasi admin.\n");
                        } else {
                            printf("NISN sudah terdaftar!\n");
                        }
                    }
                }
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
}