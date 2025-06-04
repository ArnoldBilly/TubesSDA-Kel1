#include <stdio.h>
#include "hanif.h"
#include "STACK.H"
#include "SpNRSLL.H"

int main(){
    Peserta peserta;
    Stack stack;
    CreateEmpty(&stack);

    printf("=== APLIKASI PEMILIHAN PRODI ===\n");
    displayPemilihanProdi(&stack);

    printf("\nPemilihan prodi selesai. Berikut pilihan Anda:\n");
    printStack(stack);

    return 0;
}
