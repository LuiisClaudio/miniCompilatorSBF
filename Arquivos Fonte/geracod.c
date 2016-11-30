/*
 
 Lucas Ferraço de Freitas   Matrícula 1513012   Turma 3WA
 Luís Claudio C. Martins    Matrícula 1512946   Turma 3WA
 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "geracod.h"

#define VERDADEIRO 1
#define FALSO 0
#define TAMANHO_BYTES 1600
/*
 Cada funcao tem no minimo 3 linhas, 
 o arquivo tem no maximo 50 linhas,
 logo um arquivo tem no maximo 16 funcoes.
 */
#define NUM_MAX_FUNCOES 16

static void * vetEndIniFuncoes[NUM_MAX_FUNCOES];
static int  qtdFunc = 0;

/*
 ESTRUTURA ENCAPSULADA NO MODULO
 */
typedef struct _mem Memory;

struct _mem
{
    int index; // proximo indice livre de source
    unsigned char * source;
};
/*
 FIM DA ESTRUTURA ENCAPSULADA NO MODULO
 */


/*
 FUNCOES ENCAPSULADAS NO MODULO
 */
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

    for(i=0; i<NUM_MAX_FUNCOES; i++)
        vetEndIniFuncoes[i] = NULL;
    
    return strct;
}

static void error (const char *msg, int line)
{
    fprintf(stderr, "erro %s na linha %d\n", msg, line);
    exit(EXIT_FAILURE);
}

static void make_Init(Memory* block)
{
    /*
     0:	55                   	push   %rbp
     1:	48 89 e5             	mov    %rsp,%rbp
     4:	48 83 ec 20          	sub    $0x20,%rsp
     8:	bb 00 00 00 00       	mov    $0x0,%ebx
     */
    unsigned char in[13];
    int i;
    
    in[0] = 0x55;
    in[1] = 0x48;
    in[2] = 0x89;
    in[3] = 0xE5;
    in[4] = 0x48;
    in[5] = 0x83;
    in[6] = 0xec;
    in[7] = 0x20;
    in[8] = 0xbb;
    in[9] = 0x00;
    in[10] = 0x00;
    in[11] = 0x00;
    in[12] = 0x00;
    
    if(block->index < TAMANHO_BYTES)
    {
        qtdFunc++;
        vetEndIniFuncoes[qtdFunc-1] = &block->source[block->index];

        for(i = 0; i < 13; i++)
        {
            block->source[block->index] = in[i];
            block->index++;
        }
    }
    else
    {
        printf("Estouro de block!! at make_Init()\n");
        exit(-1);
    }
    
}

static void make_Ret(Memory* block, char tipoVarpc0, int varpc0, char tipoVarpc1, int varpc1)
{
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
     25:	83 fb 00             	cmp    $0x0,%ebx
     28:	75 05                	jne    2f <FIM>
     2a:	48 89 ec             	mov    %rbp,%rsp
     2d:	5d                   	pop    %rbp
     2e:	c3                   	retq
     */
    block->source[block->index] = 0x83;
    block->source[block->index + 1] = 0xfb;
    block->source[block->index + 2] = 0x00;
    block->source[block->index + 3] = 0x75;
    block->source[block->index + 4] = 0x05;
    block->source[block->index + 5] = 0x48;
    block->source[block->index + 6] = 0x89;
    block->source[block->index + 7] = 0xec;
    block->source[block->index + 8] = 0x5d;
    block->source[block->index + 9] = 0xc3;
    
    block->index = block->index + 10;
}

static void make_OpVarLocal(Memory *block, int varpc0, char tipoVarpc1, int varpc1, char op, char tipoVarpc2, int varpc2)
{
    //reg = const + const
    //reg = const + p
    //reg = const + reg
    
    switch(tipoVarpc1)
    {
        case 'v':
        {
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
            break;
        }
        case '-':
        {
            block->source[block->index] = 0x45;
            block->source[block->index + 1] = 0x29;
            block->source[block->index + 2] = 0xec;
            block->index = block->index + 3;
            break;
        }
        case '*':
        {
            block->source[block->index] = 0x45;
            block->source[block->index + 1] = 0x0f;
            block->source[block->index + 2] = 0xaf;
            block->source[block->index + 3] = 0xe5;
            block->index = block->index + 4;
            break;
        }
    }
    
    /*
     10:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)
     14:	44 89 65 f8          	mov    %r12d,-0x8(%rbp)
     18:	44 89 65 f4          	mov    %r12d,-0xc(%rbp)
     1c:	44 89 65 f0          	mov    %r12d,-0x10(%rbp)
     20:	44 89 65 ec          	mov    %r12d,-0x14(%rbp)
     */
    
    block->source[block->index] = 0x44;
    block->source[block->index + 1] = 0x89;
    block->source[block->index + 2] = 0x65;
    block->source[block->index + 3] = 0xfc - (varpc0*4);
    block->index = block->index + 4;
    
}

static void make_Call(Memory* block, int var0, void * enderecoFuncaoChamada, char tipoVarpc1, int varpc1)
{
    long difEntreEndFuncoes, enderecoFimCall;
    
    //movl parametro, %edi
    switch(tipoVarpc1)
    {
        case 'v':
        {
            /*
             a9:	8b 7d fc             	mov    -0x4(%rbp),%edi
             ac:	8b 7d f8             	mov    -0x8(%rbp),%edi
             af:	8b 7d f4             	mov    -0xc(%rbp),%edi
             */
            block->source[block->index] = 0x8b;
            block->source[block->index + 1] = 0x7d;
            block->source[block->index + 2] = 0xfc - (varpc1*4);
            block->index = block->index + 3;
            break;
            
        }
        case 'p':
        {
            /*
             a9:	89 ff                	mov    %edi,%edi
             */
            block->source[block->index] = 0x89;
            block->source[block->index + 1] = 0xff;
            block->index = block->index + 2;
            break;
        }
        case '$':
        {
            /*
             77:	bf cc 06 06 00       	mov    $0x606cc,%edi
             7c:	bf 15 25 00 00       	mov    $0x2515,%edi
             */
            block->source[block->index] = 0xbf;
            block->source[block->index + 1] = (char)varpc1;
            block->source[block->index + 2] = (char)varpc1 >> 8;
            block->source[block->index + 3] = (char)varpc1 >> 16;
            block->source[block->index + 4] = (char)varpc1 >> 24;
            block->index = block->index + 5;
            break;
        }
    }

    //call fn
    /*
     62:	e8 00 00 00 00       	callq  67 <f1+0x35>
     6d:	e8 00 00 00 00       	callq  72 <f1+0x40>
    */
    enderecoFimCall = (long)&block->source[block->index + 5];
    difEntreEndFuncoes = (long)enderecoFuncaoChamada - enderecoFimCall;
    
    block->source[block->index] = 0xe8;
    block->source[block->index + 1] = (difEntreEndFuncoes & 0xff);
    block->source[block->index + 2] = (difEntreEndFuncoes & 0xff00) >> 8;
    block->source[block->index + 3] = (difEntreEndFuncoes & 0xff0000) >> 16;
    block->source[block->index + 4] = (difEntreEndFuncoes & 0xff000000) >> 24;    
    block->index = block->index + 5;

    //movl %eax, var
    /*
     86:	89 45 fc             	mov    %eax,-0x4(%rbp)
     89:	89 45 f8             	mov    %eax,-0x8(%rbp)
     8c:	89 45 f4             	mov    %eax,-0xc(%rbp)
    */
    block->source[block->index] = 0x89;
    block->source[block->index + 1] = 0x45;
    block->source[block->index + 2] = 0xfc - (var0*4);
    block->index = block->index + 3;
}

static void make_End(Memory *block)
{
     /*
      2a:	48 89 ec             	mov    %rbp,%rsp
      2d:	5d                   	pop    %rbp
      2e:	c3                   	retq
      */
     block->source[block->index] = 0x48;
     block->source[block->index + 1] = 0x89;
     block->source[block->index + 2] = 0xec;
     block->source[block->index + 3] = 0x5d;
     block->source[block->index + 4] = 0xc3;
     block->index = block->index + 5;
}

static void read_SBF(FILE *myfp, Memory *block)
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
                
                make_Init(block);
                break;
            }
            case 'e':   /* end */
            {
                if (fscanf(myfp, "nd%c", &c0) != 1)
                    error("comando invalido", line);
                
                make_End(block);
                break;
            }
            case 'r':    /* retorno */
            {
                if (fscanf(myfp, "et? %c%d %c%d", &var0, &idx0, &var1, &idx1) != 4)
                    error("comando invalido", line);
                
                make_Ret(block, var0, idx0, var1, idx1);
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
                    
                    make_Call(block, idx0, vetEndIniFuncoes[f], var1, idx1);
                } 
                else    /* operação aritmética */
                {
                    var1 = c0;
                    
                    if (fscanf(myfp, "%d %c %c%d", &idx1, &op, &var2, &idx2) != 4)
                        error("comando invalido", line);
                    
                    make_OpVarLocal(block, idx0, var1, idx1, op, var2, idx2);
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

static void debug(Memory* block)
{
    int i;
    
    for(i = 0; i < block->index; i++)
    {
        printf("%x : %x\n", i, block->source[i]);
    }
}

/*
 FIM DAS FUNCOES ENCAPSULADAS NO MODULO
 */


/*
 FUNCOES EXTERNADAS PELO MODULO
 */
void geracod (FILE *f, void **code, funcp *entry)
{   
    Memory *block = start();
    read_SBF(f, block);

    /*
     Caso deseje verifivar o codigo de maquina gerado pelo modulo,
      descomente a linha de codigo abaixo para imprimir o codigo
      de maquina correspondente ao do arquivo de entrada.
     */
    //debug(block);

    *code = block->source;
    *entry = (funcp)vetEndIniFuncoes[qtdFunc-1];

    return;
}

void liberacod(void* p)
{
    unsigned char* codigo = (unsigned char*) p;
    free(codigo);
}

/*
 FIM DAS FUNCOES EXTERNADAS PELO MODULO
 */
