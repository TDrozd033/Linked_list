#pragma once


//#ifndef _GLOBAL_H
//#define _GLOBAL_H

typedef struct
{
  int nKey;  // porownuje elementy
  int* p;  // tablica dwuelementowa

}ListInfo;

#define LISTINFO ListInfo
int compare( const void*, const void* );
void freeInfo( const void* );



//#endif _GLOBAL_H


/*
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdlib.h>
#include<stdio.h>



int main( int argc, char* argv[] )
{
  TreeItem* pRoot = NULL;
  FindAndInsert( 10, &pRoot );
  FindAndInsert( 2, &pRoot );
  FindAndInsert( 5, &pRoot );

  FindAndInsert( 14, &pRoot );
  FindAndInsert( 12, &pRoot );
  FindAndInsert( 18, &pRoot );

  FindAndInsert( 4, &pRoot );
  FindAndInsert( 9, &pRoot );
  FindAndInsert( 1, &pRoot );
  FindAndInsert( 10, &pRoot );


  const char* slowo1 = "ABC";
  const char* slowo2 = "ABD";
  const char* slowo3 = "ACA";
  const char* slowo4 = "ABD";


  TreeItem* Tree = NULL;
  */

  /*
  pRoot=FindInsert(10,pRoot);
  pRoot=FindInsert(2,pRoot);
  pRoot=FindInsert(5,pRoot);

  pRoot=FindInsert(14,pRoot); pRoot=FindInsert(12,pRoot); pRoot=FindInsert(8,pRoot);

  pRoot=FindInsert(4,pRoot); pRoot=FindInsert(9,pRoot); pRoot=FindInsert(1,pRoot);

  TreeItem* pRoot = TreeFinelyBalanced(15);
  printf("\n\n");
  */
/*
  preOrder( pRoot );
  printf( "\n\n" );
  inOrder( pRoot );
  //zwolnic pamiec!
  //FreeTree(&pRoot);
  pRoot = FreeTree( pRoot );
  printf( "\n\n" );
  return 0;
}


*/