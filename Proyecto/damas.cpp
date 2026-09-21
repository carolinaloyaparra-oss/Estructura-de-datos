#include <iostream>
#include <vector>
using namespace std;

char tablero[8][8];
vector<string> historial;

void mostrar() {
    cout << "\n    A B C D E F G H\n";
    for (int f = 0; f < 8; f++) {
        cout << f + 1 << "  ";
        for (int c = 0; c < 8; c++) {
            char pieza = tablero[f][c];
            if (pieza == 'x') cout << "\033[31m" << "x" << "\033[0m ";
            else if (pieza == 'o') cout << "\033[34m" << "o" << "\033[0m ";
            else if (pieza == '.') cout << "\033[37m" << "." << "\033[0m ";
            else cout << "  ";
        }
        cout << "\n";
    }
}

void mostrarHistorial() {
    cout << "Historial de jugadas:\n";
    for (size_t i = 0; i < historial.size(); i++) {
        cout << i + 1 << ". " << historial[i] << "\n";
    }
}

int main() {
    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            if ((f + c) % 2 != 0) {
                if (f < 3) tablero[f][c] = 'x';
                else if (f > 4) tablero[f][c] = 'o';
                else tablero[f][c] = '.';
            } else tablero[f][c] = ' ';
        }
    }

    char turno = 'x';

    while (true) {
        mostrar();
        cout << "\nTurno del Jugador [" << turno << "]\n";
        
        int f;
        char col;
        cout << "Fila (1-8) y Columna (A-H) de la ficha a mover: ";
        cin >> f >> col;

        f = f - 1;
        int c = col - 'A';

        if (tablero[f][c] != turno) {
            cout << "¡Esa no es tu ficha!\n";
            continue;
        }

        int dir = (turno == 'x') ? 1 : -1;
        char enemigo = (turno == 'x') ? 'o' : 'x';

        bool puedeIzq = false, puedeDer = false;
        bool comerIzq = false, comerDer = false;

        if (c - 1 >= 0 && f + dir >= 0 && f + dir < 8) {
            if (tablero[f + dir][c - 1] == '.') puedeIzq = true;
            else if (tablero[f + dir][c - 1] == enemigo && 
                     f + 2*dir >= 0 && f + 2*dir < 8 && c - 2 >= 0 &&
                     tablero[f + 2*dir][c - 2] == '.') {
                puedeIzq = true;
                comerIzq = true;
            }
        }

        if (c + 1 < 8 && f + dir >= 0 && f + dir < 8) {
            if (tablero[f + dir][c + 1] == '.') puedeDer = true;
            else if (tablero[f + dir][c + 1] == enemigo && 
                     f + 2*dir >= 0 && f + 2*dir < 8 && c + 2 < 8 &&
                     tablero[f + 2*dir][c + 2] == '.') {
                puedeDer = true;
                comerDer = true;
            }
        }

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

        string jugada;

        if (opcion == 1 && puedeIzq) {
            int salto = comerIzq ? 2 : 1;
            tablero[f + dir * salto][c - salto] = turno;
            tablero[f][c] = '.';
            if (comerIzq) tablero[f + dir][c - 1] = '.';
            jugada = string("Jugador ") + turno + ": " + col + to_string(f+1) + " ___ " + 
                     char('A' + (c - salto)) + to_string(f + dir*salto + 1);
            historial.push_back(jugada);
            turno = (turno == 'x') ? 'o' : 'x';
        } 
        else if (opcion == 2 && puedeDer) {
            int salto = comerDer ? 2 : 1;
            tablero[f + dir * salto][c + salto] = turno;
            tablero[f][c] = '.';
            if (comerDer) tablero[f + dir][c + 1] = '.';
            jugada = string("Jugador ") + turno + ": " + col + to_string(f+1) + " ___ " + 
                     char('A' + (c + salto)) + to_string(f + dir*salto + 1);
            historial.push_back(jugada);
            turno = (turno == 'x') ? 'o' : 'x';
        } 
        else {
            cout << "¡Opción inválida!\n";
        }
        mostrarHistorial();
    }

    return 0;
}