
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

ListItem* CreateList()  //Empty -  pusty element kreowany w funkcji tworz¹cej listê i usuwany w funkcji niszcz¹cej listê
{
  return (ListItem*) calloc( 1, sizeof(ListItem) );

}


int Insert( ListItem* pAfter, LISTINFO* pInfo )/*wsk do inf - pInfo */ // insert po elemencie wskazywanym przez pAfter,,,    dodaje element za wskazanym elementem,
{
  if( !pAfter )
  {
    return 0;
  }
  
  ListItem* newElement = (ListItem*)calloc( 1, sizeof(ListItem) );
  if( !newElement )
  {
    return 0;
  }
  newElement->pInfo = pInfo;// tworzy nowy element i ustawia wartosc jego pola na wartosc argumentu ktory byl przekazany do funkcji 
  newElement->pNext = pAfter->pNext;  // ustawiamy wsk nowego el na wsk elementu za tym nowym 
  pAfter->pNext = newElement;
  return 1;
}

LISTINFO* Remove( ListItem* pAfter )  // usuwa element za wskazanym elementem i zwraca jego zawartoœæ
{
  if( IsEmpty( pAfter ) )
  {
    return 0;
  }
  ListItem* doUsuniecia = pAfter->pNext;   // el do usuniecia 
  ListInfo* kolejny = doUsuniecia->pInfo; // zapisujemy zawartosc el
  pAfter->pNext = doUsuniecia->pNext;
  free( doUsuniecia );
  return kolejny;
}

/*
LISTINFO* Front( ListItem* pList )       // zwraca wsk do informacji pierwszego (jak top() w stosie)
// dostêp do pola pInfo struktury wskazywanej przez wskaŸnik pNext elementu pList.

// zwraca zawartoœæ pierwszego elementu na liœcie
{
  if( !IsEmpty( pList ) )
  {
    return pList->pNext->pInfo;
  }
  printf( "Stack overflow\n" );
  return 0;
}
*/
LISTINFO* Front( ListItem* pList )       // zwraca wsk do informacji pierwszego (jak top() w stosie)
// dostêp do pola pInfo struktury wskazywanej przez wskaŸnik pNext elementu pList.

// zwraca zawartoœæ pierwszego elementu na liœcie
{
  return (!IsEmpty( pList ) )? pList->pNext->pInfo : 0;
}




int IsEmpty( ListItem* pList )     // 1 pusta,  0 -nie pusta  - nie uzywac if!    //  sprawdza, czy lista jest pusta,
{
  /*
   if (pList->pNext == NULL) {
    return 1;  // lista jest pusta
  } else {
    return 0;  // lista nie jest pusta
  }*/
  return !( pList && pList->pNext );
}


void      ClearList( ListItem* pList, void( __cdecl* freemem )( const void* ) )  /* pointer to the function of void type with one parameter const void*  */
//usuwa wszystkie elementy z listy oraz zwalnia pamiêæ
 {
  if( !( pList ) || freemem == NULL )
  {
    printf( "Lista pusta lub nie ma funkcji do czyszczenia\n" );
    return;
  }
  while( !IsEmpty( pList ) && freemem != NULL )
  {
    freemem( Remove( pList ) );
  }
}



void      RemoveList( ListItem** pList, void( __cdecl* freemem )( const void* ) )/* pointer to the function of void type with one parameter const void*  */
//usuwa ca³¹ listê oraz zwalnia pamiêæ
{
 
    if( !pList || !(*pList) ) 
    {
      printf( "Lista nie istnieje \n\n" );
      return;
    }
    ClearList( *pList, freemem );
    free( *pList );
    *pList = NULL;
  
}
// after removing, set list as NULL


void SortList( ListItem* pList, int( __cdecl* comp )( const void*, const void* ) )
//sortuje elementy na liœcie przy u¿yciu  funkcji 
{
  if( comp == NULL ) 
  {
    printf( "funkcja nie przekazana do sortowania \n" );
    return;
  }
  ListItem* pFirst = pList;   // pfirst -  pierwszy element, od którego zaczyna siê  wyszukiwanie

  // iterujemy po ka¿dym elemencie zaczynamy  od 1 koñca listy
  while( !IsEmpty( pFirst ) )
  {
    ListItem* pMin = pFirst;
    ListItem* pCurr = pFirst->pNext;

    // iterujemy po reszcie elementow listy i porównujemy wartoœci z pMin
    while( !IsEmpty( pCurr ) )//// is empty
    {
      // Jeœli wartoœæ  pCurr jest mniejsza ni¿ wartoœæ elementu pMin
      // to pMin bedzie wskazywal na pCurr
      if( compare( pMin->pNext->pInfo, pCurr->pNext->pInfo ) == 1 )
      {
        pMin = pCurr;
      }
      pCurr = pCurr->pNext;
    }

    // Jeœli najmniejszy element nie jest 1 na liœcie to zamieniamy jego pozycje z pierwsszym el
    if( pMin != pFirst )
    {
      pCurr = pMin->pNext->pNext;  // pcurr - wskazuje na el nastepujacy po pmin
      pMin->pNext->pNext = pFirst->pNext; // wskaznik na nastepny el pmin 
      pFirst->pNext = pMin->pNext; // wskaznik na nastepny el pierwszego elementu
      pMin->pNext = pCurr;  // wskaznik na nastepny el pmin
    }
    // przechodzimy do kolejnego elementu 
    pFirst = pFirst->pNext;
  }
}


ListItem* Find( ListItem* pList, const void* pItem, ListItem** pPrev, int( __cdecl* compare )( const void*, const void* ) )/*ptr to info to find - const void* *//*wsk na poprzednigo do znalezionego*/
/* pointer to the function with two parameters const void* and returned int value */
// znajduje element na liœcie o okreœlonej wartoœci i zwraca wskaŸnik do niego, a tak¿e ustawia wskaŸnik pPrev na element poprzedzaj¹cy.
{
  if(  compare == NULL )
  {
    return NULL;
  }

  // inicjacja pPrev do pierwszego elementu listy
  *pPrev = pList;
  // przeszukujemy liste szukamy elementu 
  while( !IsEmpty( *pPrev ) )
  {
    // jeœli znaleŸliœmy element, zwracamy  wskaŸnik na ten element
    if( ( compare( pItem, ( *pPrev )->pNext->pInfo ) ) == 0 )
    {
      return ( *pPrev )->pNext;
    }
    // przesuwamy pprev na nastepny el
    *pPrev = ( *pPrev )->pNext;
  }
  // zwracamy null jesli  nie znalezlismy 
  return *pPrev = NULL;
}










/*
struktura ma 2 pola
pierwsze pole ->  pole  przechowujace wartosc  
2 pole -> pole ktore wskazuje na nastepny element liksty 
*/

// dodawanie elementu 
/* mamy 2 elementy x i z i chcemy dodac element y  pomiedzy tamte 2
 1) tworze nowa zmienna ze wskaznikiem na nastepny element
 2) ten wskaznik na nastepny element = nowy element utworzony ktory chce dodac( nowa zmienna)
3)  wskaznik na nastepny element od tego nowego co chcemy dodac  = element utworzony w 1 kroku 
( dzieki temu element ktory byl nastepny stal sie nastepnym od nastepnego czyli tak jakby z drugiego stal sie trzecim w kolejce)




 
// usuwanie elementu 
 tworze nowy wskaznik tymczasowy ( listItem* temp=) i przypisuje do niego lista->next->next ( czyli element nastepny nastepny)
 zwalniam i usuwam element current-> next ( czyli nastepny)
 przypisuje do current -> next  = temp; (czyli teraz ten 3 element w kolejce jest na drugim miejscu, 
 zajal miejsce tego usunietego, ten pierwszy wskazuje na trzeci a nie na drugi )

 */











