
ex1.o: formato do arquivo elf64-x86-64


Desmontagem da seção .text:

0000000000000000 <function>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 14          	sub    $0x14,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx
   d:	b8 01 00 00 00       	mov    $0x1,%eax
  12:	83 fb 00             	cmp    $0x0,%ebx
  15:	74 00                	je     17 <FIM>

0000000000000017 <FIM>:
  17:	48 89 ec             	mov    %rbp,%rsp
  1a:	5d                   	pop    %rbp
  1b:	c3                   	retq   
