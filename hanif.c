#include "hanif.h"

void displayBiodata(Peserta *peserta){
    int choice;
    do {
        system("cls");
        printf("===================================================\n");
        printf("     PROGRAM PENDAFTARAN UTBK - Peserta Peserta       \n");
        printf("===================================================\n\n");

        printf("  >>> Peserta DIRI CALON PESERTA <<<\n");
        printf("  1. Nama Lengkap (sesuai ijazah) : ");
        fgets(peserta->namaLengkap, sizeof(peserta->namaLengkap), stdin);
        peserta->namaLengkap[strcspn(peserta->namaLengkap, "\n")] = 0;

        printf("  2. Tempat Lahir                 : ");
        fgets(peserta->tempatLahir, sizeof(peserta->tempatLahir), stdin);
        peserta->tempatLahir[strcspn(peserta->tempatLahir, "\n")] = 0;

        printf("  3. Tanggal Lahir (DD-MM-YYYY)   : ");
        fgets(peserta->tanggalLahir, sizeof(peserta->tanggalLahir), stdin);
        peserta->tanggalLahir[strcspn(peserta->tanggalLahir, "\n")] = 0;

        printf("  4. NISN                         : ");
        fgets(peserta->nisn, sizeof(peserta->nisn), stdin);
        peserta->nisn[strcspn(peserta->nisn, "\n")] = 0;

        printf("  5. NPSN                         : ");
        fgets(peserta->npsn, sizeof(peserta->npsn), stdin);
        peserta->npsn[strcspn(peserta->npsn, "\n")] = 0;

        printf("  6. Nama Sekolah                 : ");
        fgets(peserta->namaSekolah, sizeof(peserta->namaSekolah), stdin);
        peserta->namaSekolah[strcspn(peserta->namaSekolah, "\n")] = 0;

        printf("\n  >>> Peserta ORANG TUA/WALI <<<\n");
        printf("  7. Nama Ayah                    : ");
        fgets(peserta->namaAyah, sizeof(peserta->namaAyah), stdin);
        peserta->namaAyah[strcspn(peserta->namaAyah, "\n")] = 0;

        printf("  8. Nama Ibu                     : ");
        fgets(peserta->namaIbu, sizeof(peserta->namaIbu), stdin);
        peserta->namaIbu[strcspn(peserta->namaIbu, "\n")] = 0;

        printf("  9. Jml.Tanggungan               : ");
        fgets(peserta->jumlahTanggungan, sizeof(peserta->jumlahTanggungan), stdin);
        peserta->jumlahTanggungan[strcspn(peserta->jumlahTanggungan, "\n")] = 0;

        printf(" 10. Gaji Ayah (per bulan)        : ");
        fgets(peserta->gajiAyah, sizeof(peserta->gajiAyah), stdin);
        peserta->gajiAyah[strcspn(peserta->gajiAyah, "\n")] = 0;

        printf(" 11. Gaji Ibu (per bulan)         : ");
        fgets(peserta->gajiIbu, sizeof(peserta->gajiIbu), stdin);
        peserta->gajiIbu[strcspn(peserta->gajiIbu, "\n")] = 0;

        system("cls");
   printf("===================================================\n");
   printf("     PROGRAM PENDAFTARAN UTBK - Ringkasan Peserta     \n");
   printf("===================================================\n\n");
   printf("  >>> Peserta DIRI CALON PESERTA <<<\n");
   printf("  Nama Lengkap    : %s\n", peserta->namaLengkap);
   printf("  Tempat Lahir    : %s\n", peserta->tempatLahir);
   printf("  Tanggal Lahir   : %s\n", peserta->tanggalLahir);
   printf("  NISN            : %s\n", peserta->nisn);
   printf("  NPSN            : %s\n", peserta->npsn);
   printf("  Nama Sekolah    : %s\n", peserta->namaSekolah);
   printf("\n  >>> Peserta ORANG TUA/WALI <<<\n");
   printf("  Nama Ayah       : %s\n", peserta->namaAyah);
   printf("  Nama Ibu        : %s\n", peserta->namaIbu);
   printf("  Jumlah Tanggungan wali : %s\n", peserta->jumlahTanggungan);
   printf("  Gaji Ayah       : %s\n", peserta->gajiAyah);
   printf("  Gaji Ibu        : %s\n", peserta->gajiIbu);
   printf("\n===================================================\n");
   printf("  Opsi:\n");
   printf("  0-> Kembali (Ubah Peserta)\n");
   printf("  1-> Batalkan Pendaftaran\n");
   printf("  2-> Simpan dan Lanjutkan ( program studi)\n");
   printf("===================================================\n");
        printf("  Pilih opsi: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        if (choice == 2) {
            printf("\nPeserta berhasil disimpan dan akan dilanjutkan ke pemilihan program studi!\n");
            printf("Tekan Enter untuk melanjutkan ke halaman selanjutnya->\n");
            getchar();
            break;
        } else if (choice == 1) {
            printf("\nPendaftaran dibatalkan-> Terima kasih!\n");
        } else if (choice == 0) {
            printf("\nKembali untuk mengubah peserta->->->\n");
            printf("Tekan Enter untuk melanjutkan->\n");
            getchar();
        } else {
            printf("\nPilihan tidak valid! Tekan Enter untuk coba lagi->\n");
            getchar();
            choice = 0;
        }

    } while (choice == 0);

    printf("\n[Implementasi untuk 'Memilih program studi' akan Pesertang di sini->]\n");
    printf("Terima kasih telah menggunakan program pendaftaran UTBK->\n");
    printf("Tekan Enter untuk keluar->\n");
    getchar();

}

void addPeserta(Peserta* peserta,User* user){
FILE* file;
file = fopen("BasisDataBiodata.txt","a");
fprintf(file,"%s,%s\n",user->email,user->password);
fprintf(file, "Nama Lengkap    : %s\n", peserta->namaLengkap);
fprintf(file, "Tempat Lahir    : %s\n", peserta->tempatLahir);
fprintf(file, "Tanggal Lahir   : %s\n", peserta->tanggalLahir);
fprintf(file, "NISN            : %s\n", peserta->nisn);
fprintf(file, "NPSN            : %s\n", peserta->npsn);
fprintf(file, "Nama Sekolah    : %s\n", peserta->namaSekolah);
fprintf(file, "Nama Ayah       : %s\n", peserta->namaAyah);
fprintf(file, "Nama Ibu        : %s\n", peserta->namaIbu);
fprintf(file, "Jumlah Tanggungan : %s\n",peserta->jumlahTanggungan);
fprintf(file, "Gaji Ayah       : %s\n", peserta->gajiAyah);
fprintf(file, "Gaji Ibu        : %s\n", peserta->gajiIbu);
fclose(file);
}