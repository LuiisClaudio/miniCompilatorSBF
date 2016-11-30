#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "geracod.h"
#include <math.h>

void testeCode(void *code);

int main (void) {
  int i;
  void **code;
  FILE *myfp;
  funcp entry;
  

  if ((myfp = fopen("/home/lucasferraco/inf1018/miniCompilatorSBF/Arquivos Fonte/Auxiliares/ex4/ex4.txt", "r")) == NULL)
  {
    perror ("nao conseguiu abrir arquivo!");
    exit(1);
  }
  //void geracod (FILE *f, void **code, funcp *entry);
  geracod(myfp, code, &entry);
  printf("\ncode = %x\n", ((unsigned char *)*code)[0]);
  printf("\ncode = %x\n", ((unsigned char *)*code)[1]);
  printf("\ncode = %x\n", ((unsigned char *)*code)[2]);
  testeCode(code);
  i = (*entry)(3);
  printf("\ni = %d\n", i);

  liberacod(*code);
  printf("\ncode = %x\n", ((unsigned char *)*code)[0]);
  printf("\ncode = %x\n", ((unsigned char *)*code)[1]);
  printf("\ncode = %x\n", ((unsigned char *)*code)[2]);
  testeCode(*code);
  return 0;
}

void testeCode (void *code) {
	if(code == NULL)
		printf("CODE VAZIO");
	else
		printf("CODE NAO VAZIO");
}
