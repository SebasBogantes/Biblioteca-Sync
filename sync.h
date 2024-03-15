//Estudiantes:
//Sebastián Bogantes - 2020028437
//Fernando González - 2021075114
//Emmanuel López - 2018077125

//Biblioteca de las diferentes estructuras de sincronizacion

#ifndef SYNC_H
#define SYNC_H

#include <pthread.h>

//Estructura del semaforo
typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;         //Condicional para bloquear o despertar hilos
} Semaphore;

//Estructura de la barrera
typedef struct {
    int count;
    int waiting;                 //Numeros de hilos en espera
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Barrier;

//Estructura del monitor
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Monitor;

//Funciones del semaforo
void semaphore_init(Semaphore *s, int value);
void semaphore_wait(Semaphore *s);
void semaphore_signal(Semaphore *s);

//Funciones de la barrera
void barrier_init(Barrier *b, int count);
void barrier_wait(Barrier *b);

//Funciones del monitor
void monitor_init(Monitor *m);
void monitor_enter(Monitor *m);
void monitor_exit(Monitor *m);
void monitor_wait(Monitor *m);
void monitor_notify(Monitor *m);
void monitor_notify_all(Monitor *m);

#endif

// last test..

