#ifndef FARELL_H
#define FARELL_H

#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_EMAIL 100
#define MAX_PASSWORD 100
#define MAX_NAMA 50
#define MAX_NISN 10
#define MAX_STATUS 20

// Struktur data User (untuk akun)
typedef struct User {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
    struct User* next;
} User;

typedef struct dataPeserta {
    char nisn[MAX_NISN];
    char nama[MAX_NAMA];
    char status[MAX_STATUS];
    struct dataPeserta* next;
} dataPeserta;

void menuUtama(User** akunHead, Queue* antrean, dataPeserta** pesertaHead);
void prosesLogin(User* akunHead, Queue* antrean, dataPeserta** pesertaHead);
void menuAdmin(Queue* antrean, dataPeserta* pesertaHead);
void tambahAkun(User** head, const char* email, const char* password);
void simpanAkunKeFile(User* head);
void bacaAkunDariFile(User** head);
void registrasiAkun(User** head);
int loginAkun(User* head, char* email, char* password);
void isiBiodata(dataPeserta** pesertaHead, char* nisn);
void tambahPeserta(dataPeserta** head, dataPeserta* peserta);
dataPeserta* cariPeserta(dataPeserta* head, char* nisn);
void enqueuePeserta(Queue* Q, const char* nisn, dataPeserta* pesertaHead);
dataPeserta* dequeuePeserta(Queue* Q, dataPeserta* pesertaHead);
void lihatAntrian(Queue Q, dataPeserta* pesertaHead);
void konfirmasiAntrian(Queue* Q, dataPeserta* pesertaHead);

#endif