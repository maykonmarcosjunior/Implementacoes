# 1) Dadas as matrizes A e B (abaixo), elabore um programa em Assembly para o processador MIPS (usando o simulador MARS)
# que encontre a matriz resultante do produto: A.B. Armazene a matriz resultante na memória de dados.
# A = [ 1  2  3 ]        B = [ 1  -2  5 ]        C = [ 1  0  0 ]
#     [ 0  1  4 ]            [ 0  1  -4 ]	     [ 0  1  0 ]
#     [ 0  0  1 ]	     [ 0  0  1  ]	     [ 0  0  1 ]

.data
	A: .word 1 2 3 0 1 4 0 0 1
	B: .word 1 -2 5 0 1 -4 0 0 1
	C: .word 0 0 0 0 0 0 0 0 0
.text
main:
	la $s0, A
	la $s1, B
	la $s2, C
	
	li $t0, 3 # i
	move $t1, $t0 # j
	move $t2, $t0 # k
	
	li $a0, 0 # a0 = i => A[0][0]
	li $a1, 0 # a1 = j => B[0][0]
	li $v0, 0
	jal controle	

controle:
	jal multiplicacao
	addi $t0, $t0, -1
	bnez $t0, LOOPi
	li $t0, 3
	sw $v0, 0($s2) # C[0][0] = A[i].B[][j]
	addi, $s2, $s2, 4
	li $v0, 0

	addi $t1, $t1, -1
	bnez $t1, LOOPj
	li $t1, 3

	addi $t2, $t2, -1
	bnez $t2, LOOPk
	j FIM
LOOPi:
	addi $a0, $a0, 4
	addi $a1, $a1, 12
	j controle
LOOPj:
	addi $a0, $a0, -8 # desfazer o LOOPi
	addi $a1, $a1, -20 # desfazer o LOOPi e somar 4
	j controle
LOOPk:
	addi $a0, $a0, 4 # ir para a próxima coluna
	li $a1, 0 # desfazer o LOOPi e o LOOPj
	j controle
multiplicacao:
	add $s0, $s0, $a0
	add $s1, $s1, $a1
	lw $a2, 0($s0) # a2 = A[a0]
	lw $a3, 0($s1) # a3 = B[a1]
	sub $s0, $s0, $a0
	sub $s1, $s1, $a1
	mult $a2, $a3 # multiplicação dos argumentos
  	mflo $a2 # valores são pequenos
	add $v0, $v0, $a2
	jr $ra

FIM: nop
