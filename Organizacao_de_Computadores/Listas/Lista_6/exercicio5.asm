# Implemente um programa que chame um procedimento para calcular as raízes de uma equação
# completa do segundo grau, na forma Ax2 + Bx + C = 0. Os coeficientes da equação, todos em ponto
# flutuante de precisão dupla, devem ser informados pelo teclado e os valores das raízes devem ser
# apresentados no monitor.
.text
main:
	li $v0, 7
	syscall
	mov.d $f4, $f0 # f4 = A
	li $v0, 7
	syscall
	mov.d $f2, $f0 # f2 = B
	li $v0, 7
	syscall # f0 = C
	add.d $f4, $f4, $f4 # f4 = 2A
	mul.d $f0, $f0, $f4 # f0 = 2A*C
	add.d $f0, $f0, $f0 # f0 = 4AC
	mul.d $f6, $f2, $f2 # f6 = B²
	sub.d $f0, $f6, $f0 # f0 = B² - 4AC
	sqrt.d $f0, $f0 # f0 = -/(B² - 4AC)
	neg.d $f2, $f2 # B = -B
	add.d $f6, $f2, $f0 # f6 = -B + -/delta
	sub.d $f2, $f2, $f0 # - B - -/delta
	div.d $f12, $f6, $f4 # x1 = (-B + -/delta) / 2A
	li $v0, 3
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall
	div.d $f12, $f6, $f4 # x2 = (-B - -/delta) / 2A
	li $v0, 3
	syscall
	
