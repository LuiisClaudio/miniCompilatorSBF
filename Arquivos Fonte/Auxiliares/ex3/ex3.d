
ex3.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <ex3>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 20          	sub    $0x20,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx
   d:	b8 01 00 00 00       	mov    $0x1,%eax
  12:	83 ff 00             	cmp    $0x0,%edi
  15:	74 26                	je     3d <FIM>
  17:	b8 00 00 00 00       	mov    $0x0,%eax
  1c:	89 7d fc             	mov    %edi,-0x4(%rbp)
  1f:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  23:	41 83 ec 01          	sub    $0x1,%r12d
  27:	44 89 e7             	mov    %r12d,%edi
  2a:	e8 00 00 00 00       	callq  2f <ex3+0x2f>
  2f:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  33:	41 89 c5             	mov    %eax,%r13d
  36:	45 0f af e5          	imul   %r13d,%r12d
  3a:	44 89 e0             	mov    %r12d,%eax

000000000000003d <FIM>:
  3d:	48 89 ec             	mov    %rbp,%rsp
  40:	5d                   	pop    %rbp
  41:	c3                   	retq  
