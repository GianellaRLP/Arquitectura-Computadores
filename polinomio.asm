.data
    prompt_n:      .asciiz "Introduce el grado del polinomio: "
    prompt_coef1:   .asciiz "Introduce el coeficiente  : "
    prompt_x:      .asciiz "\nIntroduce el valor de x (float): "
    result_msg:    .asciiz "\nEl resultado de P(x) es: "
    newline:       .asciiz "\n"
    
    # Declaramos los valores de 0.0 y 1.0 como constantes flotantes en memoria
    zero_float:    .float 0.0
    one_float:     .float 1.0

.text

main:
    # Pedir el grado del polinomio
    li $v0, 4                # syscall para imprimir string
    la $a0, prompt_n          # dirección del mensaje
    syscall

    li $v0, 5                # syscall para leer entero
    syscall
    move $t0, $v0            # $t0 contiene el grado n del polinomio

    # Reservar memoria para los coeficientes (4 bytes por coeficiente)
    addi $t1, $t0, 1         # cantidad de coeficientes (n + 1)
    li $v0, 9                # syscall para reservar memoria
    mul $a0, $t1, 4          # tamaño de la memoria a reservar (4 bytes por coeficiente)
    syscall
    move $s0, $v0            # $s0 contiene la dirección base de la memoria reservada
    move $s1, $s0            # Guardar la dirección base de los coeficientes en $s1

    # Pedir los coeficientes del polinomio como flotantes
    li $t2, 0                # índice para recorrer los coeficientes

input_coef:
    bge $t2, $t1, read_x     # si t2 >= n+1, terminar bucle

    li $v0, 4                # syscall para imprimir string
    la $a0, prompt_coef1       # mensaje para coeficientes
    syscall

    # Leer coeficiente en formato flotante
    li $v0, 6                # syscall para leer float
    syscall
    s.s $f0, 0($s0)          # guardar coeficiente flotante en memoria
    addi $s0, $s0, 4         # avanzar al siguiente espacio de memoria
    addi $t2, $t2, 1         # incrementar el índice
    j input_coef             # repetir el bucle

read_x:
    # Pedir valor de x
    li $v0, 4                # syscall para imprimir string
    la $a0, prompt_x          # mensaje para x
    syscall

    li $v0, 6                # syscall para leer float
    syscall
    mov.s $f12, $f0          # guardar valor de x en $f12

    # Volver a la base de los coeficientes
    move $s0, $s1            # Restablecer $s0 a la dirección base de los coeficientes
    li $t2, 0                # Inicializar el índice de la potencia

    # Cargar los valores de 0.0 y 1.0 desde memoria a registros flotantes
    l.s $f2, zero_float       # Inicializar acumulador P(x) con 0.0
    l.s $f4, one_float        # Inicializar x^0 = 1.0 para el primer término

calculate_polynomial:
    bge $t2, $t1, print_result  # Si hemos procesado todos los coeficientes, terminar

    l.s $f6, 0($s0)           # Cargar el coeficiente actual (ya es flotante)
    addi $s0, $s0, 4          # Avanzar al siguiente coeficiente

    # Multiplicar coeficiente por la potencia de x (x^t2)
    mul.s $f8, $f4, $f6       # Multiplicar coeficiente * x^t2

    # Acumular el resultado en f2 (P(x))
    add.s $f2, $f2, $f8       # Sumar al acumulador

    # Calcular la siguiente potencia de x (x^(t2+1))
    mul.s $f4, $f4, $f12      # Actualizar la potencia de x para la siguiente iteración

    addi $t2, $t2, 1          # Incrementar índice del polinomio
    j calculate_polynomial    # Repetir para el siguiente coeficiente

print_result:
    # Mostrar el mensaje de resultado
    li $v0, 4
    la $a0, result_msg
    syscall

    # Mostrar el valor de P(x)
    li $v0, 2                # syscall para imprimir flotante
    mov.s $f12, $f2          # mover el resultado de P(x) a $f12
    syscall

    # Terminar programa
    li $v0, 10               # syscall para terminar
    syscall
