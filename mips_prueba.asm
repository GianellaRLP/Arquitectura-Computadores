.data
num1:     .asciiz "Introduce el primer numero: "
num2:     .asciiz "Introduce el segundo numero: "
msg_igual:   .asciiz "Los números son iguales.\n"
msg_menor:   .asciiz "El primer número es menor que el segundo.\n"
msg_mayor:   .asciiz "El primer número es mayor que el segundo.\n"
msg_no_cumple: .asciiz "No cumple la condicion\n"

.text
main:
    li $v0, 4
    la $a0, num1
    syscall
    li $v0, 5
    syscall
    move $t0, $v0

    li $v0, 4
    la $a0, num2
    syscall
    li $v0, 5
    syscall
    move $t1, $v0

    # verificacion si los numeros osn iguales
    beq $t0, $t1, igual

    # verificacion si el primer número es menor que el segundo
    slt $t2, $t0, $t1
    bne $t2, $zero, menor

    # Si no es menor ni igual, entonces es mayor
    j mayor

igual:
    li $v0, 4
    la $a0, msg_igual
    syscall
    j end

menor:
    li $v0, 4
    la $a0, msg_menor
    syscall
    j end

mayor:
    li $v0, 4
    la $a0, msg_mayor
    syscall
    j end

end:
    li $v0, 10
    syscall
