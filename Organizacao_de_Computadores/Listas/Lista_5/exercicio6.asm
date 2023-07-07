# Adapte o programa do item 4) para que utilize uma estrutura de iteração tipo while,
# com critério de parada ao encontrar o final da string armazenada usando o caractere \0 (NULL).

.data
	string: .space 8
.text
main:
	li $v0, 8
	la $a0, string
	li $a1, 8
	syscall
	li $a2, 'a'
	jal loader
	li $v0, 1
	move $a0, $a1
	syscall
	j exit
loader:
	lb $a3, 0($a0)
	beq $a2, $a3 contador
	addi $a1, $a1, -1
contador:
	addi $a0, $a0, 1
	bne $a3, $0, loader
	jr $ra
exit: nop
