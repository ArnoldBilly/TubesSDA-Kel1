#include "hanif.h"


void displayBiodata(){
    char namaLengkap[100];
    char tempatLahir[50];
    char tanggalLahir[20];
    char nisn[15];
    char npsn[15];
    char namaSekolah[100];
    char namaAyah[100];
    char namaIbu[100];
    char jumlahTanggungan[10];
    char gajiAyah[50];
    char gajiIbu[50];

    int choice;

    do {
        system("cls");
        printf("===================================================\n");
        printf("     PROGRAM PENDAFTARAN UTBK - Data Peserta       \n");
        printf("===================================================\n\n");

        printf("  >>> DATA DIRI CALON PESERTA <<<\n");
        printf("  1. Nama Lengkap (sesuai ijazah) : ");
        fgets(namaLengkap, sizeof(namaLengkap), stdin);
        namaLengkap[strcspn(namaLengkap, "\n")] = 0;

        printf("  2. Tempat Lahir                 : ");
        fgets(tempatLahir, sizeof(tempatLahir), stdin);
        tempatLahir[strcspn(tempatLahir, "\n")] = 0;

        printf("  3. Tanggal Lahir (DD-MM-YYYY)   : ");
        fgets(tanggalLahir, sizeof(tanggalLahir), stdin);
        tanggalLahir[strcspn(tanggalLahir, "\n")] = 0;

        printf("  4. NISN                         : ");
        fgets(nisn, sizeof(nisn), stdin);
        nisn[strcspn(nisn, "\n")] = 0;

        printf("  5. NPSN                         : ");
        fgets(npsn, sizeof(npsn), stdin);
        npsn[strcspn(npsn, "\n")] = 0;

        printf("  6. Nama Sekolah                 : ");
        fgets(namaSekolah, sizeof(namaSekolah), stdin);
        namaSekolah[strcspn(namaSekolah, "\n")] = 0;

        printf("\n  >>> DATA ORANG TUA/WALI <<<\n");
        printf("  7. Nama Ayah                    : ");
        fgets(namaAyah, sizeof(namaAyah), stdin);
        namaAyah[strcspn(namaAyah, "\n")] = 0;

        printf("  8. Nama Ibu                     : ");
        fgets(namaIbu, sizeof(namaIbu), stdin);
        namaIbu[strcspn(namaIbu, "\n")] = 0;

        printf("  9. Jumlah Tanggungan Keluarga   : ");
        fgets(jumlahTanggungan, sizeof(jumlahTanggungan), stdin);
        jumlahTanggungan[strcspn(jumlahTanggungan, "\n")] = 0;

        printf(" 10. Gaji Ayah (per bulan)        : ");
        fgets(gajiAyah, sizeof(gajiAyah), stdin);
        gajiAyah[strcspn(gajiAyah, "\n")] = 0;

        printf(" 11. Gaji Ibu (per bulan)         : ");
        fgets(gajiIbu, sizeof(gajiIbu), stdin);
        gajiIbu[strcspn(gajiIbu, "\n")] = 0;


        // Bagian Review Data
        system("cls"); // Membersihkan layar (khusus Windows)
        printf("===================================================\n");
        printf("     PROGRAM PENDAFTARAN UTBK - Ringkasan Data     \n");
        printf("===================================================\n\n");
        printf("  >>> DATA DIRI CALON PESERTA <<<\n");
        printf("  Nama Lengkap    : %s\n", namaLengkap);
        printf("  Tempat Lahir    : %s\n", tempatLahir);
        printf("  Tanggal Lahir   : %s\n", tanggalLahir);
        printf("  NISN            : %s\n", nisn);
        printf("  NPSN            : %s\n", npsn);
        printf("  Nama Sekolah    : %s\n", namaSekolah);
        printf("\n  >>> DATA ORANG TUA/WALI <<<\n");
        printf("  Nama Ayah       : %s\n", namaAyah);
        printf("  Nama Ibu        : %s\n", namaIbu);
        printf("  Jml. Tanggungan : %s\n", jumlahTanggungan);
        printf("  Gaji Ayah       : %s\n", gajiAyah);
        printf("  Gaji Ibu        : %s\n", gajiIbu);
        printf("\n===================================================\n");
        printf("  Pilihan:\n");
        printf("  0. Kembali (Ubah Data)\n");
        printf("  1. Batalkan Pendaftaran\n");
        printf("  2. Simpan dan Lanjutkan ( program studi)\n");
        printf("===================================================\n");
        printf("  Pilih opsi: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Konsumsi newline

        if (choice == 1) {
            printf("\nData berhasil disimpan!\n");
            printf("Tekan Enter untuk melanjutkan ke halaman selanjutnya.\n");
            getchar();
            break;
        } else if (choice == 2) {
            printf("\nPendaftaran dibatalkan. Terima kasih!\n");
        } else if (choice == 3) {
            printf("\nMelanjutkan ke pemilihan program studi...\n");
            printf("Tekan Enter untuk melanjutkan ke halaman selanjutnya.\n");
            getchar();
            break;
        }

    } while (choice == 0);

    printf("\n[Implementasi untuk 'Memilih program studi' akan datang di sini.]\n");
    printf("Terima kasih telah menggunakan program pendaftaran UTBK.\n");
    printf("Tekan Enter untuk keluar.\n");
    getchar();
}