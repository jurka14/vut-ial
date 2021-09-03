
/* c206.c **********************************************************}
{* Téma: Dvousmìrnì vázaný lineární seznam
**
**                   Návrh a referenèní implementace: Bohuslav Køena, øíjen 2001
**                            Pøepracované do jazyka C: Martin Tuèek, øíjen 2004
**                                            Úpravy: Kamil Jeøábek, záøí 2019
**
** Implementujte abstraktní datový typ dvousmìrnì vázaný lineární seznam.
** Užiteèným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typù a funkcí od jmen u jednosmìrnì vázaného lineárního
** seznamu). Definici konstant a typù naleznete v hlavièkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ
** obousmìrnì vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu pøed prvním použitím,
**      DLDisposeList ... zrušení všech prvkù seznamu,
**      DLInsertFirst ... vložení prvku na zaèátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek pøed aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek pøed aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... pøepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na pøedchozí prvek seznamu,
**      DLActive ........ zjišuje aktivitu seznamu.
**
** Pøi implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto pøíkladu, není-li u funkce
** explicitnì uvedeno nìco jiného.
**
** Nemusíte ošetøovat situaci, kdy místo legálního ukazatele na seznam
** pøedá nìkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnì komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornìní na to, že došlo k chybì.
** Tato funkce bude volána z nìkterých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální promìnná -- pøíznak ošetøení chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L pøed jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad již inicializovaným
** seznamem, a proto tuto možnost neošetøujte. Vždy pøedpokládejte,
** že neinicializované promìnné mají nedefinovanou hodnotu.
**/
    L->Act = NULL;
    L->Last = NULL;
    L->First = NULL;
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektnì
** uvolnìny voláním operace free.
**/
    struct tDLElem *elemPtr;

    while(L->First != NULL)
    {

        elemPtr = L->First;
        L->First = L->First->rptr;
        free(elemPtr);
    }

    L->Act = NULL;
    L->Last = NULL;
    L->First = NULL;
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na zaèátek seznamu L.
** V pøípadì, že není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/

	struct tDLElem *newElemPtr = malloc(sizeof(struct tDLElem));
	if(newElemPtr == NULL)
    {
        DLError();
        return;
    }
    newElemPtr->data = val;
    newElemPtr->rptr = L->First;
    newElemPtr->lptr = NULL;
    if (L->First != NULL)
    {
        L->First->lptr = newElemPtr;
    }
    else
    {
        L->Last = newElemPtr;
    }

    L->First = newElemPtr;
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V pøípadì, že není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/

	struct tDLElem *newElemPtr = malloc(sizeof(struct tDLElem));
	if(newElemPtr == NULL)
    {
        DLError();
        return;
    }
    newElemPtr->data = val;
    newElemPtr->lptr = L->Last;
    newElemPtr->rptr = NULL;
    if (L->Last != NULL)
    {
        L->Last->rptr = newElemPtr;
    }
    else
    {
        L->First = newElemPtr;
    }

    L->Last = newElemPtr;
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->First;
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/
	L->Act = L->Last;
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
    if(L->First == NULL)
    {
        DLError();
        return;
    }

    *val = L->First->data;
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
    if(L->Last == NULL)
    {
        DLError();
        return;
    }

    *val = L->Last->data;
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/

    struct tDLElem *elemPtr;
    if(L->First != NULL)
    {
        elemPtr = L->First;
        if(L->Act == L->First)
        {
            L->Act = NULL;
        }
        if(L->First == L->Last)
        {
            L->First = NULL;
            L->Last = NULL;
        }
        else
        {
            L->First = L->First->rptr;
            L->First->lptr = NULL;
        }
        free(elemPtr);
    }
}

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/

    struct tDLElem *elemPtr;
    if(L->First != NULL)
    {
        elemPtr = L->Last;
        if(L->Act == L->Last)
        {
            L->Act = NULL;
        }
        if(L->First == L->Last)
        {
            L->First = NULL;
            L->Last = NULL;
        }
        else
        {
            L->Last = L->Last->lptr;
            L->Last->rptr = NULL;
        }
        free(elemPtr);
    }
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se nedìje.
**/

    if(L->Act != NULL)
    {
        if(L->Act->rptr!= NULL)
        {
            struct tDLElem *elemPtr;
            elemPtr = L->Act->rptr;
            L->Act->rptr = elemPtr->rptr;
            if(elemPtr == L->Last)
            {
                L->Last = L->Act;
            }
            else
            {
                elemPtr->rptr->lptr = L->Act;
            }
            free(elemPtr);
        }

    }
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek pøed aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se nedìje.
**/

    if(L->Act != NULL)
    {
        if(L->Act->lptr != NULL)
        {
            struct tDLElem *elemPtr;
            elemPtr = L->Act->lptr;
            L->Act->lptr = elemPtr->lptr;
            if(elemPtr == L->First)
            {
                L->First = L->Act;
            }
            else
            {
                elemPtr->lptr->rptr = L->Act;
            }
            free(elemPtr);
        }

    }
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, že není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/

    if(L->Act != NULL)
    {
        struct tDLElem *newElemPtr = malloc(sizeof(struct tDLElem));
        if(newElemPtr == NULL)
        {
            DLError();
            return;
        }

        newElemPtr->data = val;
        newElemPtr->rptr = L->Act->rptr;
        newElemPtr->lptr = L->Act;
        L->Act->rptr = newElemPtr;

        if(L->Act == L->Last)
        {
            L->Last = newElemPtr;
        }
        else
        {
            newElemPtr->rptr->lptr = newElemPtr;
        }
    }
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek pøed aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, že není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/

    if(L->Act != NULL)
    {
        struct tDLElem *newElemPtr = malloc(sizeof(struct tDLElem));
        if(newElemPtr == NULL)
        {
            DLError();
            return;
        }

        newElemPtr->data = val;
        newElemPtr->lptr = L->Act->lptr;
        newElemPtr->rptr = L->Act;
        L->Act->lptr = newElemPtr;

        if(L->Act == L->First)
        {
            L->First = newElemPtr;
        }
        else
        {
            newElemPtr->lptr->rptr = newElemPtr;
        }
    }
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/

    if(L->Act == NULL)
    {
        DLError();
        return;
    }

    *val = L->Act->data;
}

void DLActualize (tDLList *L, int val) {
/*
** Pøepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedìlá nic.
**/
    if(L->Act != NULL)
    {
        L->Act->data = val;
    }
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** Všimnìte si, že pøi aktivitì na posledním prvku se seznam stane neaktivním.
**/

    if(L->Act != NULL)
    {
        L->Act = L->Act->rptr;
    }
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na pøedchozí prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** Všimnìte si, že pøi aktivitì na prvním prvku se seznam stane neaktivním.
**/

    if(L->Act != NULL)
    {
        L->Act = L->Act->lptr;
    }
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním pøíkazem return.
**/

    return((int) L->Act);
}

/* Konec c206.c*/
