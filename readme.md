##
Dulce Ambrosio - 231143
/ Sistemas Operativos
# Laboratorio de Sistemas Operativos

## Resumen 

Este laboratorio se realizó en un entorno virtualizado utilizando Ubuntu Linux en VirtualBox, con el objetivo de comprender los servicios que ofrece el sistema operativo, la interacción entre espacio de usuario y kernel, y el proceso de modificación y compilación de un kernel moderno de Linux.

---

## Ejercicio 1:

En este ejercicio se analizaron los procesos y servicios básicos que ofrece el sistema operativo Linux. Se trabajó principalmente con comandos de la terminal para observar el estado del sistema, destacando el uso de herramientas como `top`, que permite visualizar los procesos activos y su consumo de recursos. A través de este comando se identificó el proceso con identificador 1 (PID 1).

### Programas

1. **Ejercicio1_Hello.c**: Programa simple que imprime "Hello World" y su PID.
2. **Ejercicio2_Fork.c**: Programa que demuestra el uso de `fork()` y `execl()` para crear procesos hijo.

### Compilación

```bash
cd Ejercicio1
gcc Ejercicio1_Hello.c -o Ejercicio1_Hello
gcc Ejercicio2_Fork.c -o Ejercicio2_Fork
```

### Ejecución

**Programa Hello World:**
```bash
./Ejercicio1_Hello
```
Salida esperada: Imprime "Hello World!" seguido del PID del proceso.

**Programa Fork:**
```bash
./Ejercicio2_Fork
```
Salida esperada: Se crean dos procesos (padre e hijo), cada uno ejecuta `Ejercicio1_Hello` y muestra su PID correspondiente.

---

## Ejercicio 2: 

El segundo ejercicio se enfocó en el análisis de las llamadas al sistema (syscalls), que son el mecanismo mediante el cual los programas en espacio de usuario solicitan servicios al kernel.

Para ello se utilizó la herramienta `strace`, que permite observar en tiempo real las llamadas al sistema realizadas por un proceso. A partir de la ejecución y análisis de `strace`, se identificaron distintos servicios provistos por el sistema operativo, tales como:

* **Gestión de archivos**: llamadas como `open`, `read`, `write` y `close`.
* **Gestión de procesos**: llamadas relacionadas con la creación y control de procesos.
* **Comunicación con el kernel**: operaciones internas que el sistema realiza automáticamente para ejecutar programas.

### Programa

**Ejercicio2_Copiar.c**: Programa que copia el contenido de un archivo a otro utilizando llamadas al sistema de bajo nivel (`open`, `read`, `write`, `close`).

### Compilación

```bash
cd Ejercicio2
gcc Ejercicio2_Copiar.c -o Ejercicio2_Copiar
```

### Ejecución

**Copia básica:**
```bash
./Ejercicio2_Copiar origen.txt destino.txt
```

**Análisis con strace:**
```bash
strace ./Ejercicio2_Copiar origen.txt destino.txt
```

Con `strace` se pueden observar todas las llamadas al sistema que realiza el programa, como:
- `open()`: para abrir archivos
- `read()`: para leer del archivo origen
- `write()`: para escribir al archivo destino
- `close()`: para cerrar los descriptores de archivo

---

## Ejercicio 3: 

En el tercer ejercicio se realizó la parte más avanzada del laboratorio: la modificación y recompilación de un kernel Linux moderno (versión 6.x).

Debido a que la guía original estaba basada en kernels antiguos (2.6.x), fue necesario adaptar el procedimiento a la arquitectura actual. Se comenzó asegurando el entorno mediante un snapshot de la máquina virtual. Posteriormente, se descargó el código fuente del kernel y se configuró el entorno de compilación instalando las dependencias necesarias.

Durante el proceso se ajustaron configuraciones de seguridad del kernel (claves de confianza, firmas y opciones de depuración) para permitir la compilación en Ubuntu moderno. Una vez compilado e instalado el kernel, se reinició el sistema y se seleccionó el nuevo kernel desde el gestor de arranque.

### Programas

1. **mycall.c**: Implementación de una syscall personalizada en el kernel que recibe un entero, lo imprime en el log del kernel y devuelve el valor + 10.
2. **prueba.c**: Programa de espacio de usuario que invoca la syscall personalizada.

### Pasos resumidos para implementar la syscall personalizada

#### 1. Preparación del entorno

```bash
# Instalar dependencias necesarias
sudo apt-get update
sudo apt-get install build-essential libncurses-dev bison flex libssl-dev libelf-dev

# Descargar código fuente del kernel
cd /usr/src
sudo wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.x.tar.xz
sudo tar -xvf linux-6.x.tar.xz
cd linux-6.x
```

#### 2. Agregar la syscall al kernel

**Editar el archivo de syscalls:**
```bash
sudo nano arch/x86/entry/syscalls/syscall_64.tbl
```

Agregar al final:
```
470    common  mycall          sys_mycall
```

**Agregar el prototipo:**
```bash
sudo nano include/linux/syscalls.h
```

Agregar antes del `#endif`:
```c
asmlinkage long sys_mycall(int i);
```

**Copiar mycall.c al kernel:**
```bash
sudo cp /ruta/a/Ejercicio3/mycall.c kernel/
```

**Modificar el Makefile:**
```bash
sudo nano kernel/Makefile
```

Agregar `mycall.o` a la línea de `obj-y`.

#### 3. Compilar e instalar el kernel

```bash
# Configurar el kernel
sudo make menuconfig
# (Desactivar opciones de firma y certificados si es necesario)

# Compilar (puede tardar varias horas)
sudo make -j$(nproc)
sudo make modules_install
sudo make install

# Actualizar GRUB
sudo update-grub

# Reiniciar y seleccionar el nuevo kernel
sudo reboot
```

#### 4. Compilación del programa de prueba

```bash
cd Ejercicio3
gcc prueba.c -o prueba
```

#### 5. Ejecución

```bash
./prueba
```

Salida esperada en consola:
```
Resultado devuelto por kernel: 60
```

Para verificar el mensaje del kernel:
```bash
dmesg | tail
```

Debe aparecer:
```
Hola desde el Kernel! Recibi: 50
```



---

