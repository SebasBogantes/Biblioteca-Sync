Repositorio del Grupo 3 del curso de Sistemas Operativos del Instituto Tecnológico Costa Rica

## Descripción Biblioteca-Sync
Biblioteca de sincronización personalizada (usando PThreads) hecha en lenguaje C, en esta biblioteca se encuentras herramientas para preveer condiciones de carrera como un semáforo, un monitor y una barrera

## Pre-requisitos
- Esta biblioteca funciona con la librería incorporada de PThreads, en un entorno Linux
- Instalación del compilador de C gcc
  ```bash
  sudo dnf install gcc
  ```

## Implementación
### Semáforos (`sync.h` y `sync.c`)

Los semáforos se implementan mediante una estructura `Semaphore` que contiene un valor entero (`value`), un mutex (`mutex`) y una variable de condición (`cond`). La función `semaphore_init` inicializa el semáforo con un valor dado. Las funciones `semaphore_wait` y `semaphore_signal` se utilizan para decrementar e incrementar el valor del semáforo, respectivamente, bloqueando el hilo si el semáforo tiene un valor de cero o negativo.

### Barreras (`sync.h` y `sync.c`)

Las barreras se implementan mediante una estructura `Barrier` que contiene un contador (`count`), un número de hilos en espera (`waiting`), un mutex (`mutex`) y una variable de condición (`cond`). La función `barrier_init` inicializa la barrera con un número específico de hilos. La función `barrier_wait` permite a los hilos esperar hasta que todos hayan alcanzado la barrera.

### Monitores (`sync.h` y `sync.c`)

Los monitores se implementan mediante una estructura `Monitor` que contiene un mutex (`mutex`) y una variable de condición (`cond`). La función `monitor_init` inicializa el monitor. Las funciones `monitor_enter` y `monitor_exit` se utilizan para controlar el acceso exclusivo a una sección crítica. Las funciones `monitor_wait`, `monitor_notify` y `monitor_notify_all` se utilizan para la sincronización de condiciones dentro del monitor.

## Uso de la Biblioteca
Para utilizar la biblioteca he de considerar los siguientes pasos:

1. Incluir el include del archivo `sync.h` en el archivo de pruebas `main.c`.
   ```c
   #include "sync.h"
   ```

2. Inicializar las estructuras de sincronización (semáforos, barreras o monitores) utilizando las funciones correspondientes (`semaphore_init`, `barrier_init`, `monitor_init`).

3. Llevar a cabo la sincronización de hilos.
- Semáforo
   ```c
   Semaphore sem;
   semaphore_init(&sem, 1);

   semaphore_wait(&sem);
   // Sección crítica
   semaphore_signal(&sem);
   ```
   
- Barrera
  ```c
  #define NUM_THREADS 5
  
  Barrier bar;
  barrier_init(&bar, NUM_THREADS);
  ```
  
- Monitor
  ```c
  Monitor mon;
  monitor_init(&mon);
  ```
  
## Compilación
Esta biblioteca debe de compilarse en el entorno de desarrollo de Linux con los siguientes los siguientes pasos:
1. Abra una terminal en la dirección de la carpeta en donde se encuentran los archivos descargados.
2. Después, ejecute los siguientes comandos en terminal:
   ```bash
   gcc -c sync.c -o sync.o -pthread
   ```
   ```bash
   gcc main.c sync.o -o main -pthread
   ```
   ```bash
   ./main
   ```
