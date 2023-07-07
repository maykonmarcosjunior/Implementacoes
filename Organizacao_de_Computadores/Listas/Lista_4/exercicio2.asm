# Implemente em Assembly do MIPS o código abaixo, escrito em linguagem C:
# int CalculaAreaQuadrado (int h, int w) {
#	int area = h * w;
#	return area
# }
# int main (void) {
#	int a = 4; int b = 10;
#	int val = CalculaAreaQuadrado(a, b);
# }
.data
	a: .word 4
	b: .word 10
	val: .double 0
.text
main:
	la $s0, a
	la $s1, b
	la $s2, val
	lw $a0, 0($s0)
	lw $a1, 0($s1)
	jal CalculaAreaQuadrado
	sw $v1, 0($s2)
	sw $v0, 4($s2)
	j exit
CalculaAreaQuadrado:
	mult $a0, $a1
	mflo $v0
	mfhi $v1
	jr $ra
exit: nop
