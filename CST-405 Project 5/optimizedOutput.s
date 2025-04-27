.data
t1: .word 1
t2: .word 10
t3: .asciiz "outside"
.text
.globl main
subOne:
	addi $a0, $a0, -1
	move $v0, $a0
	jr $ra

main:
	lw $t2, t2
	jal while

while:
	li $t4, 2
	blt $t2, $t4, end_loop
	lw $t2, t2
	move $a0, $t2
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	lw $a0, t2
	jal subOne
	move $t2, $v0
	la $a0, t2
	sw $t2, 0($a0)

	j while

end_loop:
	li $v0, 4
	la $a0, t3
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	lw $t2, t2
	move $a0, $t2
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
	syscall

	li $v0, 10
	syscall
