#include <iostream>
#include <cmath>

using namespace std;

char tablero[8][8];

void mostrar() {
    cout << "\n  0 1 2 3 4 5 6 7\n";
    for (int f = 0; f < 8; f++) {
        cout << f << " ";
        for (int c = 0; c < 8; c++) cout << tablero[f][c] << " ";
        cout << "\n";
    }
}

int main() {
    // 1. Colocar fichas iniciales
    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            if ((f + c) % 2 != 0) {
                if (f < 3) tablero[f][c] = 'x';      // Jugador 1
                else if (f > 4) tablero[f][c] = 'o'; // Jugador 2
                else tablero[f][c] = '.';            // Casilla vacia
            } else tablero[f][c] = ' ';
        }
    }

    char turno = 'x';

    while (true) {
        mostrar();
        cout << "\nTurno del Jugador [" << turno << "]\n";
        
        int f, c;
        cout << "Fila y Columna de la ficha a mover: ";
        cin >> f >> c;

        // Validar que la ficha sea del jugador actual
        if (tablero[f][c] != turno) {
            cout << "¡Esa no es tu ficha!\n";
            continue;
        }

        int dir = (turno == 'x') ? 1 : -1; // 'x' baja (+1), 'o' sube (-1)
        char enemigo = (turno == 'x') ? 'o' : 'x';

        // Comprobar opciones a la Izquierda (c - 1) y Derecha (c + 1)
        bool puedeIzq = false, puedeDer = false;
        bool comerIzq = false, comerDer = false;

        // Opción Izquierda
        if (c - 1 >= 0) {
            if (tablero[f + dir][c - 1] == '.') puedeIzq = true;
            else if (tablero[f + dir][c - 1] == enemigo && tablero[f + 2*dir][c - 2] == '.') {
                puedeIzq = true;
                comerIzq = true;
            }
        }

        // Opción Derecha
        if (c + 1 < 8) {
            if (tablero[f + dir][c + 1] == '.') puedeDer = true;
            else if (tablero[f + dir][c + 1] == enemigo && tablero[f + 2*dir][c + 2] == '.') {
                puedeDer = true;
                comerDer = true;
            }
        }

        // Mostrar opciones al usuario
        if (!puedeIzq && !puedeDer) {
            cout << "¡Esta ficha no se puede mover!\n";
            continue;
        }

        cout << "¿Hacia donde mover?\n";
        if (puedeIzq) cout << "  1) Izquierda " << (comerIzq ? "(Comer)" : "") << "\n";
        if (puedeDer) cout << "  2) Derecha " << (comerDer ? "(Comer)" : "") << "\n";
        
        int opcion;
        cout << "Elige (1 o 2): ";
        cin >> opcion;

        // Aplicar movimiento
        if (opcion == 1 && puedeIzq) {
            int salto = comerIzq ? 2 : 1;
            tablero[f + dir * salto][c - salto] = turno;
            tablero[f][c] = '.';
            if (comerIzq) tablero[f + dir][c - 1] = '.'; // Borra la comidad
            turno = (turno == 'x') ? 'o' : 'x'; // Cambia turno
        } 
        else if (opcion == 2 && puedeDer) {
            int salto = comerDer ? 2 : 1;
            tablero[f + dir * salto][c + salto] = turno;
            tablero[f][c] = '.';
            if (comerDer) tablero[f + dir][c + 1] = '.'; // Borra la comida
            turno = (turno == 'x') ? 'o' : 'x'; // Cambia turno
        } 
        else {
            cout << "¡Opcion invalida!\n";
        }
    }

    return 0;
}