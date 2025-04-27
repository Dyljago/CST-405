.data
t0: .word 0
t1: .word 1
t2: .asciiz "outside"
.text
.globl main
main:
	lw $t0, t0
	jal while_1

while_1:
	li $t3, 3
	bge $t0, $t3, end_loop_1
	lw $t0, t0
	move $a0, $t0
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	lw $t0, t0
	add $t0, $t0, 1
	sw $t0, t0
	j while_1

end_loop_1:
	li $v0, 4
	la $a0, t2
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	lw $t0, t0
	move $a0, $t0
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	lw $t0, t0
	jal while_2

while_2:
	li $t4, 1
	blt $t0, $t4, end_loop_2
	lw $t0, t0
	move $a0, $t0
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	lw $t0, t0
	sub $t0, $t0, 1
	sw $t0, t0
	j while_2

end_loop_2:
	li $v0, 4
	la $a0, t2
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	lw $t0, t0
	move $a0, $t0
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	li $v0, 10
	syscall
