#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// Estructura para pasar parámetros a los hilos
struct ThreadData {
    int n;      // Valor de n en la serie
    double result;  // Resultado parcial de la serie
};

// Función que evalúa el valor de la serie para un n dado
void *compute_term(void *arg) {
    ThreadData *data = (ThreadData *) arg;
    int n = data->n;
    // Cálculo del término de la serie (-1)^(n+1) / n
    data->result = (pow(-1, n + 1)) / (double)n;
    pthread_exit(NULL);
    return NULL;
}

int main() {
    int nMax;
    
    // Pedir al usuario el valor máximo de "n" a evaluar
    cout << "Ingrese el valor maximo de 'n' para la serie: ";
    cin >> nMax;

    // Validación del valor de n
    if (nMax <= 0) {
        cout << "El valor de 'n' debe ser mayor que 0." << endl;
        return 1;
    }

    // Crear un arreglo de hilos y estructuras para almacenar los datos
    pthread_t *threads = new pthread_t[nMax];
    ThreadData *threadData = new ThreadData[nMax];

    // Crear los hilos para calcular cada término de la serie
    for (int i = 1; i <= nMax; i++) {
        threadData[i - 1].n = i;  // Pasar el valor de n al hilo
        int rc = pthread_create(&threads[i - 1], NULL, compute_term, (void *)&threadData[i - 1]);
        if (rc) {
            cout << "Error: no se pudo crear el hilo " << i << ". Codigo de error: " << rc << endl;
            return 1;
        }
    }

    // Esperar a que todos los hilos terminen y acumular los resultados
    double sum = 0.0;
    for (int i = 1; i <= nMax; i++) {
        pthread_join(threads[i - 1], NULL);  // Esperar a que el hilo termine
        sum += threadData[i - 1].result;  // Acumular el resultado del término
    }

    // Imprimir el resultado final de la serie
    cout << "El valor de convergencia de la serie hasta n = " << nMax << " es: " << sum << endl;

    // Liberar la memoria utilizada
    delete[] threads;
    delete[] threadData;

    pthread_exit(NULL);  // Finalizar el hilo principal
    return 0;
}
