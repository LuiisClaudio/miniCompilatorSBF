
ex2.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <ex2>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 14          	sub    $0x14,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx
   d:	41 89 fc             	mov    %edi,%r12d
  10:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  16:	45 01 e5             	add    %r12d,%r13d
  19:	44 89 6d fc          	mov    %r13d,-0x4(%rbp)
  1d:	bb 00 00 00 00       	mov    $0x0,%ebx
  22:	8b 45 fc             	mov    -0x4(%rbp),%eax
  25:	83 fb 00             	cmp    $0x0,%ebx
  28:	74 05                	je     2f <FIM>
  2a:	b8 00 00 00 00       	mov    $0x0,%eax

000000000000002f <FIM>:
  2f:	48 89 ec             	mov    %rbp,%rsp
  32:	5d                   	pop    %rbp
  33:	c3                   	retq   
  34:	89 7d fc             	mov    %edi,-0x4(%rbp)
  37:	44 89 6d fc          	mov    %r13d,-0x4(%rbp)
  3b:	44 89 6d f8          	mov    %r13d,-0x8(%rbp)
  3f:	44 89 6d f4          	mov    %r13d,-0xc(%rbp)
  43:	44 89 6d f0          	mov    %r13d,-0x10(%rbp)
  47:	44 89 6d ec          	mov    %r13d,-0x14(%rbp)
  4b:	41 bc 01 00 00 00    	mov    $0x1,%r12d
  51:	41 bc 02 00 00 00    	mov    $0x2,%r12d
  57:	41 bc 03 00 00 00    	mov    $0x3,%r12d
  5d:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  61:	44 8b 65 f8          	mov    -0x8(%rbp),%r12d
  65:	44 8b 65 f4          	mov    -0xc(%rbp),%r12d
  69:	44 8b 65 f0          	mov    -0x10(%rbp),%r12d
  6d:	44 8b 65 ec          	mov    -0x14(%rbp),%r12d
  71:	41 89 fd             	mov    %edi,%r13d
  74:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  7a:	41 bd 02 00 00 00    	mov    $0x2,%r13d
  80:	41 bd 03 00 00 00    	mov    $0x3,%r13d
  86:	44 8b 6d fc          	mov    -0x4(%rbp),%r13d
  8a:	44 8b 6d f8          	mov    -0x8(%rbp),%r13d
  8e:	44 8b 6d f4          	mov    -0xc(%rbp),%r13d
  92:	45 01 e5             	add    %r12d,%r13d
  95:	45 29 e5             	sub    %r12d,%r13d
  98:	41 81 ec 00 00 00 00 	sub    $0x0,%r12d
  9f:	45 0f af ec          	imul   %r12d,%r13d
  a3:	41 89 fc             	mov    %edi,%r12d
  a6:	41 83 c4 01          	add    $0x1,%r12d
  aa:	41 83 c4 04          	add    $0x4,%r12d
  ae:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)
  b2:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  b6:	41 89 fc             	mov    %edi,%r12d
  b9:	44 03 65 fc          	add    -0x4(%rbp),%r12d
  bd:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)
  c1:	c7 45 f8 07 00 00 00 	movl   $0x7,-0x8(%rbp)
  c8:	44 8b 65 f8          	mov    -0x8(%rbp),%r12d
  cc:	41 89 fc             	mov    %edi,%r12d
  cf:	44 03 65 f8          	add    -0x8(%rbp),%r12d
  d3:	44 89 65 f8          	mov    %r12d,-0x8(%rbp)
  d7:	89 fb                	mov    %edi,%ebx
  d9:	bb cc 06 06 00       	mov    $0x606cc,%ebx
  de:	bb 15 25 00 00       	mov    $0x2515,%ebx
  e3:	8b 5d fc             	mov    -0x4(%rbp),%ebx
  e6:	8b 5d f8             	mov    -0x8(%rbp),%ebx
  e9:	8b 5d f4             	mov    -0xc(%rbp),%ebx
  ec:	8b 5d f0             	mov    -0x10(%rbp),%ebx
  ef:	8b 5d ec             	mov    -0x14(%rbp),%ebx
  f2:	8b 45 fc             	mov    -0x4(%rbp),%eax
  f5:	8b 45 f8             	mov    -0x8(%rbp),%eax
  f8:	8b 45 f4             	mov    -0xc(%rbp),%eax
  fb:	8b 45 f0             	mov    -0x10(%rbp),%eax
  fe:	8b 45 ec             	mov    -0x14(%rbp),%eax
 101:	89 f8                	mov    %edi,%eax
 103:	b8 74 0f 00 00       	mov    $0xf74,%eax
 108:	b8 bf e8 90 00       	mov    $0x90e8bf,%eax
 10d:	83 fb 00             	cmp    $0x0,%ebx
 110:	0f 84 19 ff ff ff    	je     2f <FIM>
 116:	48 89 ec             	mov    %rbp,%rsp
 119:	5d                   	pop    %rbp
 11a:	c3                   	retq   
