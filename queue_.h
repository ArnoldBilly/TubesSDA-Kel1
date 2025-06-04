/*File header untuk ADT Queue*/

#ifndef QUEUE_H
#define QUEUE_H
#include "boolean.h"
#define NBElement 10
#include "SpNRSLL.H"

typedef struct
{
    List L;
}Queue;


/*Membuat sebuah queue baru dengan Front dan Rear NULL*/
void CreateQueue (Queue *Q);

/*Memeriksa apakah queue kosong */
boolean is_Empty (Queue Q);

/*Memeriksa apakah queue penuh */
boolean is_Full (Queue Q);

/*Melekukan insertion pada queue*/
void EnQueue (Queue *Q, infotype X);

/*Melakukan deletion pada queue*/
void deQueue (Queue *Q, infotype *X);

void printQueue(Queue *Q);

#endif

