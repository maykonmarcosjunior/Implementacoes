# Escreva um programa em Assembly do MIPS que implemente a função escrita em alto nível
# apresentada abaixo. Considere que:
# – Os valores de g, h, i, j devem ser números inteiros informados pelo usuário via teclado;
# – Os valores lidos (g, h, i, j) e o valor calculado (f) devem ser armazenados em memória;
# – A função calcula() deverá ser implementada como um procedimento no Assembly do MIPS.
# -----
# int calcula (int g, int h, int i, int j) {
# 	int f;
#	f = (g + h) - (i + j);
#	return f;
# }
.data
	f: .word 0
	g: .word 0
	h: .word 0
	i: .word 0
	j: .word 0
.text
main:
	la $s0 g
	la $s1 h
	la $s2 i
	la $s3 j
	la $s4 f
	
	li $v0, 5
	syscall
	move $a0, $v0 # a0 = g
	li $v0, 5
	syscall
	move $a1, $v0 # a1 = h
	li $v0, 5
	syscall
	move $a2, $v0 # a2 = i
	li $v0, 5
	syscall
	move $a3, $v0 # a3 = j
	jal calcula
	sw $a0 0($s0)
	sw $a1 0($s1)
	sw $a2 0($s2)
	sw $a3 0($s3)
	sw $v0 0($s4)
	j exit
calcula:
	addi $sp, $sp, -8
	sw $t1, 4($sp)
	sw $t0, 0($sp)
	add $t0, $a0, $a1
	add $t1, $a2, $a3
	sub $t0, $t0, $t1
	move $v0, $t0
	lw $t1, 4($sp)
	lw $t0, 0($sp)
	addi $sp, $sp, 8
	jr $ra
exit: nop
