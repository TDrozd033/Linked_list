#pragma once
//#ifndef _LIST_H
//#define _LIST_H
#include"global.h"

//define the structural type named ListItem
 // Fields: pInfo  wskaznik do typu zdefiniowanego przez uzytkownika - stala preprocesora LISTINFO
 //         pNext  wsk do nastepnego elementu na liscie  (tagListItem)

typedef struct  tagListItem
{
  LISTINFO* pInfo;
  tagListItem* pNext;
}ListItem;

ListItem* CreateList();
int       Insert( ListItem* pAfter, LISTINFO* pInfo ); /*wsk do inf - pInfo */  // insert po elemencie wskazywanym przez pAfter
LISTINFO* Remove( ListItem* pAfter );      // usun element po elemencie wsk przez pAfter

LISTINFO* Front( ListItem* pList );        // zwraca wsk do informacji pierwszego (jak top() w stosie)

int       IsEmpty( ListItem* pList );     // 1 pusta,  0 -nie pusta  - nie uzywac if!

void      ClearList( ListItem* pList, void( __cdecl* freemem )( const void* )); /* pointer to the function of void type with one parameter const void*  */ 
void      RemoveList( ListItem** pList, void( __cdecl* freemem )( const void* ) ); /* pointer to the function of void type with one parameter const void*  */ 
// after removing, set list as NULL

void      SortList( ListItem* pList, int( __cdecl* compare )( const void*, const void* ) );
  /* pointer to the function with two parameters const void* and returned int value */ 

ListItem* Find( ListItem* pList,const void* pItem, ListItem** pPrev, int( __cdecl* compare )( const void*, const void* ));

//#endif  _LIST_H




