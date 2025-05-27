/*File body untuk ADT Queue*/
//Dibuat tanggal 28-3-2013

#include "queue_.h"
#include "SpNRSLL.H"
#include "malloc.h"

/*Membuat sebuah queue baru dengan Front dan Rear NULL*/
void CreateQueue (Queue *Q)
{
    CreateList(&Q->L);
}


/*Memeriksa apakah queue kosong */
boolean is_Empty (Queue Q)
{
	 return ListEmpty(Q.L);
}

/*Memeriksa apakah queue penuh */
boolean is_Full (Queue Q)
{
    address p;
	p = (address)malloc(sizeof(ElmtList));
	if (p== NULL){
		return true;
	}
	free(p);
	return false;
}

/*Melekukan insertion pada queue*/
void EnQueue (Queue *Q, infotype X)
{
	address p;
    p= Alokasi(X);
    if (p!=Nil){
        InsertLast(&Q->L, p);
    }
    
}

/*Melakukan deletion pada queue*/
void deQueue (Queue *Q, infotype *X)
{	address p;
	DelFirst(&Q->L,&p);
	*X = Info(p);
	DeAlokasi(p);
}

void printQueue (Queue *Q)
{
	PrintInfo(Q->L);
}
