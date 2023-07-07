#Escreva um pequeno programa que armazene as seguintes half-words: 1 , 2, -2, -3.
# Verifique na memória de dados como estes números foram armazenados.
.data
	espacos: .half 0 0 0 0
.text
main:
	la $s0, espacos
	li $t0, 1
	li $t1, 2
	li $t2, -2
	li $t3, -3

	sh $t0, 0($s0)
	sh $t1, 2($s0)
	sh $t2, 4($s0)
	sh $t3, 6($s0)
