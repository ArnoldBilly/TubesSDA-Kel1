#include <stdio.h>
#include "hanif.h"

int main(){
    Peserta peserta;
    User user;
    displayBiodata(&peserta);
    addPeserta(&peserta,&user);
    return 0;
}