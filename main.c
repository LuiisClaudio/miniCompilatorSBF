#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "geracod.h"
#include <math.h>

int main (void) {
  int i;
  void **code;
  FILE *myfp;
  funcp *entry;
  

  if ((myfp = fopen("//home//luis//tra2//ex2.txt", "r")) == NULL)
  {
    perror ("nao conseguiu abrir arquivo!");
    exit(1);
  }
  //void geracod (FILE *f, void **code, funcp *entry);
  geracod(myfp, code, entry);
  entry = (funcp)code;

  i = (*entry)(0);
  printf("\ni = %d\n", i);
  
  return 0;
}
