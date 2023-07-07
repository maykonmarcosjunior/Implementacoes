# Adapte o programa anterior para contar quantas letras a (minúsculas)
# existem na palavra armazenada.
# Sugestão: teste o programa digitando a palavra abacate e veja se o 
# seu programa contará certo a quantidade de letras a.

.data
	string: .space 8
.text
main:
	li $v0, 8
	la $a0, string
	li $a1, 8
	syscall
	li $t0, 'a'
	subi $a1, $a1, 1
	lb $t2, 0($a0)
	beq $t2, $t0, d2
	subi $a1, $a1, 1
d2:
	lb $t2, 1($a0)
	beq $t2, $t0, d3
	subi $a1, $a1, 1
d3:
	lb $t2, 2($a0)
	beq $t2, $t0, d4
	subi $a1, $a1, 1
d4:
	lb $t2, 3($a0)
	beq $t2, $t0, d5
	subi $a1, $a1, 1
d5:
	lb $t2, 4($a0)
	beq $t2, $t0, d6
	subi $a1, $a1, 1
d6:
	lb $t2, 5($a0)
	beq $t2, $t0, d7
	subi $a1, $a1, 1
d7:
	lb $t2, 6($a0)
	beq $t2, $t0, exit
	subi $a1, $a1, 1
exit: 
	li $v0, 1
	move $a0, $a1
	syscall
