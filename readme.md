# Laboratorio #3

**Dulce Ambrosio - 231143**  
Universidad del Valle de Guatemala  
Sistemas Operativos - CC3064

---

## Descripcion

Este proyecto valida un Sudoku 9x9 usando memoria mapeada, `fork()`, `pthread` y OpenMP. Se incluyen cuatro versiones con diferentes estrategias de paralelizacion para comparar comportamiento y salida de hilos/procesos.

---

## Estructura del proyecto

```
Sistemas_Operativos/
│
├── SudokuValidator1.c
├── SudokuValidator2.c
├── SudokuValidator3.c
├── SudokuValidator4.c
└── readme.md
```

---

## Formato de entrada

- Archivo de 81 caracteres con digitos del 1 al 9, sin espacios ni saltos de linea.
- El archivo se lee con `mmap()` y se carga a una matriz 9x9.

---

## Versiones

### SudokuValidator1.c

- Subcuadros 3x3: secuencial.
- Columnas: un `pthread` (sin OpenMP).
- Filas: secuencial.
- Usa `fork()` para mostrar procesos antes y despues del `pthread` con `ps`.

### SudokuValidator2.c

- Subcuadros 3x3: `#pragma omp parallel for`.
- Columnas: `pthread` + OpenMP en el `for`.
- Filas: OpenMP en el `for`.

### SudokuValidator3.c

- Igual a la version 2, pero con `schedule(dynamic)`.
- `omp_set_num_threads(1)` fuerza ejecucion serial de OpenMP.

### SudokuValidator4.c

- OpenMP anidado (`omp_set_nested(1)`).
- `omp_set_num_threads(9)` para 9 columnas y trabajo del `main`.
- Columnas y filas paralelizadas con OpenMP.


---

## Compilacion y ejecucion

### Compilacion general

```bash
gcc -o nombre_ejecutable archivo.c
```

### Version 1

```bash
gcc -o validator1 SudokuValidator1.c -pthread
./validator1 sudoku.c
```

### Version 2

```bash
gcc -o validator2 SudokuValidator2.c -pthread -fopenmp
./validator2 sudoku.c
```

### Version 3

```bash
gcc -o validator3 SudokuValidator3.c -pthread -fopenmp
./validator3 sudoku.c
```

### Version 4

```bash
gcc -o validator4 SudokuValidator4.c -pthread -fopenmp
./validator4 sudoku.c
```

---

