# Reproduza cada uma das expressões escritas em linguagem de alto nível a seguir para Assembly do
# MIPS. Considerações:
# – As variáveis a e b são posições de memória (segmento de dados). Os valores (inteiros positivos)
#dessas variáveis devem ser informados pelo usuário via teclado.
# – Implemente pequenos programas, um para cada expressão abaixo.
# if (a < b)
#  a = a + 1;
# else
#  b = b + 1;
.text
main:
	li $v0, 5
	syscall
	move $s0, $v0
	li $v0, 5
	syscall
	move $s1, $v0
	bge $s0, $s1, incrementaB
incrementaA:
	addi $s0, $s0, 1
	li $a0, 'a'
	move $a1, $s0
	j exit
incrementaB:
	addi $s1, $s1, 1
	li $a0, 'b'
	move $a1, $s1
	j exit
exit: 
	li $v0, 11
	syscall
	li $v0, 11
	li $a0, ' '
	syscall
	li $v0, 11
	li $a0, '='
	syscall
	li $v0, 11
	li $a0, ' '
	syscall
	li $v0, 1
	move $a0, $a1
	syscall
