# Faça um programa que calcule: ∑i:1 a 5

.text
main_:
	li $a0, 0
	li $a1, 1
	li $a2, 5
LOOP:
	add $a0, $a0, $a1
	addi $a1, $a1, 1
	subi $a2, $a2, 1
	bne $a2, $zero LOOP
	jal Exit
Exit: nop
