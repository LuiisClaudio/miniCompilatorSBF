
ex4.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <f0>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	48 83 ec 20          	sub    $0x20,%rsp
   8:	bb 00 00 00 00       	mov    $0x0,%ebx

   d:	41 89 fc             	mov    %edi,%r12d
  10:	41 89 fd             	mov    %edi,%r13d
  13:	45 0f af e5          	imul   %r13d,%r12d
  17:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)

  1b:	bb 00 00 00 00       	mov    $0x0,%ebx
  20:	8b 45 fc             	mov    -0x4(%rbp),%eax
  23:	83 fb 00             	cmp    $0x0,%ebx
  26:	74 05                	je     2d <FIM0>
  28:	b8 00 00 00 00       	mov    $0x0,%eax

000000000000002d <FIM0>:
  2d:	48 89 ec             	mov    %rbp,%rsp
  30:	5d                   	pop    %rbp
  31:	c3                   	retq   

0000000000000032 <f1>:
  32:	55                   	push   %rbp
  33:	48 89 e5             	mov    %rsp,%rbp
  36:	48 83 ec 20          	sub    $0x20,%rsp
  3a:	bb 00 00 00 00       	mov    $0x0,%ebx

  3f:	89 fb                	mov    %edi,%ebx
  41:	b8 00 00 00 00       	mov    $0x0,%eax
  46:	83 fb 00             	cmp    $0x0,%ebx
  49:	74 4b                	je     96 <FIM1>
  4b:	b8 00 00 00 00       	mov    $0x0,%eax

  50:	41 89 fc             	mov    %edi,%r12d
  53:	41 bd 01 00 00 00    	mov    $0x1,%r13d
  59:	45 29 ec             	sub    %r13d,%r12d
  5c:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)

  60:	89 ff                	mov    %edi,%edi
  62:	e8 00 00 00 00       	callq  67 <f1+0x35>
  67:	89 45 f8             	mov    %eax,-0x8(%rbp)

  6a:	8b 7d fc             	mov    -0x4(%rbp),%edi
  6d:	e8 00 00 00 00       	callq  72 <f1+0x40>
  72:	89 45 fc             	mov    %eax,-0x4(%rbp)

  75:	44 8b 65 fc          	mov    -0x4(%rbp),%r12d
  79:	44 8b 6d f8          	mov    -0x8(%rbp),%r13d
  7d:	45 01 ec             	add    %r13d,%r12d
  80:	44 89 65 fc          	mov    %r12d,-0x4(%rbp)

  84:	bb 00 00 00 00       	mov    $0x0,%ebx
  89:	8b 45 fc             	mov    -0x4(%rbp),%eax
  8c:	83 fb 00             	cmp    $0x0,%ebx
  8f:	74 05                	je     96 <FIM1>
  91:	b8 00 00 00 00       	mov    $0x0,%eax

0000000000000096 <FIM1>:
  96:	48 89 ec             	mov    %rbp,%rsp
  99:	5d                   	pop    %rbp
  9a:	c3                   	retq 
