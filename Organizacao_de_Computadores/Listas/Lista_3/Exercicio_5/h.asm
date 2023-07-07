# Reproduza cada uma das expressões escritas em linguagem de alto nível a seguir para Assembly do
# MIPS. Considerações:
# – As variáveis a e b são posições de memória (segmento de dados). Os valores (inteiros positivos)
#dessas variáveis devem ser informados pelo usuário via teclado.
# – Implemente pequenos programas, um para cada expressão abaixo.
# switch(a){
#    case 1:
#	b = c + 1;
#	break;
#    case 2:
#	b = c + 2;
#	break;
#    default:
#	b = c;
#	break;}
.data
	a: .word 0
	b: .word 0
	c: .word 0
.text
main:
	la $s0, a
	la $s1, b
	la $s2, c

	li $v0, 5
	syscall
	move $t0, $v0 #t0 = a
	li $v0, 5
	syscall
	move $t1, $v0 #t1 = b
	li $v0, 5
	syscall
	move $t2, $v0 #t2 = c
	li $a0, 1
	beq $t0, $a0 exit # a = 1 --> case1
	li $a0, 2
	beq $t0, $a0 exit # a = 2 --> case2
	li $a0, 0 # a /= 1 /= 2 --> default
exit: 
	add $t1, $t2, $a0
	sw $t0, 0($s0)
	sw $t1, 0($s1)
	sw $t2, 0($s2)
