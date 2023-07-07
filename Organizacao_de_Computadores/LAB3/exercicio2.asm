# Implemente um programa no MARS que percorrerá uma matriz inteira
# de 16 por 16 elementos, coluna após coluna, atribuindo aos elementos
# os valores de 0 a 255 na ordem. Para isso, seu programa deverá
# incluir o seguinte algoritmo:
# int value = 0;
# for (int col = 0; col < 16; col++) {
#	for (int row = 0; row < 16; row++) {
#		matriz[row][col] = value;
#		value++;
#	}
# }

.data
	matriz: .space 16
.text
main:
	la $a0, matriz
	jal inicio_aloc
	j exit
inicio_aloc:
	addi $sp, $sp, -4
	sw $s0, 0($sp)
	move $s0, $a0
	li $a0, 0 # int row = 0
	li $a1, 0 # int col = 0
	li $a2, 0 # value
	li $a3, 64 # passo
alocacao:
	sw $a2, 0($s0) # *a3 = value
	addi $a2, $a2, 1 # value++
	add $s0, $s0, $a3
	
	addi $a0, $a0, 1 # row++
	blt $a0, 16, alocacao # row < 16
	li $a0, 0 # row = 0
	addi $s0, $s0, -1020
	addi $a1, $a1, 1 #col++
	blt $a1, 16, alocacao # col < 16
desaloc:
	lw $s0, 0($sp)
	addi $sp, $sp, 4
	jr $ra
exit:nop