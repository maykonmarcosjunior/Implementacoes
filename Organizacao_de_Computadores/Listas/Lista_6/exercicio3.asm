# Escreva um programa que receba dois valores inteiros S e C, calcule e exiba a média:
# MEDIA = S (float) / C (float) como um número de ponto flutuante de precisão simples.
# Dica: use a instrução de conversão adequada para converter S e C de palavras inteiras
# em flutuação de precisão simples.
.text
main:
	li $v0, 5
	syscall
	mtc1.d $v0, $f0
	cvt.d.w $f0, $f0
	li $v0, 5
	syscall
	mtc1.d $v0, $f12
	cvt.d.w $f12, $f12
	div.d $f12, $f0, $f12
	li $v0, 3
	syscall
	
