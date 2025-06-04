#include "hanif.h"
#include "SpNRSLL.H"
#include "STACK.H"

void displayPemilihanProdi(Stack *stack) {
    char* PTN[55] = {
    "Universitas Indonesia (UI)", "Universitas Gadjah Mada (UGM)", "Institut Teknologi Bandung (ITB)", "Universitas Brawijaya (UB)", "Universitas Airlangga (Unair)", "IPB University", "Universitas Sebelas Maret (UNS)", "Universitas Diponegoro (Undip)", "Institut Teknologi Sepuluh Nopember (ITS)", "Universitas Pendidikan Indonesia (UPI)",
    "Universitas Hasanuddin (Unhas)", "Universitas Sumatera Utara (USU)", "Universitas Andalas (Unand)", "Universitas Negeri Malang (UM)", "Universitas Negeri Yogyakarta (UNY)", "Universitas Jember (Unej)", "Universitas Negeri Semarang (Unnes)", "Universitas Lampung (Unila)", "Universitas Syiah Kuala (USK)", "Universitas Udayana (Unud)",
    "Universitas Riau (Unri)", "Universitas Mataram (Unram)", "Universitas Negeri Makassar (UNM)", "Universitas Negeri Padang (UNP)", "Universitas Negeri Surabaya (Unesa)", "Universitas Negeri Medan (Unimed)", "Universitas Negeri Jakarta (UNJ)", "Universitas Sultan Ageng Tirtayasa (Untirta)", "Universitas Muhammadiyah Surakarta (UMS)", "Universitas Lampung (Unila)",
    "Institut Teknologi Bandung (ITB)", "Institut Pertanian Bogor (IPB University)", "Institut Teknologi Sepuluh Nopember (ITS)", "Institut Teknologi Nasional (ITENAS)", "Institut Teknologi Telkom Purwokerto", "Institut Teknologi Nasional Malang (ITN Malang)", "Institut Teknologi Kalimantan (ITK)", "Institut Teknologi Sumatera (ITERA)", "Institut Teknologi Del", "Institut Seni Indonesia Yogyakarta (ISI Yogyakarta)",
    "Politeknik Elektronika Negeri Surabaya (PENS)", "Politeknik Negeri Medan (Polmed)", "Politeknik LP3I Bandung", "Politeknik Manufaktur Negeri Bangka Belitung", "Politeknik Pertanian Negeri Kupang", "Politeknik Negeri Lhokseumawe", "Politeknik Perkapalan Negeri Surabaya", "Politeknik Negeri Tanah Laut", "Politeknik Negeri Banjarmasin", "Politeknik Negeri Batam",
    "Politeknik Negeri Jakarta (PNJ)", "Politeknik Negeri Bandung (Polban)", "Politeknik Negeri Semarang (Polines)", "Politeknik Negeri Sriwijaya (Polsri)", "Politeknik Negeri Malang (Polinema)"
};

char* jurusanUniversitas[] = {
    "Kedokteran", "Hukum", "Ilmu Komunikasi", "Psikologi", "Manajemen", "Akuntansi", "Ilmu Politik", "Sastra Inggris",
    "Sastra Indonesia", "Hubungan Internasional", "Ilmu Pemerintahan", "Teknik Sipil", "Teknik Elektro", "Teknik Industri",
    "Teknik Kimia", "Arsitektur", "Pendidikan Matematika", "Pendidikan Bahasa Inggris", "Pendidikan Guru Sekolah Dasar",
    "Pendidikan Biologi", "Agribisnis", "Peternakan", "Ilmu Komputer", "Statistika", "Ekonomi Pembangunan"
};

char* jurusanInstitut[] = {
    "Teknik Informatika", "Sistem Informasi", "Teknik Elektro", "Teknik Mesin", "Teknik Sipil", "Teknik Kimia", "Teknik Fisika",
    "Teknik Biomedik", "Rekayasa Perangkat Lunak", "Teknik Industri", "Teknik Lingkungan", "Teknik Geofisika", "Teknik Geologi",
    "Teknik Material", "Matematika", "Fisika", "Biologi", "Desain Produk", "Desain Komunikasi Visual", "Aktuaria"
};

char* jurusanPoliteknik[] = {
    "Teknik Informatika", "Teknik Komputer", "Manajemen Informatika", "Teknik Elektronika", "Teknik Telekomunikasi",
    "Teknik Mesin", "Teknik Pendingin dan Tata Udara", "Teknik Sipil", "Akuntansi", "Administrasi Bisnis", "Perhotelan",
    "Pariwisata", "Teknik Listrik", "Manufaktur", "Teknik Otomotif", "Teknik Kimia Industri", "Teknik Instrumentasi",
    "Logistik Industri", "Keuangan dan Perbankan", "Teknik Energi Terbarukan"
};

    Prodi input;
    char pilihan;
    int i = 1;
    int jumlahProdi = 0;

    do {
        if (jumlahProdi >= 4) {
            printf("\nSudah memilih maksimal 4 prodi.\n");
            break;
        }
        printf("\n=== Pemilihan Prodi ke-%d ===\n", i);
        printf("Masukkan nama Universitas: ");
        fgets(input.universitas, sizeof(input.universitas), stdin);
        input.universitas[strcspn(input.universitas, "\n")] = '\0';

        printf("Masukkan nama Program Studi: ");
        fgets(input.prodi, sizeof(input.prodi), stdin);
        input.prodi[strcspn(input.prodi, "\n")] = '\0';

        printf("\nPilihan:\n");
        printf("1. Batal (hapus prodi terakhir)\n");
        printf("2. Simpan dan Tambah Prodi\n");
        printf("3. Simpan dan Lanjutkan (ke tahap selanjutnya)\n");
        printf("Masukkan pilihan (1/2/3): ");
        scanf(" %c", &pilihan);
        getchar();  // Bersihkan newline

        if (pilihan == '1') {
            Prodi removed;
            if (jumlahProdi == 0) {
                printf("Belum ada prodi yang dipilih.\n");
            } else {
                Pop(stack, &removed);
                printf("Berhasil Menghapus Prodi");
                printStack(*stack);
                i--;
                jumlahProdi--;
            }
        } else if (pilihan == '2') {
            Push(stack, input);
            printStack(*stack);
            i++;
            jumlahProdi++;
        } else if (pilihan == '3') {
            Push(stack, input);
            printStack(*stack);
            printf("Berhasil Memilih Prodi");
            break;
        } else {
            printf("Pilihan tidak valid.\n");
        }

    } while (1);
}

void printStack(Stack S) {
    address p = First(S.Top);
    int i = 1;
    if (p == NULL) {
        printf("Belum ada prodi yang dipilih.\n");
        return;
    }
    printf("\n\n=================================\n");
    printf("     Daftar Pilihan Prodi\n");
    printf("=================================\n");
    while (p != NULL) {
        printf("%d. Universitas: %s | Prodi: %s\n", i, p->info.universitas, p->info.prodi);
        p = p->next;
        i++;
    }
}

void pilihProdi(Stack* S,Prodi P){
    Push(S, P);  
    printf("\nProdi berhasil ditambahkan.\n");
    printf("=== Daftar Prodi Saat Ini ===\n");
    printStack(*S);
}

void hapusProdi(Stack* S){
    if (!IsEmpty(*S)) {
        Prodi removed;
        Pop(S, &removed);
        printf("\nProdi terakhir telah dihapus:\n");
        printf("Universitas: %s | Prodi: %s\n", removed.universitas, removed.prodi);
    } else {
        printf("\nStack kosong. Tidak ada prodi yang bisa dihapus.\n");
    }

    printf("\n=== Daftar Prodi Saat Ini ===\n");
    printStack(*S);
}
