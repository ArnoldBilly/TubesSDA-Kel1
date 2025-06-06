#include "hanif.h"
#include "SpNRSLL.H"
#include "STACK.H"


void displayPemilihanProdi(Stack *stack) {
    char* PTN[30] = {
        "Universitas Indonesia (UI)", "Universitas Gadjah Mada (UGM)", "Universitas Brawijaya (UB)", "Universitas Airlangga (Unair)", "Universitas Sebelas Maret (UNS)",
        "Universitas Diponegoro (Undip)", "Universitas Pendidikan Indonesia (UPI)", "Universitas Hasanuddin (Unhas)", "Universitas Sumatera Utara (USU)", "Universitas Andalas (Unand)",
        "Universitas Negeri Malang (UM)", "Universitas Negeri Yogyakarta (UNY)", "Universitas Jember (Unej)", "Universitas Negeri Semarang (Unnes)", "Universitas Lampung (Unila)",
        "Universitas Syiah Kuala (USK)", "Universitas Udayana (Unud)", "Universitas Riau (Unri)", "Universitas Mataram (Unram)", "Universitas Negeri Padang (UNP)",
        "Institut Teknologi Bandung (ITB)", "Institut Teknologi Sepuluh Nopember (ITS)", "Institut Pertanian Bogor (IPB University)", "Institut Teknologi Kalimantan (ITK)", "Institut Teknologi Sumatera (ITERA)",
        "Institut Teknologi Del", "Institut Seni Indonesia Yogyakarta (ISI Yogyakarta)", "Institut Seni Indonesia Surakarta (ISI Surakarta)", "Institut Seni Indonesia Padangpanjang (ISI Padangpanjang)", "Institut Seni Budaya Indonesia Bandung (ISBI Bandung)"
    };

    char* jurusanUniversitas[] = {
        "Kedokteran", "Hukum", "Ilmu Komunikasi", "Psikologi", "Manajemen", "Akuntansi", "Ilmu Politik", "Sastra Inggris",
        "Sastra Indonesia", "Hubungan Internasional", "Ilmu Pemerintahan", "Teknik Sipil", "Teknik Elektro", "Teknik Industri",
        "Teknik Kimia", "Arsitektur", "Pendidikan Matematika", "Pendidikan Bahasa Inggris", "Pendidikan Guru Sekolah Dasar",
        "Pendidikan Biologi", "Agribisnis", "Peternakan", "Ilmu Komputer", "Statistika", "Ekonomi Pembangunan"
    };

    Prodi input;
    char pilihan;
    int i = 1;
    int jumlahProdi = 0;
    const int TOTAL_PTN   = 30;
    const int TOTAL_PRODI = 25;
    int nomorPTN;
    int nomorProdi;

    for (address p = First(stack->Top); p != NULL; p = p->next) {
        jumlahProdi++;
    }

    do {
        system("cls");

        if (jumlahProdi >= 4) {
            printf("\n--- Peringatan: Maksimal 4 prodi telah dipilih ---\n");
            printStack(*stack);
            printf("\nAnda hanya bisa membatalkan pilihan terakhir atau melanjutkan.\n");
            printf("1. Batal (hapus prodi terakhir)\n");
            printf("2. Simpan dan Lanjutkan (ke tahap selanjutnya)\n");
            printf("Masukkan pilihan (1/2): ");
            scanf(" %c", &pilihan);
            while (getchar() != '\n');

            if (pilihan == '1') {
                if (jumlahProdi == 0) {
                    printf("Belum ada prodi yang dipilih.\n");
                } else {
                    hapusProdi(stack);
                    jumlahProdi--;
                    if (jumlahProdi < 4) {
                        i = jumlahProdi + 1;
                        continue;
                    } else {
                        continue;
                    }
                }
            } else if (pilihan == '2') {
                printf("\nMelanjutkan ke tahap selanjutnya...\n");
                break;
            } else {
                printf("Pilihan tidak valid, coba lagi.\n");
            }
            continue;
        }

        printf("\n=== Pemilihan Prodi ke-%d ===\n", jumlahProdi + 1);

        printf("\nDaftar Perguruan Tinggi:\n");
        for (int idx = 0; idx < TOTAL_PTN; idx++)
            printf("%d. %s\n", idx + 1, PTN[idx]);

        do {
            printf("Pilih nomor universitas (1-%d): ", TOTAL_PTN);
            if (scanf("%d", &nomorPTN) != 1 || nomorPTN < 1 || nomorPTN > TOTAL_PTN) {
                printf("Input tidak valid, coba lagi.\n");
                while (getchar() != '\n');
            } else break;
        } while (1);
        while (getchar() != '\n');

        strcpy(input.universitas, PTN[nomorPTN - 1]);

        printf("\nDaftar Program Studi:\n");
        for (int idx = 0; idx < TOTAL_PRODI; idx++)
            printf("%d. %s\n", idx + 1, jurusanUniversitas[idx]);

        do {
            printf("Pilih nomor prodi (1-%d): ", TOTAL_PRODI);
            if (scanf("%d", &nomorProdi) != 1 || nomorProdi < 1 || nomorProdi > TOTAL_PRODI) {
                printf("Input tidak valid, coba lagi.\n");
                while (getchar() != '\n');
            } else break;
        } while (1);
        while (getchar() != '\n');

        strcpy(input.prodi, jurusanUniversitas[nomorProdi - 1]);

        if (jumlahProdi > 0) {
            printStack(*stack);
        }

        printf("\nPilihan untuk prodi ini:\n");
        printf("1. Batal (kembali ke pemilihan ini, tanpa menyimpan)\n");
        if (jumlahProdi > 0) {
            printf("2. Batal Pilihan Sebelumnya (hapus prodi terakhir yang tersimpan)\n");
        }
        printf("3. Simpan dan Tambah Prodi\n");
        printf("4. Simpan dan Lanjutkan (ke tahap selanjutnya)\n");
        printf("Masukkan pilihan: ");
        scanf(" %c", &pilihan);
        while (getchar() != '\n');
        system("cls");

        if (pilihan == '1') {
            printf("Anda membatalkan pilihan ini. Kembali ke pemilihan prodi ke-%d.\n", jumlahProdi + 1);
        } else if (pilihan == '2' && jumlahProdi > 0) {
            hapusProdi(stack);
            jumlahProdi--;
            printf("Pilihan sebelumnya dibatalkan. Kembali ke pemilihan prodi ke-%d.\n", jumlahProdi + 1);
        } else if (pilihan == '3') {
            pilihProdi(stack, input);
            jumlahProdi++;
            i = jumlahProdi + 1;
        } else if (pilihan == '4') {
            pilihProdi(stack, input);
            printf("\nMelanjutkan ke tahap selanjutnya...\n");
            break;
        } else {
            printf("Pilihan tidak valid. Kembali ke pemilihan prodi ke-%d.\n", jumlahProdi + 1);
        }

    } while (1);
}

void printStack(Stack S) {
    char pilihanUniversitas[4][64];
    char pilihanProdi[4][32];
    int i = 0;

    if (IsEmpty(S)) {
        printf("\n--- Belum ada prodi yang dipilih ---\n");
        return;
    }

    for (address p = First(S.Top); p != NULL && i < 4; p = p->next) {
        strcpy(pilihanUniversitas[i], p->info.universitas);
        strcpy(pilihanProdi[i], p->info.prodi);
        ++i;
    }

    printf("\n=================================\n");
    printf("     Daftar Pilihan Prodi Saat Ini\n");
    printf("=================================\n");

    for (int idx = i - 1, no = 1; idx >= 0; --idx, ++no) {
        printf("Pilihan %d : %s | Prodi: %s\n",
               no,
               pilihanUniversitas[idx],
               pilihanProdi[idx]);
    }
    printf("=================================\n");
}


void pilihProdi(Stack* S, Prodi P) {
    Push(S, P);
    printf("\nProdi berhasil ditambahkan: %s - %s\n", P.universitas, P.prodi);
}

void hapusProdi(Stack* S) {
    if (!IsEmpty(*S)) {
        Prodi removed;
        Pop(S, &removed);
        printf("\nProdi terakhir telah dihapus:\n");
        printf("Universitas: %s | Prodi: %s\n", removed.universitas, removed.prodi);
    } else {
        printf("\nStack kosong. Tidak ada prodi yang bisa dihapus.\n");
    }
}

void displayBioPeserta(Peserta *peserta){
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