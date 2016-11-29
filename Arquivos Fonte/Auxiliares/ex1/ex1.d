
ex1.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <function>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 14          	sub    $0x14,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx
   d:	bb 00 00 00 00       	mov    $0x0,%ebx
  12:	b8 01 00 00 00       	mov    $0x1,%eax
  17:	83 fb 00             	cmp    $0x0,%ebx
  1a:	75 05                	jne    21 <FIM>
  1c:	48 89 ec             	mov    %rbp,%rsp
  1f:	5d                   	pop    %rbp
  20:	c3                   	retq   

0000000000000021 <FIM>:
  21:	48 89 ec             	mov    %rbp,%rsp
  24:	5d                   	pop    %rbp
  25:	c3                   	retq   
