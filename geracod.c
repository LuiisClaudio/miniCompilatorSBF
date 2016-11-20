# miniCompilatorSBF
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "geracod.h"

#define TAMANHO_BYTES 1600

typedef union _code Code;
typedef struct _mem Memory;

union _code{
	int a[400]; //1600 bytes
	unsigned char source[1600];
};


struct _mem {
	int index; // proximo index livre de source
	unsigned char* finalcode; // array totalmente preenchida com o código
	int* finalcode_int;
	Code* code;
};

static Memory* start()
{
	int i;
	Memory* strct;
	strct = (Memory *) malloc(sizeof(Memory));
	strct->index = 0;
	strct->finalcode = NULL;
	strct->code = (Code *) malloc(sizeof(Code));
	for(i = 0; i < TAMANHO_BYTES; i++ )
	{
		strct->code->source[i] = 0x90; //NOP
	}
	return strct;
}
/*typedef struct _stack Stack;
struct _stack {
	int height; //altura da pilha
	int alocheight; //altura alocada
	int locals[20]; //altura de cada varíavel local na pilha ( em relação a rbp )
};*/

static void error (const char *msg, int line) {
  fprintf(stderr, "erro %s na linha %d\n", msg, line);
  exit(EXIT_FAILURE);
}

/** Inicializa uma pilha **/
/*static Stack* inicializa_pilha()
{
	Stack* p = (Stack *) malloc(sizeof(Stack));
	int i;
	for(i = 0; i < 20; i++)
	{
		p->locals[i] = 0;
	}
	p->height = 0;
	p->alocheight = 0;
	return p;
}*/

static void preenche_prologo(unsigned char * inicio)//, unsigned char* fim)
{
/*
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 14          	sub    $0x14,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx
*/
	unsigned char in[4];
	//unsigned char fi[2];
	
	in[0] = 0x55;
	in[1] = 0x48;
	in[2] = 0x89;
	in[3] = 0xE5;
	
	//fi[0] = 0xC9;
	//fi[1] = 0xC3;
	
	strcpy((char *)inicio, (char *)in);
	//strcpy((char *)fim, (char *)fi);
}


static void insere(Memory* block, unsigned char* codigo, int size)
{
	int i;
	if(block->index < TAMANHO_BYTES)
	{
		for(i = 0; i < size; i++)
		{
			block->code->source[block->index] = codigo[i];
			block->index++;
		}

	}
	else
	{
		printf("Estouro de block!! at insere()\n");
		exit(-1);
	}

}

void make_ret(Memory* block)
{
	unsigned char ret[15] = {0xb8, 0x01, 0x00, 0x00, 0x00, 0x83, 0xfb, 0x00, 0x74, 0x00, 0x48, 0x89, 0xec, 0x5d, 0xc3};
	insere(block, ret, 15);
	return;
/*
d:	b8 01 00 00 00       	mov    $0x1,%eax
  12:	83 fb 00             	cmp    $0x0,%ebx
  15:	74 00                	je     17 <FIM>

0000000000000017 <FIM>:
  17:	48 89 ec             	mov    %rbp,%rsp
  1a:	5d                   	pop    %rbp
  1b:	c3                   	retq
*/	
}

void read_SBF(FILE *myfp, Memory *block)
{
  int line = 1;
  int  c;
		
  while ((c = fgetc(myfp)) != EOF) {
    switch (c) {
      case 'f': { /* function */
        char c0;
        if (fscanf(myfp, "unction%c", &c0) != 1)
          error("comando invalido", line);
        printf("function\n");
        
        break;
      }
      case 'e': { /* end */
        char c0;
        if (fscanf(myfp, "nd%c", &c0) != 1)
          error("comando invalido", line);
        printf("end\n");
        break;
      }
      case 'r': {  /* retorno */
        int idx0, idx1;
        char var0, var1;
        if (fscanf(myfp, "et? %c%d %c%d", &var0, &idx0, &var1, &idx1) != 4) 
          error("comando invalido", line);
        printf("ret? %c%d %c%d\n", var0, idx0, var1, idx1);
        make_ret(block);
        break;
      }
      case 'v': {  /* atribuicao */
        int idx0;
        char var0 = c, c0;
        if (fscanf(myfp, "%d = %c",&idx0, &c0) != 2)
          error("comando invalido",line);

        if (c0 == 'c') { /* call */
          int f, idx1;
          char var1;
          if (fscanf(myfp, "all %d %c%d\n", &f, &var1, &idx1) != 3)
            error("comando invalido",line);
          printf("%c%d = call %d %c%d\n",var0, idx0, f, var1, idx1);
        }
        else { /* operação aritmética */
          int idx1, idx2;
          char var1 = c0, var2, op;
          if (fscanf(myfp, "%d %c %c%d", &idx1, &op, &var2, &idx2) != 4)
            error("comando invalido", line);
          printf("%c%d = %c%d %c %c%d\n",
                var0, idx0, var1, idx1, op, var2, idx2);
        }
        break;
      }
      default: error("comando desconhecido", line);
    }
    line ++;
    fscanf(myfp, " ");
  }
}

void debug(Memory* block)
{
	int i;
	for(i = 0; i < block->index; i++)
	{
		printf("%d : %x\n", i, block->code->source[i]);
	}
}

static void finaliza(Memory* block)
{
	int i;
	int *ptr;
	int code_intsize = ceil((block->index)/4.0);
	block->finalcode = (unsigned char*) malloc(sizeof(unsigned char) * block->index);
	block->finalcode_int = (int *) malloc(sizeof(int) * code_intsize);
	for(i = 0; i < block->index; i++)
	{
		block->finalcode[i] = block->code->source[i];
	}
	for(i = 0; i < code_intsize; i++)
	{
		ptr = (int*)(block->code->source + i*4);
		block->finalcode_int[i] = *(ptr);
	}
	free(block->code);
}

void geracod (FILE *f, void **code, funcp *entry)
{
	unsigned char prologo_inicio[4];
	Memory *block = start();
	preenche_prologo(prologo_inicio);
	insere(block, prologo_inicio, 4);
	read_SBF(f, block);
	debug(block);
	finaliza(block);
	code = block->finalcode;
	entry = (funcp)block->finalcode;
	
	return;
}

void liberacod (void *p);
