# Reproduza cada uma das expressões escritas em linguagem de alto nível a seguir para Assembly do
# MIPS. Considerações:
# – As variáveis a e b são posições de memória (segmento de dados). Os valores (inteiros positivos)
#dessas variáveis devem ser informados pelo usuário via teclado.
# – Implemente pequenos programas, um para cada expressão abaixo.
# a = 0; b = 0;  c = 5;
# while (a < c){a = a + 1; b = b + 2;}
.data
	a: .word 0
	b: .word 0
	c: .word 5
.text
main:
	la $s0, a
	la $s1, b
	la $s2, c
	lw $a0, 0($s0) # a0 = a
	lw $a1, 0($s1) # a1 = b
	lw $a2, 0($s2) # a2 = c
LOOP:
	bge $a0, $a2, atribui
	addi $a0, $a0, 1
	addi $a1, $a1, 2
	j LOOP
atribui:
	sw $a0, 0($s0)
	sw $a1, 0($s1)
exit: 
	move $s0, $a0
	li $v0, 11
	li $a0, 'a'
	syscall
	li $v0, 11
	li $a0, '='
	syscall
	li $v0, 1
	move $a0, $s0
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	li $v0, 11
	li $a0, 'b'
	syscall
	li $v0, 11
	li $a0, '='
	syscall
	li $v0, 1
	move $a0, $a1
	syscall
