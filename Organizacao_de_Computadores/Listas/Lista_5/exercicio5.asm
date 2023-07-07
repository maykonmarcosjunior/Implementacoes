# Adapte o programa do item 4) para utilizar uma estrutura de iteração (laço for)
# para testar as letras da string armazenada.

.data
	string: .space 8
.text
main:
	li $v0, 8
	la $a0, string
	li $a1, 8
	syscall
	li $a2, 'a'
	move $t0, $a1
	jal loader
	li $v0, 1
	move $a0, $t0
	syscall
	j exit
loader:
	lb $a3, 0($a0)
	addi $a1, $a1, -1
	beq $a2, $a3 contador
	addi $t0, $t0, -1
contador:
	addi $a0, $a0, 1
	bnez $a1, loader
	jr $ra
exit: nop
