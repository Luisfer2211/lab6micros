#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

// Estructura para pasar parámetros a la función de los hilos
struct FibonacciParams {
    int maxNumber;          // El número máximo ingresado por el usuario
    vector<int> fibonacci;  // Vector que almacenará los números de Fibonacci
};

// Función para calcular la serie de Fibonacci
void* calculateFibonacci(void* params) {
    FibonacciParams* fibParams = (FibonacciParams*)params;
    int a = 0, b = 1, next = 0;

    fibParams->fibonacci.push_back(a); // Primer número de Fibonacci: 0
    if (fibParams->maxNumber == 0) {
        pthread_exit(nullptr);
    }

    fibParams->fibonacci.push_back(b); // Segundo número de Fibonacci: 1
    next = a + b;

    while (next <= fibParams->maxNumber) {
        fibParams->fibonacci.push_back(next);
        a = b;
        b = next;
        next = a + b;
    }

    pthread_exit(nullptr);
}

int main() {
    int maxNumber;
    
    // Pedir al usuario un número entre 0 y 100
    do {
        cout << "Ingrese un numero entre 0 y 100: ";
        cin >> maxNumber;
        if (maxNumber < 0 || maxNumber > 100) {
            cout << "Numero fuera de rango. Intente de nuevo." << endl;
        }
    } while (maxNumber < 0 || maxNumber > 100);

    // Crear y configurar los parámetros para los hilos
    FibonacciParams fibParams;
    fibParams.maxNumber = maxNumber;

    // Crear el hilo
    pthread_t fibThread;
    pthread_create(&fibThread, nullptr, calculateFibonacci, (void*)&fibParams);

    // Esperar a que el hilo termine su ejecución
    pthread_join(fibThread, nullptr);

    // Imprimir los resultados
    int sum = 0;
    cout << "Numeros de Fibonacci entre 0 y " << maxNumber << ":" << endl;
    for (size_t i = 0; i < fibParams.fibonacci.size(); ++i) {
        cout << "F" << i << " = " << fibParams.fibonacci[i] << endl;
        sum += fibParams.fibonacci[i];
    }

    // Imprimir la suma total
    cout << "Suma total de los numeros de Fibonacci: " << sum << endl;

    return 0; 
}
