#include "test.h"

Address newNode(const char* nama) {
    int kapasitas = rand() % 50 + 100;
    int jumlahpeserta = rand() % kapasitas;
    Address node = (Address)malloc(sizeof(TreeNode));
    strcpy(node->namaUniv, nama);
    node->kapasitas = kapasitas;
    node->jumlahPeserta = jumlahpeserta;

    node->parent = NULL;
    node->firstChild = NULL;
    node->nextSibling = NULL;
    node->prevSibling = NULL;
    return node;
}

void addChild(Address parent, Address child) {
    child->parent = parent;

    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    } else {
        Address temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
        child->prevSibling = temp;
    }
}

void simpanTreeKeFile(Address root, FILE *f, int level) {
    if (root) {
        for (int i = 0; i < level; i++) fprintf(f, "-");
        fprintf(f, "%s|%d|%d\n", root->namaUniv, root->jumlahPeserta, root->kapasitas);
        simpanTreeKeFile(root->firstChild, f, level + 1);
        simpanTreeKeFile(root->nextSibling, f, level);
    }
}

Address bacaTreeDariFile(FILE *f) {
    char line[MAX_LINE];
    Address stack[100];
    int levelStack[100];
    int top = -1;
    Address root = NULL;

    while (fgets(line, sizeof(line), f)) {
        int level = 0;
        while (line[level] == '-') level++;

        char *content = line + level;
        char *nama = strtok(content, "|");
        int peserta = atoi(strtok(NULL, "|"));
        int kapasitas = atoi(strtok(NULL, "|"));

        Address node = (Address)malloc(sizeof(TreeNode));
        strcpy(node->namaUniv, nama);
        node->kapasitas = kapasitas;
        node->jumlahPeserta = peserta;
        node->firstChild = node->nextSibling = node->prevSibling = node->parent = NULL;

        if (level == 0) {
            root = node;
            top = 0;
            stack[top] = node;
            levelStack[top] = level;
        } else {
            while (top >= 0 && levelStack[top] >= level) top--;
            if (top >= 0) addChild(stack[top], node);
            top++;
            stack[top] = node;
            levelStack[top] = level;
        }
    }
    return root;
}

void loadAtauInit(Address *j, Address *s, Address *k, Address *u, Address *p) {
    FILE *f = fopen("datauniv.txt", "r");

    if (f != NULL) {
        int c = fgetc(f);
        if (c == EOF) {
            fclose(f);
            f = NULL;
        } else {
            ungetc(c, f);
        }
    }

    if (f != NULL) {
        char line[MAX_LINE];
        Address stack[100];
        int levelStack[100];
        int top = -1;
        *j = *s = *k = *u = *p = NULL;

        Address *currentWilayah = NULL;
        Address rootWilayah = NULL;

        while (fgets(line, sizeof(line), f)) {
            if (strncmp(line, "#JAWA", 5) == 0) {
                currentWilayah = j;
                rootWilayah = NULL;
                top = -1;
            } else if (strncmp(line, "#SUMATERA", 9) == 0) {
                currentWilayah = s;
                rootWilayah = NULL;
                top = -1;
            } else if (strncmp(line, "#KALIMANTAN", 11) == 0) {
                currentWilayah = k;
                rootWilayah = NULL;
                top = -1;
            } else if (strncmp(line, "#SULAWESI", 9) == 0) {
                currentWilayah = u;
                rootWilayah = NULL;
                top = -1;
            } else if (strncmp(line, "#PAPUA", 6) == 0) {
                currentWilayah = p;
                rootWilayah = NULL;
                top = -1;
            } else if (currentWilayah && line[0] != '\n') {
                int level = 0;
                while (line[level] == '-') level++;

                char *content = line + level;
                char *nama = strtok(content, "|");
                int peserta = atoi(strtok(NULL, "|"));
                int kapasitas = atoi(strtok(NULL, "|"));

                Address node = (Address)malloc(sizeof(TreeNode));
                strcpy(node->namaUniv, nama);
                node->jumlahPeserta = peserta;
                node->kapasitas = kapasitas;
                node->firstChild = node->nextSibling = node->prevSibling = node->parent = NULL;

                if (level == 0) {
                    rootWilayah = node;
                    *currentWilayah = rootWilayah;
                    top = 0;
                    stack[top] = node;
                    levelStack[top] = level;
                } else {
                    while (top >= 0 && levelStack[top] >= level) top--;
                    if (top >= 0) {
                        Address parent = stack[top];
                        if (parent->firstChild == NULL) {
                            parent->firstChild = node;
                            node->parent = parent;
                        } else {
                            Address sibling = parent->firstChild;
                            while (sibling->nextSibling != NULL) sibling = sibling->nextSibling;
                            sibling->nextSibling = node;
                            node->prevSibling = sibling;
                            node->parent = parent;
                        }
                    }
                    top++;
                    stack[top] = node;
                    levelStack[top] = level;
                }
            }
        }
        fclose(f);
    } else {
        *j = initTreeJawa();
        *s = initTreeSumatera();
        *k = initTreeKalimantan();
        *u = initTreeSulawesi();
        *p = initTreePapua();

        f = fopen("datauniv.txt", "w");
        fprintf(f, "#JAWA\n"); simpanTreeKeFile(*j, f, 0);
        fprintf(f, "#SUMATERA\n"); simpanTreeKeFile(*s, f, 0);
        fprintf(f, "#KALIMANTAN\n"); simpanTreeKeFile(*k, f, 0);
        fprintf(f, "#SULAWESI\n"); simpanTreeKeFile(*u, f, 0);
        fprintf(f, "#PAPUA\n"); simpanTreeKeFile(*p, f, 0);
        fclose(f);
    }
}

void printTree(Address root, int level) {
    if (root != NULL) {
        for (int i = 0; i < level; i++) printf("  ");
        printf("- %s (Peserta: %d/%d)\n", root->namaUniv, root->jumlahPeserta, root->kapasitas);
        printTree(root->firstChild, level + 1);
        printTree(root->nextSibling, level);
    }
}

void showTree(Address root, int level) {
    if (root != NULL) {
        printf("- %s \n", root->namaUniv);
        showTree(root->firstChild, level + 1);
        showTree(root->nextSibling, level);
    }
}

Address findUniv(Address root, const char* target) {
    if (root == NULL) return NULL;
    if (strcmp(root->namaUniv, target) == 0) return root;

    Address found = findUniv(root->firstChild, target);
    if (found != NULL) return found;

    return findUniv(root->nextSibling, target);
}

Address daftarUniv(Address root, const char* target) {
    Address targetUniv = findUniv(root, target);
    if (targetUniv == NULL) {
        printf("Universitas tidak ditemukan.\n");
        return NULL;
    }

    if (targetUniv->jumlahPeserta < targetUniv->kapasitas) {
        targetUniv->jumlahPeserta++;
        printf("Kamu berhasil mendaftar di %s\n", targetUniv->namaUniv);
        return targetUniv;
    } else {
        printf("Maaf, %s penuh. Mencari alternatif...\n", targetUniv->namaUniv);
        Sleep(5000);
        rekomendasiAlternatif(root, target);
    }
}

void rekomendasiAlternatif(Address root, const char* target) {
    Address targetUniv = findUniv(root, target);
    if (targetUniv == NULL) {
        printf("Universitas tidak ditemukan.\n");
        return;
    }

    printf("\nBerikut alternatif di sekitarnya:\n", targetUniv->namaUniv);
    int adaRekomendasi = 0;

    // Cek Parent //
    Address parent = targetUniv->parent;
    if (parent != NULL && parent->jumlahPeserta < parent->kapasitas) {
        printf("- %s\n", parent->namaUniv);
        adaRekomendasi = 1;
    }

    // Cek Saudara Kiri //
    Address prev = targetUniv->prevSibling;
    while (prev != NULL) {
        if (prev->jumlahPeserta < prev->kapasitas) {
            printf("- %s \n", prev->namaUniv);
            adaRekomendasi = 1;
        }
        prev = prev->prevSibling;
    }

    // Cek Saudara Kanan //
    Address next = targetUniv->nextSibling;
    while (next != NULL) {
        if (next->jumlahPeserta < next->kapasitas) {
            printf("- %s \n", next->namaUniv);
            adaRekomendasi = 1;
        }
        next = next->nextSibling;
    }

    // Cek Anak //
    Address child = targetUniv->firstChild;
    while (child != NULL) {
        if (child->jumlahPeserta < child->kapasitas) {
            printf("- %s\n", child->namaUniv);
            adaRekomendasi = 1;
        }
        child = child->nextSibling;
    }

    // Semua penuh //
    if (!adaRekomendasi) {
        printf("Tidak ada universitas terdekat yang tersedia saat ini.\n");
    }
}

Address initTreeJawa() {
    Address unsoed = newNode("Universitas Jenderal Soedirman");
    Address unpad = newNode("Universitas Padjajaran");
    Address itb = newNode("Institut Teknologi Bandung");
    Address upi = newNode("Universitas Pendidikan Indonesia");
    Address ipb = newNode("Institut Pertanian Bogor");
    Address ui = newNode("Universitas Indonesia");
    Address upnvj = newNode("Universitas Pembangunan Nasional Veteran Jakarta");
    Address unj = newNode("Universitas Negeri Jakarta");
    Address untirta = newNode("Universitas Sultan Ageng Tirtayasa");
    Address undip = newNode("Universitas Diponegoro");
    Address uns = newNode("Universitas Sebelas Maret");
    Address ugm = newNode("Universitas Gadjah Mada");
    Address uny = newNode("Universitas Negeri Yogyakarta");
    Address ub = newNode("Universitas Brawijaya");
    Address its = newNode("Institut Teknologi Sepuluh November");
    Address unair = newNode("Universitas Airlangga");
    addChild(itb, upi);
    addChild(itb, unpad);
    addChild(itb, unsoed);
    addChild(upi, ipb);
    addChild(ipb, ui);
    addChild(ipb, unj);
    addChild(ui, upnvj);
    addChild(unj, untirta);
    addChild(unsoed, undip);
    addChild(unsoed, uns);
    addChild(unsoed, ugm);
    addChild(ugm, uny);
    addChild(uny, ub);
    addChild(uny, its);
    addChild(uny, unair);
    return itb;
}

Address initTreeSumatera() {
    Address itera = newNode("Institut Teknologi Sumatera");
    Address unila = newNode("Universitas Negeri Lampung");
    Address unsri = newNode("Universitas Sriwijaya");
    Address uinrf = newNode("Universitas Islam Negeri Raden Fatah");
    Address unja = newNode("Universitas Jambi");
    Address andalas = newNode("Universitas Negeri Andalas");
    Address unpadang = newNode("Universitas Negeri Padang");
    Address usu = newNode("Universitas Sumatera Utara");
    Address unimed = newNode("Universitas Negeri Medan");
    Address unsyia = newNode("Universitas Syiah Kuala");
    addChild(itera, unila);
    addChild(itera, unsri);
    addChild(unsri, uinrf);
    addChild(unsri, unja);
    addChild(unja, andalas);
    addChild(unja, unpadang);
    addChild(andalas, usu);
    addChild(andalas, unimed);
    addChild(andalas, unsyia);
    return itera;
}

Address initTreeKalimantan() {
    Address unlam = newNode("Universitas Lambung Mangkurat");
    Address utp = newNode("Universitas Tanjung Pura");
    Address up = newNode("Universitas Palangkaraya");
    Address itk = newNode("Institut Teknologi Kalimantan");
    Address umw = newNode("Universitas Mulawarman");
    Address uku = newNode("Universitas Kalimantan Utara");
    addChild(unlam, utp);
    addChild(unlam, up);
    addChild(unlam, itk);
    addChild(itk, umw);
    addChild(itk, uku);
    return unlam;
}

Address initTreeSulawesi() {
    Address untad = newNode("Universitas Tadulako");
    Address usb = newNode("Universitas Sulawesi Barat");
    Address unmak = newNode("Universitas Negeri Makassar");
    Address uinmak = newNode("Universitas Islam Negeri Makassar");
    Address ung = newNode("Universitas Negeri Gorontalo");
    Address samrat = newNode("Universitas Sam Ratulangi");
    Address unman = newNode("Universitas Negeri Manado");
    addChild(untad, usb);
    addChild(untad, ung);
    addChild(usb, unmak);
    addChild(usb, uinmak);
    addChild(ung, samrat);
    addChild(ung, unman);
    return untad;
}

Address initTreePapua() {
    Address polinef = newNode("Politeknik Negeri Fak-Fak");
    Address unipa = newNode("Universitas Papua");
    Address unira = newNode("Universitas Jayapura");
    Address pore = newNode("Politeknik Amamapare");
    addChild(polinef, unipa);
    addChild(polinef, unira);
    addChild(polinef, pore);
    return polinef;
}