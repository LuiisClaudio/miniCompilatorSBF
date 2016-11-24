#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "geracod.h"

#define TAMANHO_BYTES 1600
//block->code->source[]

void geracod (FILE *f, void **code, funcp *entry)
{
    unsigned char prologo_inicio[13];
    
    Memory *block = start();
    preenche_prologo(prologo_inicio);
    insere(block, prologo_inicio, 13);
    read_SBF(f, block);
    debug(block);
    
    *code = block->source;
    entry = (funcp)code;
    
    return;
}

void liberacod(void* p)
{
    unsigned char* freeme = (unsigned char*) p;
    free(freeme);
}

typedef struct _mem Memory;

struct _mem
{
    int index; // proximo indice livre de source
    unsigned char *source;
};

static Memory* start()
{
    int i;
    Memory* strct;
    
    strct = (Memory *) malloc(sizeof(Memory));
    if (strct == NULL)
    {
        printf("Erro ao alocar memoria para o codigo");
        exit(1);
    }
    
    strct->index = 0;
    strct->source = (unsigned char *) malloc(sizeof(unsigned char)*TAMANHO_BYTES);
    for(i = 0; i < TAMANHO_BYTES; i++ )
    {
        strct->source[i] = 0x90; //NOP
    }
    
    return strct;
}

/*typedef struct _stack Stack;
 struct _stack {
	int height; //altura da pilha
	int alocheight; //altura alocada
	int locals[20]; //altura de cada varíavel local na pilha ( em relação a rbp )
 };*/

static void error (const char *msg, int line)
{
    fprintf(stderr, "erro %s na linha %d\n", msg, line);
    exit(EXIT_FAILURE);
}

/** Inicializa uma pilha **/
/*static Stack* inicializa_pilha()
 {
	Stack* p = (Stack *) malloc(sizeof(Stack));
	int i;16:	45 01 e5             	add    %r12d,%r13d
	for(i = 0; i < 20; i++)
	{
 p->locals[i] = 0;
	}
	p->height = 0;
	p->alocheight = 0;
	return p;
 }*/

static void preenche_prologo(unsigned char * inicio)
{
    /*
     0:	55                   	push   %rbp
     1:	48 89 e5             	mov    %rsp,%rbp
     4:	48 83 ec 32          	sub    $0x32,%rsp
     8:	bb 00 00 00 00       	mov    $0x0,%ebx
     */
    unsigned char in[13];
    
    printf("\n\tEntrei no PREENCHE PROLOGO\n");
    
    in[0] = 0x55;
    in[1] = 0x48;
    in[2] = 0x89;
    in[3] = 0xE5;
    in[4] = 0x48;
    in[5] = 0x83;
    in[6] = 0xec;
    in[7] = 0x32;
    in[8] = 0xbb;
    in[9] = 0x00;
    in[10] = 0x00;
    in[11] = 0x00;
    in[12] = 0x00;
    
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
            block->source[block->index] = codigo[i];
            block->index++;
            //printf("Index: %d", block->index);
        }
        
    }
    else
    {
        printf("Estouro de block!! at insere()\n");
        exit(-1);
    }
    
}

void make_ret(Memory* block, char tipoVarpc0, int varpc0, char tipoVarpc1, int varpc1)
{
    printf("\n\tEntrei no MAKE RET\n");
    
    //movl teste, %ebx
    switch(tipoVarpc0)
    {
        case 'v':
        {
            /*
             a9:	8b 5d fc             	mov    -0x4(%rbp),%ebx
             ac:	8b 5d f8             	mov    -0x8(%rbp),%ebx
             af:	8b 5d f4             	mov    -0xc(%rbp),%ebx
             */
            block->source[block->index] = 0x8b;
            block->source[block->index + 1] = 0x5d;
            block->source[block->index + 2] = 0xfc - (varpc0*4);
            block->index = block->index + 3;
            break;
            
        }
        case 'p':
        {
            /*
             a9:	89 fb                	mov    %edi,%ebx
             */
            block->source[block->index] = 0x89;
            block->source[block->index + 1] = 0xfb;
            block->index = block->index + 2;
            break;
        }
        case '$':
        {
            /*
             ab:	bb cc 06 06 00       	mov    $0x606cc,%ebx
             b0:	bb 15 25 00 00       	mov    $0x2515,%ebx
             */
            block->source[block->index] = 0xbb;
            block->source[block->index + 1] = (char)varpc0;
            block->source[block->index + 2] = (char)varpc0 >> 8;
            block->source[block->index + 3] = (char)varpc0 >> 16;
            block->source[block->index + 4] = (char)varpc0 >> 24;
            block->index = block->index + 5;
            break;
        }
    }
    
    //movl retorno, %eax
    switch(tipoVarpc1)
    {
        case 'v':
        {
            /*
             c4:	8b 45 fc             	mov    -0x4(%rbp),%eax
             c7:	8b 45 f8             	mov    -0x8(%rbp),%eax
             ca:	8b 45 f4             	mov    -0xc(%rbp),%eax
             */
            block->source[block->index] = 0x8b;
            block->source[block->index + 1] = 0x45;
            block->source[block->index + 2] = 0xfc - (varpc1*4);
            block->index = block->index + 3;
            break;
        }
        case 'p':
        {
            /*
             d3:	89 f8                	mov    %edi,%eax
             */
            block->source[block->index] = 0x89;
            block->source[block->index + 1] = 0xf8;
            block->index = block->index + 2;
            break;
        }
        case '$':
        {
            /*
             d5:	b8 74 0f 00 00       	mov    $0xf74,%eax
             da:	b8 bf e8 90 00       	mov    $0x90e8bf,%eax
             */
            block->source[block->index] = 0xb8;
            block->source[block->index + 1] = (char)varpc1;
            block->source[block->index + 2] = (char)varpc1 >> 8;
            block->source[block->index + 3] = (char)varpc1 >> 16;
            block->source[block->index + 4] = (char)varpc1 >> 24;
            block->index = block->index + 5;
            break;
        }
    }
    
    //faz o teste e retorna
    /*
     df:	83 fb 00             	cmp    $0x0,%ebx
     e2:	74 00                	je     e4 <FIM>
     2a:	b8 00 00 00 00       	mov    $0x0,%eax
     */
    block->source[block->index] = 0x83;
    block->source[block->index + 1] = 0xfb;
    block->source[block->index + 2] = 0x00;
    block->source[block->index + 3] = 0x74;
    block->source[block->index + 4] = 0x05; // porque é 0x05 e não 0x00 ?
    
    block->source[block->index + 5] = 0xb8;
    block->source[block->index + 6] = 0x00;
    block->source[block->index + 7] = 0x00;
    block->source[block->index + 8] = 0x00;
    block->source[block->index + 9] = 0x00;
    
    /*
     00000000000000e4 <FIM>:
     e4:	48 89 ec             	mov    %rbp,%rsp
     e7:	5d                   	pop    %rbp
     e8:	c3                   	retq
     */
    block->source[block->index + 10] = 0x48;
    block->source[block->index + 11] = 0x89;
    block->source[block->index + 12] = 0xec;
    block->source[block->index + 13] = 0x5d;
    block->source[block->index + 14] = 0xc3;
    
    block->index = block->index + 15;
}


void makeOpVarLocal(Memory *block, int varpc0, char tipoVarpc1, int varpc1, char op, char tipoVarpc2, int varpc2)
{
    printf("\nEntrei no MAKE OP VAR LOCAL\n");
    //reg = const + const
    //reg = const + p
    //reg = const + reg
    
    switch(tipoVarpc1)
    {
        case 'v':
        {
            printf("\n\t\tEntrei no MAKE OP VAR LOCAL: Var1: Case v%d\n", varpc1);
            
            /*
             1f:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
             23:	44 8b 65 f8          	mov    -0x8(%rbp),%r12d
             27:	44 8b 65 f4          	mov    -0xc(%rbp),%r12d
             2b:	44 8b 65 f0          	mov    -0x10(%rbp),%r12d
             2f:	44 8b 65 ec          	mov    -0x14(%rbp),%r12d
             */
            block->source[block->index] = 0x44;
            block->source[block->index + 1] = 0x8b;
            block->source[block->index + 2] = 0x65;
            block->source[block->index + 3] = 0xfc - (varpc1*4);
            block->index = block->index + 4;
            break;
        }
        case 'p':
        {
            printf("\n\t\tEntrei no MAKE OP VAR LOCAL: Var1: Case p0\n");
            
            /* 
             75:	41 89 fc             	mov    %edi,%r12d
             */
            block->source[block->index] = 0x41;
            block->source[block->index + 1] = 0x89;
            block->source[block->index + 2] = 0xfc;
            block->index = block->index + 3;
            break;
        }
        case '$':
        {
            printf("\n\t\tEntrei no MAKE OP VAR LOCAL: Var1: Case $\n");
            
            /*
             d:	    41 bc 01 00 00 00    	mov    $0x1,%r12d
             13:	41 bc 02 00 00 00    	mov    $0x2,%r12d
             19:	41 bc 03 00 00 00    	mov    $0x3,%r12d
             */
            block->source[block->index] = 0x41;
            block->source[block->index + 1] = 0xbc;
            
            block->source[block->index + 2] = (char) varpc1;
            block->source[block->index + 3] = (char) varpc1 >> 8;
            block->source[block->index + 4] = (char) varpc1 >> 16;
            block->source[block->index + 5] = (char) varpc1 >> 24;
            
            block->index = block->index + 6;
            break;
        }
    }
    
    switch(tipoVarpc2)
    {
        case 'v':
        {
            printf("\n\t\tEntrei no MAKE OP VAR LOCAL: Var2: Case v%d\n", varpc2);
            
            /*
             48:	44 8b 6d fc          	mov    -0x4(%rbp),%r13d
             4c:	44 8b 6d f8          	mov    -0x8(%rbp),%r13d
             50:	44 8b 6d f4          	mov    -0xc(%rbp),%r13d
             */
            block->source[block->index] = 0x44;
            block->source[block->index + 1] = 0x8b;
            block->source[block->index + 2] = 0x6d;
            block->source[block->index + 3] = 0xfc - (varpc2*4);
            block->index = block->index + 4;
            break;
        }
        case 'p':
        {
            printf("\n\t\tEntrei no MAKE OP VAR LOCAL: Var2: Case p0\n");
            
            /*
             33:	41 89 fd             	mov    %edi,%r13d
             */
            block->source[block->index] = 0x41;
            block->source[block->index + 1] = 0x89;
            block->source[block->index + 2] = 0xfd;
            block->index = block->index + 3;
            break;
        }
        case '$':
        {
            printf("\n\t\tEntrei no MAKE OP VAR LOCAL: Var2: Case $%d\n", varpc2);
            
            /*
             36:	41 bd 01 00 00 00    	mov    $0x1,%r13d
             3c:	41 bd 02 00 00 00    	mov    $0x2,%r13d
             42:	41 bd 03 00 00 00    	mov    $0x3,%r13d
             */
            block->source[block->index] = 0x41;
            block->source[block->index + 1] = 0xbd;
            block->source[block->index + 2] = (char) varpc2 ;
            block->source[block->index + 3] = (char) varpc2 >> 8;
            block->source[block->index + 4] = (char) varpc2 >> 16;
            block->source[block->index + 5] = (char) varpc2 >> 24;
            block->index = block->index + 6;
            break;
            
        }
    }
    
    switch(op)
    {
            /*
             54:	45 01 e5             	add    %r12d,%r13d
             57:	45 29 e5             	sub    %r12d,%r13d
             5a:	45 0f af ec          	imul   %r12d,%r13d
             
             9c:	45 01 ec             	add    %r13d,%r12d
             9f:	45 29 ec             	sub    %r13d,%r12d
             a2:	45 0f af e5          	imul   %r13d,%r12d
             */
        case '+':
        {
            block->source[block->index] = 0x45;
            block->source[block->index + 1] = 0x01;
            block->source[block->index + 2] = 0xec;
            block->index = block->index + 3;
            printf("\n\t\t OPERACAO de ++++\n");
            
            break;
        }
        case '-':
        {
            block->source[block->index] = 0x45;
            block->source[block->index + 1] = 0x29;
            block->source[block->index + 2] = 0xec;
            block->index = block->index + 3;
            printf("\n\t\t OPERACAO de ----\n");
            break;
        }
        case '*':
        {
            block->source[block->index] = 0x45;
            block->source[block->index + 1] = 0x0f;
            block->source[block->index + 2] = 0xaf;
            block->source[block->index + 3] = 0xe5;
            block->index = block->index + 4;
            printf("\n\t\t OPERACAO de ****\n");
            break;
        }
    }
    
    /*
     10:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)
     14:	44 89 65 f8          	mov    %r12d,-0x8(%rbp)
     18:	44 89 65 f4          	mov    %r12d,-0xc(%rbp)
     1c:	44 89 65 f0          	mov    %r12d,-0x10(%rbp)
     20:	44 89 65 ec          	mov    %r12d,-0x14(%rbp)
     
     bd:	44 89 6d fc          	mov    %r13d,-0x4(%rbp)
     */
    
    printf("\nEntrei no MAKE OP VAR LOCAL: 	ATRIBUI A OPERAÇÃO PARA A VARIAVEL LOCAL\n");
    
    block->source[block->index] = 0x44;
    block->source[block->index + 1] = 0x89;
    block->source[block->index + 2] = 0x65;
    block->source[block->index + 3] = 0xfc - (varpc0*4);
    block->index = block->index + 4;
    
}

void read_SBF(FILE *myfp, Memory *block)
{
    char c0, op, var0, var1, var2;
    int c, f, idx0, idx1, idx2;
    int line = 1;

    while ((c = fgetc(myfp)) != EOF)
    {
        switch (c)
        {
            case 'f':   /* function */
            {
                if (fscanf(myfp, "unction%c", &c0) != 1)
                    error("comando invalido", line);
                
                printf("function\n");
                break;
            }
            case 'e':   /* end */
            {
                if (fscanf(myfp, "nd%c", &c0) != 1)
                    error("comando invalido", line);
                
                printf("end\n");
                break;
            }
            case 'r':    /* retorno */
            {
                if (fscanf(myfp, "et? %c%d %c%d", &var0, &idx0, &var1, &idx1) != 4)
                    error("comando invalido", line);
                
                printf("ret? %c%d %c%d\n", var0, idx0, var1, idx1);
                
                make_ret(block, var0, idx0, var1, idx1);
                break;
            }
            case 'v':   /* atribuicao */
            {
                var0 = c;
                
                if (fscanf(myfp, "%d = %c",&idx0, &c0) != 2)
                    error("comando invalido",line);
                
                if (c0 == 'c')  /* call */
                {
                    if (fscanf(myfp, "all %d %c%d\n", &f, &var1, &idx1) != 3)
                        error("comando invalido",line);
                    printf("%c%d = call %d %c%d\n",var0, idx0, f, var1, idx1);
                }
                else    /* operação aritmética */
                {
                    var1 = c0;
                    
                    if (fscanf(myfp, "%d %c %c%d", &idx1, &op, &var2, &idx2) != 4)
                        error("comando invalido", line);
                    
                    printf("%c%d = %c%d %c %c%d\n",
                           var0, idx0, var1, idx1, op, var2, idx2);
                    
                    makeOpVarLocal(block, idx0, var1, idx1, op, var2, idx2);
                }
                break;
            }
            default:
                error("comando desconhecido", line);
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
        printf("%d : %x\n", i, block->source[i]);
    }
}
