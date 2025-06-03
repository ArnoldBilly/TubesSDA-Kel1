#include "test.h"

Address newNode(const char* nama) {
    int kapasitas = rand() % 50 + 100;
    int jumlahpeserta = rand() % kapasitas;
    Address node = (Address)malloc(sizeof(TreeNode));
    strcpy(node->namaUniv, nama);
    node->kapasitas = kapasitas;
    node->jumlahPeserta = jumlahpeserta;
    node->firstChild = NULL;
    node->nextSibling = NULL;
    return node;
}

void addChild(Address parent, Address child) {
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    } else {
        Address temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
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
        printf("- %s\n", root->namaUniv);
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
        printf("Silahkan lanjut ke proses selanjutnya\n");
        return targetUniv;
    }

    Address nextbrother = targetUniv->nextSibling;
    while (nextbrother != NULL)
    {
        if (nextbrother->jumlahPeserta < nextbrother->kapasitas) {
            nextbrother->jumlahPeserta++;
            printf("Maaf, kampus %s penuh. Kamu dialihkan ke %s\n", targetUniv->namaUniv, nextbrother->namaUniv);
            printf("Silahkan lanjut ke proses selanjutnya\n");
            return nextbrother;
        }
        nextbrother = nextbrother->nextSibling;
    }
        
    Address child = targetUniv->firstChild;
    while (child != NULL) {
        if (child->jumlahPeserta < child->kapasitas) {
            child->jumlahPeserta++;
            printf("Maaf, kampus %s penuh. Kamu dialihkan ke %s\n", targetUniv->namaUniv, child->namaUniv);
            printf("Silahkan lanjut ke proses selanjutnya\n");
            return child;
        }
        child = child->nextSibling;
    }

    printf("Maaf, semua universitas di dekat %s sudah penuh\n", targetUniv->namaUniv);
    return NULL;
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
    addChild(unsoed, unpad);
    addChild(unsoed, undip);
    addChild(unpad, itb);
    addChild(unpad, upi);
    addChild(upi, ipb);
    addChild(upi, ui);
    addChild(ui, upnvj);
    addChild(ui, unj);
    addChild(unj, untirta);
    addChild(undip, uns);
    addChild(undip, ugm);
    addChild(undip, uny);
    addChild(uny, ub);
    addChild(uny, its);
    addChild(uny, unair);
    return unsoed;
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