#include <iostream>
#include <vector>
using namespace std;

/*
 *Calcula la diversidad de un subconjunto
 *La función recorre todos los pares de elementos del vector 'seleccionados' y
 *acumula la suma de sus distancias.
 *Devuelve un entero, que sería el total de las distancias.
*/ 

int calcularDiversidad(const vector<int>& seleccionados, int** distancias) {
    int suma = 0; //entero que representa la diversidad total
    for (size_t i = 0; i < seleccionados.size(); ++i) {
        //Se suman ambas direcciones de la distancia
        for (size_t j = i + 1; j < seleccionados.size(); ++j) {
            suma += distancias[seleccionados[i]][seleccionados[j]] +
                distancias[seleccionados[j]][seleccionados[i]];
        }
    }
    return suma;
}

/*
 *Elige el candidato con más ganancia
 *Dado el conjunto soluciones S y el conjunto de candidatos C, la función
 *determina que cancidato es
 *mejor sumando la ganancia de añadirlo a S
 *Devuelve el mejor candidato.
*/ 

int seleccionar(const vector<int>& S, const vector<int>& C, int** distancias) {
    int mejorCandidato = -1; //entero que representa el mejor candidato
    int mejorGanancia = -1; //entero que representa la mejor ganancia

    for (int candidato : C) {
        int ganancia = 0; //ganancia del candidato seleccionado
        for (int s : S) {
            ganancia += distancias[candidato][s] + distancias[s][candidato];
        }

        if (ganancia > mejorGanancia) {
            mejorGanancia = ganancia;
            mejorCandidato = candidato;
        }
    }

    return mejorCandidato;
}

/*
 *Determina si es factible seguir agregando elementos
 *La función devuelve verdadero si el numero de elementos de S es menor que m y
 *falso si es mayor
*/ 
// Función factible: true si no se ha alcanzado el tamaño m
bool factible(const vector<int>& S, int m) {
    return S.size() < (size_t)m;
}

/*Función Avance rápido
 *A partir de un elemento de inicio, se construye la solución S agregando en
 *cada iteración el mejor candidato
 *n es el número total de elementos y m el número de elementos a seleccionar
 *'distancias' contiene las distancias entre cada par de elementos
 *'inicio' es el elemento inicial
*/ 
vector<int> voraz(int n, int m, int** distancias, int inicio) {
    vector<int> C; // conjunto de candidatos
    for (int i = 0; i < n; ++i) {
        if (i != inicio)
            C.push_back(i);
    }

    vector<int> S = {inicio}; // solución inicial con el elemento de inicio
    vector<bool> enSolucion(n, false); //vector booleano
    enSolucion[inicio] = true;

    while (!C.empty() && factible(S, m)) {
        int x = seleccionar(S, C, distancias); // seleccionar candidato

        // Construir nuevo conjunto de candidatos sin x 
        vector<int> nuevoC;
        for (int c : C) {
            if (c != x) nuevoC.push_back(c);
        }
        C = nuevoC;

        // Insertar si es factible
        if (factible(S, m)) {
            S.push_back(x);
            enSolucion[x] = true;
        }
    }

    // Convertir solución a vector de 0 y 1
    vector<int> resultado(n);
    for (int i = 0; i < n; ++i)
        resultado[i] = enSolucion[i] ? 1 : 0;
    return resultado;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        
        // Reservar espacio para la matriz de distancias
        int** distancias = new int*[n];
        for (int i = 0; i < n; ++i)
            distancias[i] = new int[n];

        //Lectura de matriz
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> distancias[i][j];

        int mejorDiversidad = -1;
        vector<int> mejorSeleccion;

        //evaluar el algoritmo para cada posible elemento de inicio
        for (int i = 0; i < n; ++i) {
            vector<int> seleccion = voraz(n, m, distancias, i);

            //extraer índices de elementos seleccionados
            vector<int> seleccionados;
            for (int j = 0; j < n; ++j)
                if (seleccion[j]) seleccionados.push_back(j);

            //calcular diversiad
            int diversidad = calcularDiversidad(seleccionados, distancias);

            //seleccionar mejor solución
            if (diversidad > mejorDiversidad) {
                mejorDiversidad = diversidad;
                mejorSeleccion = seleccion;
            }
        }

        //imprimir resultado
        cout << mejorDiversidad << endl;
        for (int bit : mejorSeleccion)
            cout << bit << " ";
        cout << endl;

        //liberar memoria
        for (int i = 0; i < n; ++i)
            delete[] distancias[i];
        delete[] distancias;
    }

    return 0;
}

