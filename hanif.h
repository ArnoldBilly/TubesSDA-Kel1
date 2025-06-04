#ifndef HANIF_H
#define HANIF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STACK.H"
#include "SpNRSLL.H"

typedef struct Peserta {
    char namaLengkap[100];
    char tanggalLahir[20];
    char nisn[15];      
} Peserta;


void pilihProdi(Stack* S,Prodi prodi);
void hapusProdi(Stack* S);
void displayPemilihanProdi(Stack* stack);
void printStack(Stack S);

#endif