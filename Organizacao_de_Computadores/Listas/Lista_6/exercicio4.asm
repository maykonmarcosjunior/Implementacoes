# Implemente um programa que chame um procedimento para calcular a raiz de uma equação
# completa do primeiro grau, na forma Ax + B = 0. Os coeficientes, todos em ponto flutuante de
# precisão simples, devem ser informados pelo teclado. O valor da raiz deve ser apresentado no monitor.
.text
main:
	li $v0, 6
	syscall
	mov.s $f12, $f0 # f12 = A
	li $v0, 6
	syscall # f0 = B
	div.s $f0, $f0, $f12
	neg.s $f12, $f0
	li $v0, 2
	syscall
	
