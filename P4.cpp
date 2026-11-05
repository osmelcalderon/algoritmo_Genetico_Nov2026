#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

//https://cpp.sh/
//https://www.programiz.com/cpp-programming/online-compiler/
//https://www.onlinegdb.com/online_c++_compiler
using namespace std;

const int DIAS = 4;
const int HORAS_DIA = 3;
const int TAM = DIAS * HORAS_DIA;
const int POB = 8;

// 🔹 Materias y horas
char materias[] = {'A', 'B', 'C'};
int horas[]     = { 2 ,  7 ,  3 };
const int NUM_MAT = 3;

// 🔥 BASE MANUAL (aunque esté mal)
char base_manual[TAM] = {
    'A','A','B',    // L
    'B','B','B',    // M
    'C','C','C',    // Mi
    'C','C','C'     // J
};

// 🔥 Restricción por hora
int restriccionHoras[NUM_MAT][TAM] = {

            //✔ 1 = permitido ✔ 0 = prohibido
    // A
    { 1,1,0,  0,0,0,  0,0,0,  1,1,1 },

    // B
    { 0,0,1,  1,1,1,  1,1,1,  0,0,0 },

    // C
    { 0,0,0,   1,1,1,  1,1,1,  1,1,1 }
};

// 🔹 Copiar
void copiar(char a[], char b[]) {
    for (int i = 0; i < TAM; i++)
        b[i] = a[i];
}

// 🔹 Mezclar
void mezclar(char ind[]) {
    for (int i = TAM - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char t = ind[i];
        ind[i] = ind[j];
        ind[j] = t;
    }
}

// 🔹 Generar individuo
void generar(char ind[]) {
    copiar(base_manual, ind);
    mezclar(ind);
}

// 🔹 Buscar índice de materia
int idxMateria(char m) {
    for (int i = 0; i < NUM_MAT; i++) {
        if (materias[i] == m)
            return i;
    }
    return -1;
}

// 🔥 FITNESS COMPLETO
int fitnessTotal(char ind[]) {

    int score = 0;

    // 🔹 1. Restricción por hora
    for (int i = 0; i < TAM; i++) {

        int idx = idxMateria(ind[i]);

        if (idx != -1) {
            if (restriccionHoras[idx][i] == 1)
                score += 3;
            else
                score -= 10; // fuerte castigo
        }
    }

    // 🔹 2. Restricción de horas
    int conteo[NUM_MAT] = {0};

    for (int i = 0; i < TAM; i++) {
        int idx = idxMateria(ind[i]);
        if (idx != -1)
            conteo[idx]++;
    }

    for (int i = 0; i < NUM_MAT; i++) {
        if (conteo[i] == horas[i])
            score += 30;
        else
            score -= abs(conteo[i] - horas[i]) * 10;
    }

    return score;
}

// 🔥 CONDICIÓN PERFECTA
bool esPerfecto(char ind[]) {

    // 🔹 horas exactas
    int conteo[NUM_MAT] = {0};

    for (int i = 0; i < TAM; i++) {
        int idx = idxMateria(ind[i]);
        if (idx != -1)
            conteo[idx]++;
    }

    for (int i = 0; i < NUM_MAT; i++) {
        if (conteo[i] != horas[i])
            return false;
    }

    // 🔹 restricciones por hora
    for (int i = 0; i < TAM; i++) {

        int idx = idxMateria(ind[i]);

        if (idx != -1) {
            if (restriccionHoras[idx][i] == 0)
                return false;
        }
    }

    return true;
}

// 🔹 Mutación (importante mejorarla)
void mutar(char ind[]) {
    int pos = rand() % TAM;
    ind[pos] = materias[rand() % NUM_MAT];
}

// 🔹 Imprimir
void imprimir(char ind[]) {
    for (int i = 0; i < TAM; i++) {
        cout << ind[i] << " ";
        if ((i + 1) % HORAS_DIA == 0)
            cout << "| ";
    }
}

// 🔥 MAIN
int main() {

    srand(time(0));

    char poblacion[POB][TAM];

    // 🔹 Inicial
    for (int i = 0; i < POB; i++) {
        generar(poblacion[i]);
    }

    int gen = 0;

    // 🔥 NO PARA hasta solución perfecta
    while (true) {

        int mejor = 0;

        for (int i = 0; i < POB; i++) {
            if (fitnessTotal(poblacion[i]) > fitnessTotal(poblacion[mejor])) {
                mejor = i;
            }
        }

        cout << "Gen " << gen << ": ";
        imprimir(poblacion[mejor]);
        cout << " Fitness: " << fitnessTotal(poblacion[mejor]) << endl;

        // 🔥 condición real completa
        if (esPerfecto(poblacion[mejor])) {
            cout << "\n✅ SOLUCIÓN PERFECTA ENCONTRADA\n";
            imprimir(poblacion[mejor]);
            cout << endl;
            break;
        }

        // 🔹 Evolución (simple)
        for (int i = 0; i < POB; i++) {
            mutar(poblacion[i]);
        }

        gen++;
    }

    return 0;
}