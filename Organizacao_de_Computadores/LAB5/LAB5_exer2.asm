# Implemente o algoritmo abaixo no MARS que
# realiza a soma de uma matriz com outra transposta.
# porém utilizando a técnica de cache blocking.
# O tamanho das matrizes (MAX) e dos blocos (block_size)
# devem ser parametrizáveis:
# obs: &nbsp significa "Non-breaking space" →
# preenche com espaços não visíveis um bloco. 
# 
# float A[MAX][MAX], B[MAX][MAX];
# for (int i = 0; i < MAX; i += block_size) {
#	for (int j = 0; j < MAX; j += block_size) {
#		for (int ii = i; ii < i+block_size; ii++) {
#			for (int jj = j; jj < j+block_size; jj++) {
#				A[ii][jj] = A[ii][jj] + B[jj][ii];
#			}
# 		}
#  	}
# }
#

.data
	A: 0
.text
main:
	la $s0, A
	li $t0, 8 # t0 = MAX
	li $t1, 4 # t1 = block_size
	multu $t0, $t0 # lo = MAX²
	mflo $t2 # t2 = MAX²
	sll $t2, $t2, 2 # t2 = 4*MAX²
	add $s1, $s0, $t2 # s1 = &B = &A + 4*MAX²
	li $a0, 0 # int ii = 0
	li $a1, 0 # int jj = 0
	li $a2, 0 # int i = 0
	li $a3, 0 # int j = 0
soma:
	# obtendo B[i][j]
	multu $a1, $t0 # lo = MAX*jj
	mflo $t2 # t2 = [jj][]
	add $t2, $t2, $a0 # t2 = [jj][ii]
	sll $t2, $t2, 2 # t2 *= 4
	add $t2, $t2, $s1 # t2 = &B[jj][ii]
	lw $t2, 0($t2) # $t2 = B[jj][ii]
	# obtendo-se A[ii][jj]
	multu $a0, $t0 # lo = MAX*ii
	mflo $t3 # t3 = [ii][]
	add $t3, $t3, $a1 # t3 = [ii][jj]
	sll $t3, $t3, 2 # t3 *= 4
	add $t3, $t3, $s0 # t3 = &A[ii][jj]
	lw $t4, 0($t3) # $t4 = A[ii][jj]
	add $t2, $t2, $t4 # t2 = A[ii][jj] + B[jj][ii]
	sw $t2, 0($t3) # A[ii][jj] += B[jj][ii]
	
	addi $a1, $a1, 1 # jj++
	add $t2, $a3, $t1 # t2 = j+block_size
	blt $a1, $t2, soma # jj < j+block_size
	move $a1, $a3 # jj = j
	addi $a0, $a0, 1 # ii++
	add $t2, $a2, $t1 # t2 = i+block_size
	blt $a0, $t2, soma # ii < i+block_size
	move $a0, $a2 # ii = i
	add $a3, $a3, $t1 # j += block_size
	move $a1, $a3 # jj = j
	blt $a3, $t0, soma # j < MAX
	li $a3, 0 # j = 0
	move $a1, $a3 # jj = j
	add $a2, $a2, $t1 # i += block_size
	move $a0, $a2 # ii = i
	blt $a2, $t0, soma # i < MAX
exit:nop
