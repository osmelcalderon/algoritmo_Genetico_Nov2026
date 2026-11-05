#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

double fitness(double x) {
    return abs(50 - x);
}

double randomDouble(double min, double max) {
    return min + (rand() / (double)RAND_MAX) * (max - min);
}

int main() {
    srand(time(0));

    double poblacion[4] = {10, 80, 25, 60};

    int gen = 0;

    while (true) {

        cout << "\nGeneracion " << gen << endl;

        // Mostrar población
        for (int i = 0; i < 4; i++) {
            cout << poblacion[i] << " ";
        }
        cout << endl;

        // Buscar los 2 mejores
        int mejor1 = 0, mejor2 = 1;

        for (int i = 0; i < 4; i++) {
            if (fitness(poblacion[i]) < fitness(poblacion[mejor1]))
                mejor1 = i;
        }

        for (int i = 0; i < 4; i++) {
            if (i != mejor1 &&
                fitness(poblacion[i]) < fitness(poblacion[mejor2]))
                mejor2 = i;
        }

        double p1 = poblacion[mejor1];
        double p2 = poblacion[mejor2];

        // Si ya encontramos 50 exacto → salir
        if (p1 == 50 || p2 == 50) {
            cout << "\nEncontrado 50!" << endl;
            break;
        }

        // Cruce (promedio)
        double hijo = (p1 + p2) / 2.0;

        // 🔥 Mutación INTELIGENTE (clave)
        double delta = randomDouble(-2, 2); // pequeño ajuste
        hijo = hijo + delta;

        // 🔥 Redondeo (esto hace posible llegar EXACTO a 50)
        hijo = round(hijo);

        cout << "Padres: " << p1 << " y " << p2 << endl;
        cout << "Hijo: " << hijo << endl;

        // Nueva población (sin ruido innecesario)
        poblacion[0] = p1;
        poblacion[1] = p2;
        poblacion[2] = hijo;
        poblacion[3] = hijo + randomDouble(-1,1); // ligera variación

        gen++;
    }

    return 0;
}

/*


#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función fitness: qué tan cerca está de 50
double fitness(double x) {
    return abs(50 - x);
}

// Genera número aleatorio entre min y max
double randomDouble(double min, double max) {
    return min + (rand() / (double)RAND_MAX) * (max - min);
}

int main() {
    srand(time(0));

    // Población inicial (4 números)
    double poblacion[4] = {10, 80, 25, 60};

    for (int gen = 0; gen < 10; gen++) {
        cout << "\nGeneracion " << gen << endl;

        // Mostrar población
        for (int i = 0; i < 4; i++) {
            cout << "Individuo " << i << ": " << poblacion[i]
                 << " fitness=" << fitness(poblacion[i]) << endl;
        }

        // Selección: encontrar los 2 mejores
        int mejor1 = 0, mejor2 = 1;

         //Encontrar mejor1
        for (int i = 0; i < 4; i++) {
            if (fitness(poblacion[i]) < fitness(poblacion[mejor1]))
                mejor1 = i;
        }

        //Encontrar mejor2
        for (int i = 0; i < 4; i++) {
            if (i != mejor1 &&
                fitness(poblacion[i]) < fitness(poblacion[mejor2]))
                mejor2 = i;
        }

         //Convertir Mejor1 y Mejor2 En padres
        double p1 = poblacion[mejor1];
        double p2 = poblacion[mejor2];

        cout << "Padres: " << p1 << " y " << p2 << endl;

        // 🔀 CRUCE (promedio)
        double hijo = (p1 + p2) / 2.0;

        // ⚡ MUTACIÓN (AQUÍ ESTÁ LO IMPORTANTE)
        double delta = randomDouble(-5, 5);  // 👈 AQUÍ defines el -5 y +5
        hijo = hijo + delta;

        cout << "Hijo antes mutacion: " << (p1 + p2) / 2.0 << endl;
        cout << "Delta (mutacion): " << delta << endl;
        cout << "Hijo final: " << hijo << endl;

        // Nueva población (reemplazo simple)
        poblacion[0] = p1;
        poblacion[1] = p2;
        poblacion[2] = hijo;
        poblacion[3] = randomDouble(0, 100); // nuevo individuo aleatorio
    }

    return 0;
}

*/