# Reproduza cada uma das expressões escritas em linguagem de alto nível a seguir para Assembly do
# MIPS. Considerações:
# – As variáveis a e b são posições de memória (segmento de dados). Os valores (inteiros positivos)
#dessas variáveis devem ser informados pelo usuário via teclado.
# – Implemente pequenos programas, um para cada expressão abaixo.
# if (a == b) {b = a;}
.text
main:
	li $v0, 5
	syscall
	move $s0, $v0
	li $v0, 5
	syscall
	move $s1, $v0
	sub $s1, $s0, $s1
	bne $s1, $0, exit
	move $s1, $s0
exit: 
	li $v0, 1
	move $a0, $s1
	syscall
