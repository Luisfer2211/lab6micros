#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *paramID) {
    int *id;
    id = (int *)paramID;
    printf("Hello world thread No. %d\n", *id);
    pthread_exit(NULL);
    return NULL;
}

int main (int argc, char *argv[]) {
    pthread_t threadsID[NUM_THREADS];
    pthread_attr_t attr;  // Atributos del hilo
    int rc, t, param[NUM_THREADS];

    // Inicializar los atributos del hilo
    pthread_attr_init(&attr);

    // Crear hilos en un ciclo for
    for(t = 0; t < NUM_THREADS; t++) {
        printf("Main: creando el thread No. %d\n", t);
        param[t] = t;
        rc = pthread_create(&threadsID[t], &attr, PrintHello, (void *)&param[t]);
        if (rc) {
            printf("ERROR: código de retorno desde pthread_create %d\n", rc);
            exit(-1);
        }
    }

    // Destruir atributos después de usar
    pthread_attr_destroy(&attr);

    // Esperar la finalización de cada hilo
    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threadsID[t], NULL);
    }

    pthread_exit(NULL);  // Finalizar el thread principal
}
