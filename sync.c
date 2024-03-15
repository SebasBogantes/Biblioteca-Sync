//Estudiantes:
//Sebastián Bogantes - 2020028437
//Fernando González - 2021075114
//Emmanuel López - 2018077125

//Implementacion de las funciones de cada estructura

#include "sync.h"

//Inicialización del semaforo.
void semaphore_init(Semaphore *s, int value) {
    s->value = value;
    pthread_mutex_init(&s->mutex, NULL);
    pthread_cond_init(&s->cond, NULL);
}

//Implementacion de la espera del semaforo
void semaphore_wait(Semaphore *s) {
    pthread_mutex_lock(&s->mutex);  //Bloquea el mutex
    while (s->value <= 0) {  //Si el valor del semaforo es 0 o negativo, el hilo debe esperar
        pthread_cond_wait(&s->cond, &s->mutex);  //Espera en la variable de condicion
    }
    s->value--;
    pthread_mutex_unlock(&s->mutex);  //Desbloquea el mutex
}

//Implementacion de la señalizacion del semaforo
void semaphore_signal(Semaphore *s) {
    pthread_mutex_lock(&s->mutex);
    s->value++;
    pthread_cond_signal(&s->cond);  //Notifica a un hilo en espera que el semaforo ha sido incrementado
    pthread_mutex_unlock(&s->mutex);
}

//Inicializacion de la barrera
void barrier_init(Barrier *b, int count) {
    b->count = count;  //Numero total de hilos que deben alcanzar la barrera
    b->waiting = 0;  //Contador de hilos en espera
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cond, NULL);
}

//Implementacion de la espera en la barrera
void barrier_wait(Barrier *b) {
    pthread_mutex_lock(&b->mutex);
    b->waiting++;
    if (b->waiting == b->count) {
        b->waiting = 0;  //Reinicia el contador
        pthread_cond_broadcast(&b->cond);  //Notifica a todos los hilos que la barrera esta completa
    } else {
        while (pthread_cond_wait(&b->cond, &b->mutex) != 0);  //La variable de condicion espera hasta que la barrera este completa
    }
    pthread_mutex_unlock(&b->mutex);
}

//Inicializacion del monitor
void monitor_init(Monitor *m) {
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->cond, NULL);
}

//Implementacion de entrada al monitor
void monitor_enter(Monitor *m) {
    pthread_mutex_lock(&m->mutex);
}

//Implementacion de salida del monitor
void monitor_exit(Monitor *m) {
    pthread_mutex_unlock(&m->mutex);
}

//Implementacion de espera del monitor
void monitor_wait(Monitor *m) {
    pthread_cond_wait(&m->cond, &m->mutex);
}

//Implementacion de notificacion del monitor
void monitor_notify(Monitor *m) {
    pthread_cond_signal(&m->cond);  //Notifica a un hilo en espera dentro del monitor
}

//Implementacion de notificacion a todos los hilos dentro del monitor
void monitor_notify_all(Monitor *m) {
    pthread_cond_broadcast(&m->cond);
}

// last test..

