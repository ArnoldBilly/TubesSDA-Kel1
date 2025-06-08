#ifndef HANIF_H
#define HANIF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STACK.H"
#include "SpNRSLL.H"

typedef struct Peserta {
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
} Peserta;

typedef struct User User;

// typedef struct User{
// char email[7] ;
// char password[11] ;
// }User;

void displayBioPeserta(Peserta* Peserta);
void pilihProdi(Stack* S,Prodi prodi);
void hapusProdi(Stack* S);
void displayPemilihanProdi(Stack* stack);
void printStack(Stack S);

#endif