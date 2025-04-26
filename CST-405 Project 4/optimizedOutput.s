.data
t1: .word 1
t4: .word 2
t5: .word 6
.text
.globl main
addOne:
	li $v0, 1
	li $a0, 6
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $a0, 6
	addi $a0, $a0, 1
	move $v0, $a0
	jr $ra

subOne:
	addi $a0, $a0, -1
	move $v0, $a0
	jr $ra

mulTwo:
	mul $a0, $a0, 2
	move $v0, $a0
	jr $ra

main:
	li $a0, 6
	jal addOne
	move $t5, $v0

	move $a0, $t5
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	li $v0, 10
	syscall
