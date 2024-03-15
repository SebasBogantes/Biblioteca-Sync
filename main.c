//Estudiantes:
//Sebastián Bogantes - 2020028437
//Fernando González - 2021075114
//Emmanuel López - 2018077125

//Pruebas de las estructuras de sincronizacion

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "sync.h"

#define NUM_THREADS 10  //Numero de hilos a crear

//Variables globales
Semaphore sem;
Barrier bar;
Monitor mon;

//Funcion del semaforo
void *semaphore_thread(void *arg) {
    printf("Hilo %ld esperando para entrar en la seccion critica (semaforo)...\n", (long)arg);
    semaphore_wait(&sem);  //El hilo espera hasta que pueda entrar en la region critica
    printf("Hilo %ld esta dentro la seccion critica (semaforo).\n", (long)arg);
    sleep(1);
    printf("Hilo %ld salio de la sección critica (semaforo).\n", (long)arg);
    semaphore_signal(&sem);  //El hilo sale de la region critica y manda señal a los otros hilos
    return NULL;
}

//Funcion de la barrera
void *barrier_thread(void *arg) {
    printf("Hilo %ld esperando en la barrera...\n", (long)arg);
    barrier_wait(&bar);
    printf("Hilo %ld ha pasado la barrera.\n", (long)arg);
    return NULL;
}

//Funcion del monitor
void *monitor_thread(void *arg) {
    printf("Hilo %ld intentando entrar en el monitor...\n", (long)arg);
    monitor_enter(&mon);  //Acceso exclusivo del hilo al monitor
    printf("Hilo %ld ha entrado en el monitor.\n", (long)arg);
    sleep(1);
    printf("Hilo %ld esta saliendo del monitor.\n", (long)arg);
    monitor_exit(&mon);  //El hilo sale del monitor y libera el acceso exclusivo
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    //printf("PID: %d\n", getpid());

    semaphore_init(&sem, 3);
    barrier_init(&bar, NUM_THREADS);
    monitor_init(&mon);

    //Hilos para el semaforo
    printf("[Hilos que utilizan el semaforo]\n");
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, semaphore_thread, (void *)i);
    }
    //Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    //Hilos para la barrera
    printf("[Hilos que utilizan la barrera]\n");
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, barrier_thread, (void *)i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    //Hilos para el monitor
    printf("[Hilos que utilizan el monitor]\n");
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, monitor_thread, (void *)i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
    // last test..
}

