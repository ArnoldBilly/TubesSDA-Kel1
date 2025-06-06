/* File        : stack.cpp */
/* Deskripsi   : Body ADT stack yang diimplementasikan dgn linked list */
/* Dibuat oleh : Ade Chandra Nugraha*/

#include "STACK.H"
#include "SpNRSLL.H"
#include "malloc.h"

/**** Perubahan nilai komponen struktur ****/
void SetTop (Stack *S, Stack NewTop )
/* Memberi Nilai TOP yang baru dengan NewTop */
{
	*S = NewTop;
}

/*    PROTO TYPE    */
/**** Konstruktor/Kreator ****/
void CreateEmpty (Stack *S)
/* IS : S sembarang */
/* FS : Membuat sebuah stack S yang kosong */
/* Ciri stack kosong : TOP bernilai NULL */
{
	CreateList(&S->Top);
}

/**** Predikat untuk test keadaan KOLEKSI ****/
boolean IsEmpty (Stack S)
/* Mengirim true jika Stack Kosong */
{
	return ListEmpty(S.Top);
}


boolean stackFull(Stack S)
{
	address p;
	p = (address)malloc(sizeof(ElmtList));
	if (p == NULL){
		return true;
	}
	free(p);
	return false;
}
/**** Menambahkan sebuah elemen ke Stack ****/
void Push (Stack *S, infotype X)
/* Menambahkan X sebagai elemen stack S */
/* IS : S mungkin kosong */
/* FS : X menjadi TOP yang baru */
{
	if (stackFull(*S))
	{
		printf("Stack Penuh Gagal Push");
	}else{
		InsVFirst(&S->Top,X);	
	}
}

/**** Menghapus sebuah elemen Stack ****/
void Pop (Stack *S, infotype *X)
/* Menghapus X dari Stack S */
/* IS : S tidak mungkin kosong */
/* FS : X adalah nilai elemen TOP yang lama */
{
	if (IsEmpty(*S)){
		printf("Stack Kosong");
	}else{
	DelVFirst(&S->Top,X);
	}
}

