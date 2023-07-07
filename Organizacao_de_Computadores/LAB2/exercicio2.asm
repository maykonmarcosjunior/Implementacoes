# armazene a matriz resultante do exercicio 1 em um arquivo com extensão .txt.
# Importante: você deve converter os elementos da matriz resultante em representações ASCII para
# poderem ser visualizados por uma pessoa no arquivo .txt.

.data
	
	C: .word 1 0 0 0 1 0 0 0 1
	STRING: .asciiz "                  "
	nome_arquivo: .asciiz "matriz.txt"
	
.text
main:
	la $s0, STRING
	la $s2, C
	li $s6, 3
	li $s7, 3

	li $v0, 13
	la $a0, nome_arquivo
	li $a1, 1
	li $a2, 0
	syscall
	move $s3, $v0

	jal LOOP
	
	li $v0, 15
	move $a0, $s3
	la $a1, STRING
	li $a2, 72
	syscall
	
	li $v0, 16
	move $a0, $s3
	syscall	
	
	jal FIM
	

LOOP:
	lw $t0, 0($s2)
	addi $t0, $t0, 48
	addi $s2, $s2, 4
	sw $t0, 0($s0)
	li $t0, ' '
	sw $t0, 4($s0)
	addi $s0, $s0, 8
	
	addi $s6, $s6, -1
	bnez $s6, LOOP
	li $s6, 3
	
	li $t0, '\n'
	sw $t0, -4($s0)
	
	addi $s7, $s7, -1
	bnez $s7, LOOP
	
	jr $ra

FIM: nop
