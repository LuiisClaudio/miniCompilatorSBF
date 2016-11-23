
ex3.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <ex3>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 10          	sub    $0x10,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx
   d:	b8 01 00 00 00       	mov    $0x1,%eax
  12:	83 ff 00             	cmp    $0x0,%edi
  15:	74 32                	je     49 <FIM>
  17:	b8 00 00 00 00       	mov    $0x0,%eax
  1c:	89 7d fc             	mov    %edi,-0x4(%rbp)
  1f:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  23:	41 83 ec 01          	sub    $0x1,%r12d
  27:	44 89 65 f8          	mov    %r12d,-0x8(%rbp)
  2b:	44 89 e7             	mov    %r12d,%edi
  2e:	e8 cd ff ff ff       	callq  0 <ex3>
  33:	89 45 f8             	mov    %eax,-0x8(%rbp)
  36:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  3a:	44 8b 6d f8          	mov    -0x8(%rbp),%r13d
  3e:	45 0f af e5          	imul   %r13d,%r12d
  42:	44 89 6d fc          	mov    %r13d,-0x4(%rbp)
  46:	8b 45 fc             	mov    -0x4(%rbp),%eax

0000000000000049 <FIM>:
  49:	48 89 ec             	mov    %rbp,%rsp
  4c:	5d                   	pop    %rbp
  4d:	c3                   	retq 
