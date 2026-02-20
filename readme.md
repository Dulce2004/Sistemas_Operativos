# Laboratorio 2 de Sistemas Operativos

**Dulce Ambrosio - 231143**  
Universidad del Valle de Guatemala  
Sistemas Operativos - Semestre 7

---

## Descripción

este laboratorio reforzará el concepto de proceso, terminación, relación padre-hijo y cambio
de contexto. También se implementarán tres medios comunes de comunicación entre procesos: memoria
compartida, pipes ordinarios y pipes nombrados. Es obligatorio el uso de estos tres medios de
comunicación entre procesos. Deberá entregar un documento con las respuestas a las preguntas
planteadas en cada ejercicio (incluyendo diagramas o escaneos si es necesario), junto con todos los
archivos de código que programe.


---

## Estructura del Proyecto

```
Sistemas_Operativos/
│
├── Ejercicio1/          # Creación masiva de procesos
│   ├── foks_consecutivos.c
│   └── fork_dentroFor.c
│
├── Ejercicio2/          # Comparación secuencial vs concurrente
│   ├── primer_programa.c
│   └── segundo_programa.c
│
├── Ejercicio3/          # Concurrencia con salida intensiva
│   ├── primer_programa.c
│   └── segundo_programa.c
│
├── Ejercicio4/          # Procesos zombie y huérfanos
│   ├── fork_ejercicio4.c
│   └── ejercicio4_modificado.c
│
├── Ejercicio5/          # Comunicación entre procesos (IPC)
│   ├── ipc.c
│   └── Segundo_Programa.c
│
└── readme.md
```

---

## Ejercicios

### Ejercicio 1: Creación Masiva de Procesos

**Objetivo:** Comparar diferentes formas de crear múltiples procesos con `fork()` y analizar el número de procesos generados.




### Ejercicio 2: Ejecución Secuencial vs Concurrente

**Objetivo:** Comparar el tiempo de ejecución entre procesamiento secuencial y concurrente usando procesos múltiples.


### Ejercicio 3: Concurrencia con Salida Intensiva

**Objetivo:** Analizar el impacto de operaciones de I/O (escritura a terminal) en ejecución secuencial vs concurrente.


### Ejercicio 4: Procesos Zombie y Huérfanos

**Objetivo:** Reproducir y analizar los estados especiales de procesos en Linux.

### Ejercicio 5: Comunicación Entre Procesos (IPC)

**Objetivo:** Implementar comunicación entre procesos usando pipes y memoria compartida.


---

## Compilación y Ejecución

### Compilación General

```bash
gcc -o nombre_ejecutable archivo.c
```

### Ejercicio 1

```bash
gcc -o forks_consecutivos Ejercicio1/foks_consecutivos.c
./forks_consecutivos

gcc -o fork_for Ejercicio1/fork_dentroFor.c
./fork_for
```

### Ejercicio 2 y 3

```bash
gcc -o secuencial Ejercicio2/primer_programa.c
./secuencial

gcc -o concurrente Ejercicio2/segundo_programa.c
./concurrente
```

### Ejercicio 4

```bash
gcc -o zombie Ejercicio4/fork_ejercicio4.c
./zombie &
ps -ael | grep Z

gcc -o zombie_mod Ejercicio4/ejercicio4_modificado.c
./zombie_mod
```

### Ejercicio 5

```bash
# Compilar con soporte de memoria compartida
gcc -o ipc Ejercicio5/ipc.c -lrt
./ipc 4 X

# Compilar y ejecutar coordinador
gcc -o coordinador Ejercicio5/Segundo_Programa.c
./coordinador
```

---

