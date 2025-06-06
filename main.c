#include "farell.h"


int main() {
    User* akunHead = NULL;
    Queue antrean;
    CreateQueue(&antrean);
    dataPeserta* pesertaHead = NULL;

    bacaAkunDariFile(&akunHead);
    menuUtama(&akunHead, &antrean, &pesertaHead);

    return 0;
}