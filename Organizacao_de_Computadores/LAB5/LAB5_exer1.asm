# Implemente o algoritmo abaixo no MARS que
# realiza a soma de uma matriz com outra transposta.
# (O tamanho das matrizes (MAX) deve ser parametrizável):
#
# float A[MAX][MAX], B[MAX][MAX];
# for (int i = 0; i < MAX; i++) {
#	for (int j = 0; j < MAX; j++) {
#		A[i][j] = A[i][j] + B[j][i];
#	}
# }
#

.data
	A: 0
.text
main:
	la $s0, A
	li $t0, 4 #t0 = MAX
	multu $t0, $t0 # lo = MAX²
	mflo $t1 # t1 = MAX²
	sll $t1, $t1, 2 # t1 = 4*MAX²
	add $s1, $s0, $t1 # s1 = &B = &A + 4*MAX²
	jal aloc_soma
aloc_soma:
	li $a0, 0 # int i = 0
	li $a1, 0 # int j = 0
	li $a2, 0
	multu $t0, $t0
	mflo $t7 # contador
	li $t8, 1 # valores em A
	li $t9, 2 # valores em B
	move $a0, $s0
	move $a1, $s1
loop_aloc:
	sw $t8, 0($a0) # A[c] = 1
	sw $t9, 0($a1) # B[c] = 2
	addi $a0, $a0, 4
	addi $a1, $a1, 4
	addi $t7, $t7, -1
	bnez $t7 loop_aloc
	li $a0, 0
	li $a1, 0
soma:
	# precisa multiplicar por MAX
	# para que valha uma linha
	multu $a1, $t0 # lo = MAX*j
	mflo $a2 # a2 = [j][]
	add $a2, $a2, $a0 # a2 = [j][i]
	sll $a2, $a2, 2 # a2 *= 4
	add $a2, $a2, $s1 # a2 = &B[i][j]
	lw $a2, 0($a2) # $a2 = B[i][j]
	# obtendo-se A[i][j]
	multu $a0, $t0 # lo = MAX*i
	mflo $a3 # a3 = [i][]
	add $t3, $a3, $a1 # t3 = [i][j]
	sll $t3, $t3, 2 # t3 *= 4
	add $t3, $t3, $s0 # t3 = &A[i][j]
	lw $a3, 0($t3) # $a3 = A[i][j]
	add $a2, $a2, $a3 # a2 = A[i][j] + B[j][i]
	sw $a2, 0($t3) # A[i][j] += B[j][i]	
	
	addi $a1, $a1, 1 #j++
	blt $a1, $t0, soma # j < MAX
	li $a1, 0 # col = 0
	addi $a0, $a0, 1 # i++
	blt $a0, $t0, soma # i < MAX
exit:nop
