.data
    mensajeN:      .asciiz "Introduce el grado del polinomio: "
    mensaje_coef:   .asciiz "Introduce el coeficiente: "
    mensaje_x:      .asciiz "\nIntroduce el valor de x (float): "
    resultado:    .asciiz "\nEl resultado de P(x) es: "
    newline:       .asciiz "\n"
    
    zero_float:    .float 0.0
    one_float:     .float 1.0

.text

main:
    # Pedir el grado del polinomio
    li $v0, 4
    la $a0, mensajeN
    syscall

    li $v0, 5
    syscall
    move $t0, $v0

    # Reservar memoria para los coeficientes
    addi $t1, $t0, 1
    li $v0, 9
    mul $a0, $t1, 4
    syscall
    move $s0, $v0
    move $s1, $s0

    # Leer coeficientes
    li $t2, 0

input_coef:
    bge $t2, $t1, read_x

    li $v0, 4
    la $a0, mensaje_coef
    syscall

    li $v0, 6
    syscall
    s.s $f0, 0($s0)
    addi $s0, $s0, 4
    addi $t2, $t2, 1
    j input_coef

read_x:
    li $v0, 4
    la $a0, mensaje_x
    syscall

    li $v0, 6
    syscall
    mov.s $f12, $f0

    # Calcular P(x)
    move $s0, $s1
    li $t2, 0

    l.s $f2, zero_float
    l.s $f4, one_float

calc_poli:
    bge $t2, $t1, print_result

    l.s $f6, 0($s0)
    addi $s0, $s0, 4

    mul.s $f8, $f4, $f6
    add.s $f2, $f2, $f8

    mul.s $f4, $f4, $f12

    addi $t2, $t2, 1
    j calc_poli

print_result:
    li $v0, 4
    la $a0, resultado
    syscall

    li $v0, 2
    mov.s $f12, $f2
    syscall

    li $v0, 10
    syscall
