# Faça um programa que carregue o vetor v=[1,3,2,1,4,5] para a memória. Ou seja, que contenha a
# sequência de instruções MIPS correspondentes às instruções C seguintes:
# v[0] = 1; v[1] = 3; v[2] = 2; v[3] = 1; v[4] = 4; v[5] = 5;
# Assuma que o registrador $s0 contém o endereço de início do vetor como sendo 0x10010020.
.text
main_:
	li $s0, 0x10010020
	li $a0, 1
	jal LOOP
	li $a0, 3
	jal LOOP
	li $a0, 2
	jal LOOP
	li $a0, 1
	jal LOOP
	li $a0, 4
	jal LOOP
	li $a0, 5
	jal LOOP
	jal EXIT
LOOP:
	sw $a0, 0($s0)
	addi $s0, $s0, 4
	jr $ra
EXIT: nop
