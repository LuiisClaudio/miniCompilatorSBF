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
  

  if ((myfp = fopen("/home/lucasferraco/inf1018/miniCompilatorSBF/Arquivos Fonte/Auxiliares/ex3/ex3.txt", "r")) == NULL)
  {
    perror ("nao conseguiu abrir arquivo!");
    exit(1);
  }
  //void geracod (FILE *f, void **code, funcp *entry);
  geracod(myfp, code, entry);
  printf("\nsaiu da geracod\n");
  //entry = (funcp)code;
  //printf("\natribuiu code a entry\n");
  i = (*entry)(4);
  printf("\ni = %d\n", i);
  printf("\nacabou\n");
  return 0;
}
