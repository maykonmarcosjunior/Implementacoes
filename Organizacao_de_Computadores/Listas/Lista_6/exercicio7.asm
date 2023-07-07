# Implemente o código abaixo, escrito em linguagem C, para Assembly do MIPS.
# Perceba que o valor da matriz a[][] é dupla precisão.
# int NUM; double a[10][10];
# void init() {
#    for(int i = 0; i < NUM; ++i) {
#        for (int j = 0; j < NUM; ++j) {
#    	     a[i][j] = i + j;
#        }
#    }
# }
# int main (void) {
#    NUM = 10; init();
#    for(int i = 0; i < NUM; ++i) {
#        for (int j = 0; j < NUM; ++j) {
#    	     printf("%lf\n", a[i][j])
#        }
# }
.data
	NUM: .word 10
	.align 3
	a: .space 800
.text
main:
	la $s0, a
	la $s1, NUM
	lw $t0, 0($s1)
	move $a0, $0 # i = 0
	move $a1, $0 # j = 0
	jal init
	move $a0, $0
	la $s0, a
	jal printar
	j exit
printar:
	li $v0, 3
	l.d $f12, 0($s0)
	syscall
	
	addi $s0, $s0, 8
	addi $a1, $a1, 1
	
	sub $a3, $t0, $a1 # se j = NUM
	movz $a1, $0, $a3 # --> j = 0
	addi $a3, $a0, 1
	movz $a0, $a3, $a1 # e i++
	move $a3, $0
	
	li $v0, 11
	move $t1, $a0
	li $a0, ' '
	li $t2, '\n'
	movz $a0, $t2, $a1
	syscall
	move $a0, $t1
	
	bne $t0, $a0, printar
	jr $ra
init:
	add $t1, $a1, $a0 # t1 = i+j
	mtc1.d $t1, $f0
	cvt.d.w $f0, $f0
	s.d $f0, 0($s0)
	
	addi $s0, $s0, 8
	addi $a1, $a1, 1
	
	sub $a3, $t0, $a1 # se j = NUM
	movz $a1, $0, $a3 # --> j = 0
	addi $a3, $a0, 1
	movz $a0, $a3, $a1 # e i++
	move $a3, $0
	
	bne $t0, $a0, init # enquanto i < NUM
	jr $ra
exit:nop
