/*File body untuk ADT Queue*/
//Dibuat tanggal 28-3-2013

#include "queue.h"
#include "SpNRSLL.H"
#include "malloc.h"

/*Membuat sebuah queue baru dengan Front dan Rear NULL*/
void CreateQueue (Queue *Q)
{
    CreateQueueList(&Q->L);
}


/*Memeriksa apakah queue kosong */
boolean is_Empty (Queue Q)
{
	 return QueueListEmpty(Q.L);
}

/*Memeriksa apakah queue penuh */
boolean is_Full (Queue Q)
{
	queueAddress p = (queueAddress)malloc(sizeof(QueueElmtlist));
	if (p== NULL){
		free(p);
		return true;
	}
	free(p);
	return false;
}

/*Melekukan insertion pada queue*/
void EnQueue (Queue *Q, QueueInfo X)
{
	QueueInsVLast(&Q->L, X);
}
    

/*Melakukan deletion pada queue*/
void deQueue (Queue *Q, QueueInfo *X){	
	if (!is_Empty(*Q)) {
        QueueDelFirst(&Q->L, X);
	}
}

void printQueue (Queue *Q)
{
	QueuePrintInfo(Q->L);
}