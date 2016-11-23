
atr.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <atr>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 14          	sub    $0x14,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx
   
   d:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
  14:	c7 45 f8 02 00 00 00 	movl   $0x2,-0x8(%rbp)
  1b:	c7 45 f4 03 00 00 00 	movl   $0x3,-0xc(%rbp)
  22:	c7 45 f0 04 00 00 00 	movl   $0x4,-0x10(%rbp)
  29:	c7 45 ec 05 00 00 00 	movl   $0x5,-0x14(%rbp)
  
  30:	89 7d fc             	mov    %edi,-0x4(%rbp)
  33:	89 7d f8             	mov    %edi,-0x8(%rbp)
  36:	89 7d f4             	mov    %edi,-0xc(%rbp)

0000000000000039 <FIM>:
  39:	48 89 ec             	mov    %rbp,%rsp
  3c:	5d                   	pop    %rbp
  3d:	c3                   	retq   
