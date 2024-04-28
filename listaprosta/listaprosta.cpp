

// operacje na liscie ktore przechowuja dane dowolnego typu 

// sortowanie oraz wyszukiwanie na liscie
// funkcja porownujaca, porownuje 2 elementy informacji uzytkownika

#include <stdio.h>
#include "list.h"
#include<time.h>
#include <stdlib.h>

void PrintList( ListItem* list );

ListInfo* Create( int pierwszy_element, int drugi_element);

int main()
{
  ListItem* pList = CreateList();		
  if( !IsEmpty( pList ) )
  {
    printf( "Error, blad 1\n" );
    return -8;
  }
  srand( ( unsigned int ) time( NULL ) );
 // dodać minimum 20 elementów z kluczami losowymi( < 50 ) ( dla indeksu 9 wstawić klucz 2000 )
  
  for( int i = 0; i < 20; i++ )												
  {
    int wynik = 0;
    if( i == 9 )
      wynik = 2000;
    else
      wynik = rand() % 50;

    ListInfo* pInfo = Create( wynik, i );	
    if( !pInfo )
    {
      printf( "Error, blad 2\n" );
      return -6;
    }
    if( !Insert( pList, pInfo ) )	
    {
      printf( "Blad podczas wstawiania!\n" );
      return -1;
    }
  }
  printf( "\nLista na poczatku: " ); 
  PrintList( pList ); // wypisujemy liste
  SortList( pList, compare );  // sortujemy liste
  printf( "\nLista po posortowaniu:\n" );												
  PrintList( pList );

  //wyszukać element z kluczem 2000,
  ListItem* pPrev = NULL;
  int temp = 20;
  LISTINFO* pSearchKey = Create( 2000, 9 );	
  if( !pSearchKey ) 
  {
    printf( "Blad numer 3\n" );
    return -5;
  }

 ListItem* pFind = Find( pList, pSearchKey, &pPrev, compare ); // szuka element i jesli on jest to go wypisuje 
 if( pFind )
 {
   printf( "%d\n", pFind->pInfo->nKey );
   if(pPrev->pInfo )
    printf( "%d\n", pPrev->pInfo->nKey );
 }
  freeInfo( pSearchKey );

  //wstawić przed znalezionym, element z kluczem 3000
  LISTINFO* pNewElement = Create( 3000, 69 );
  if( !Insert( pPrev, pNewElement ) )									
  {
    printf( "Blad podczas wstawiania!\n" );
    freeInfo( pNewElement );
    return -2;
  }
  // wypisujemy liste po wstawieniu 3000
  printf( "Po wstawieniu elementu z kluczem 3000:\n " );
  PrintList( pList );

  //usunąć element z kluczem 2000
  pSearchKey = Remove( pPrev->pNext );	//!!	
  if( !pSearchKey )
  {
    printf( "blad numer 6\n" );
    return -3;
  }
  printf( "Usuniecie el 2000:\n" );
  PrintList( pList );
  //zwolnić listę
  ClearList( pList, freeInfo );											

  //wstawić dwa elementy dowolne
 ListInfo* pInfo = Create( 345, 68 );
 if( !pInfo ) 
 {
   printf( "Blad numer 4\n" );
   return -4;
 }

  if( !Insert( pList, pInfo ) )
  {
    printf( "Blad podczas wstawiania!\n" );
    freeInfo( pInfo );
    return -3;
  }
  ListInfo* pInfo1  = Create( 777, 431 );
  if( !pInfo1 ) {
    printf( "Blad numer 5\n" );
    return -11;
  }
  if( !Insert( pList, pInfo1 ) )
  {
    perror( "Blad podczas wstawiania!\n" );
    freeInfo( pInfo1 );
    return -3;
  }
  //wypisujemy liste z dwoma el
  printf( "Lista z dwoma elementami:\n" );
  PrintList( pList );

  //Usunąć całą listę
  RemoveList( &pList, freeInfo );		
  // wydrukowac liste!!
  PrintList( pList );
  if( !pList )
  {
    printf( "Lista poprawnie usunieta\n" );
  }
  return 0;


}



ListInfo* Create( int pierwszy_element, int drugi_element )
{
  //tworzymy nowy el listy 
  ListInfo* temp = (ListInfo*)calloc( 1, sizeof(ListInfo) ); 
  if( temp == NULL ) // sprawdzamy zaalokowanie pamieci
  {
    return 0;
  }
  // tworzenie tablicy dla wartosci nowego elementu 
  temp->p = (int*)calloc( 2, sizeof(int) ); 
  if( !(temp->p)  )
  {
    return NULL;
  }
  // przypisanie klucza i wartosci do tego nowego elementu 
  temp->nKey = pierwszy_element;		
  temp->p[0] = drugi_element;

  return temp;// wsk na nowy el listy 

}




int compare( const void* Item1, const void* Item2 ) // porownuje 2 elementy 
{
  if( ( (LISTINFO*) Item1 )->nKey < ( (LISTINFO*) Item2 )->nKey )
  {
    return -1;
  }

  if( ( (LISTINFO*) Item1 )->nKey > ( (LISTINFO*) Item2 )->nKey )
  {
    return 1;
  }
  return 0;
}




void freeInfo( const void* Item ) // usuwanie
{
  free( ( (ListInfo*) Item )->p ); // zwalniamy pamiec dla tablicy wskaznikow
  free( (ListInfo*) Item ); // zwalniamy pamiec dla struktury 
 
}





void PrintList( ListItem* pList )
{
  printf( "\n" );
  for( int i = 1; !IsEmpty( pList ); i++, pList = pList->pNext )
  {
    printf( "Key %d = %d\n ", pList->pNext->pInfo->p[0], pList->pNext->pInfo->nKey );
  }
  printf( "\n" );
}


// uzywamy funkcji calloc - zeruje zaalakowana pamiec  - do createlist
// calloc - 
// w plikach naglowkowych mozna korzystac z pragma once



// lista prosta z głową - element pusty
// analogie do kalkulatora onp
// createlist





/// uwagi:
/*
używać pragma once
nie inkludować ekstra global h ( list h inkluduje global h wiec nie potrzebne) 
sprawdzac po kazdym czy sie powiodlo 
funkcja kreujaca element sparametryzowac 
w funkcji porownujacej elementy uzzywac stalej preprocesora listinfo 
przy zwalnianiu pamieci to nie ma sensu nulowac wskaznika ktory jest parametrem 
przy wydrukach elementow drukowac równiez zerowy element 
wiekszosc funkcji listy powinna sprawdzic czy lista jest ( funkcja isEmpty sprawdza czy lista jest) 
jezeli funkcja zwraca kod bledu to wtedy nie drukujemy zadnego komunikatu, a jesli funkcja typu void to trzeba komunikat 
przy sortowaniu sprawdzic czy jest funkcja 
przy find wskaznik pprev trzebu nulowac
\po znalezieniu elementu trzeba element wypisac (oba poprzedni tez)
w funkcji wyszukujace find nie deklarowac dodatkowego wskaznika pomocniczego ( bo mamy wskaznik pprev) 
w funkcji front - zrobic return wyrazenie pytajnikowe 


*/


// 3 wersja dzialajaca



