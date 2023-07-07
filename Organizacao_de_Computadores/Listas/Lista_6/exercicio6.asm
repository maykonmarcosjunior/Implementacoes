# O método iterativo de Newton pode ser usado para aproximar a raiz quadrada de um número x,
# usando a expressão: guess = ((x/guess) + guess) / 2. Deve-se iniciar o algoritmo com o valor 1(guess).
# Escreva uma função chamada square_root que recebe um parâmetro de precisão dupla x, calcula,
# e retorna o valor aproximado da raiz quadrada de x. Escreva um loop que se repita 20 vezes
# e calcula 20 valores de palpite e, em seguida, retorna o palpite final após 20 iterações. Compare o
# resultado da instrução sqrt.d com o resultado de sua função square_root. Qual é o erro em valor absoluto?
.text
main:
	li $v0, 7
	syscall # f0 = x
	li $a0, 2
	mtc1 $a0, $f2
	cvt.d.w $f2, $f2 # f2 = 2
	li $a0, 20
	div.d $f12, $f0, $f2 # f12 = guess = x/2
	jal square_root
	li $v0, 3
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	sqrt.d $f12, $f0
	li $v0, 3
	syscall
	j exit
square_root:
	div.d $f4, $f0, $f12 # f4 =  x/guess
	add.d $f12, $f4, $f12 # f12 = (x/guess + guess)
	div.d $f12, $f12, $f2 # f12 = (x/guess + guess)/2
	addi $a0, $a0, -1
	bnez $a0, square_root
	jr $ra
exit:nop
