# Reproduza cada uma das expressões escritas em linguagem de alto nível a seguir para Assembly do
# MIPS. Considerações:
# – As variáveis a e b são posições de memória (segmento de dados). Os valores (inteiros positivos)
#dessas variáveis devem ser informados pelo usuário via teclado.
# – Implemente pequenos programas, um para cada expressão abaixo.
# a = 1; b = 2;
# for (i = 0; i < 5; i ++){ a = b + 1; b = b + 3;}
.data
	a: .word 1
	b: .word 2
.text
main:
	la $s0, a
	la $s1, b
	lw $a0, 0($s0) # a0 = a
	lw $a1, 0($s1) # a1 = b
	li $a2, 5 # i = 5
LOOP:
	addi $a0, $a1, 1
	addi $a1, $a1, 3
	subi $a2, $a2, 1
	beqz $a2, exit
	j LOOP
exit:
	sw $a0, 0($s0)
	sw $a1, 0($s1)
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
