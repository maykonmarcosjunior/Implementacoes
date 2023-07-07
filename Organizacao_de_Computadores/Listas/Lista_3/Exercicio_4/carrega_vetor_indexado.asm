# assumindo que o registrador $s0 contém o valor 0x10010020,
# faça um programa que contenha a sequência de
# instruções MIPS correspondentes às instruções C seguintes:
# i = 0; v[i] = 1; i = i + 1; v[i] = 3; i = i + 1; v[i] = 2;
# i = i + 1; v[i] = 1; i = i + 1; v[i] = 4; i = i + 1; v[i] = 5;
.text
main_:
	li $s0, 0x10010020
	li $a1, 0

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
	li $a2, 0
	add $a2, $a1, $a1
	add $a2, $a1, $a1
	add $a2, $s0, $a2
	sw $a0, 0($a2)
	jr $ra
EXIT: nop
