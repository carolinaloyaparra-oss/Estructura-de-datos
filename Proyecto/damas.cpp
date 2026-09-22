#include <iostream>
#include <vector>
#include <chrono>
#include <conio.h>

using namespace std;

#define TECLA_IZQUIERDA 75
#define TECLA_DERECHA 77
#define TECLA_ENTER 13
#define TECLA_ESC 27

char tablero[8][8];
vector<string> historial;

void mostrar(int cursorFila, int cursorCol) {
    system("cls");
    cout << "\n    A B C D E F G H\n";
    for (int f = 0; f < 8; f++) {
        cout << f + 1 << "  ";
        for (int c = 0; c < 8; c++) {
            bool esCursor = (f == cursorFila && c == cursorCol);
            
            if (esCursor) cout << "[";
            else cout << " ";

            char pieza = tablero[f][c];
            if (pieza == 'x') cout << "\033[31m" << "x" << "\033[0m";
            else if (pieza == 'o') cout << "\033[34m" << "o" << "\033[0m";
            else if (pieza == '.') cout << "\033[37m" << "." << "\033[0m";
            else cout << " ";

            if (esCursor) cout << "]";
            else cout << " ";
        }
        cout << "\n";
    }
}

void mostrarHistorial() {
    cout << "\n--- Historial de jugadas ---\n";
    for (size_t i = 0; i < historial.size(); i++) {
        cout << i + 1 << ". " << historial[i] << "\n";
    }
    cout << "---------------------------\n";
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
    const int TIEMPO_LIMITE = 30;
    int cursorFila = 0, cursorCol = 0;

    while (true) {
        mostrar(cursorFila, cursorCol);
        cout << "\nTurno del Jugador [" << turno << "] (Limite: " << TIEMPO_LIMITE << "s)\n";
        cout << "Usa FLECHA IZQ / DER para recorrer casillas, ENTER para seleccionar, ESC para rendirte.\n";
        mostrarHistorial();

        auto inicio = chrono::steady_clock::now();
        
        int f = -1, c = -1;
        bool seleccionado = false;

        while (!seleccionado) {
            if (_kbhit()) {
                int tecla = _getch();
                if (tecla == 0 || tecla == 224) {
                    tecla = _getch();
                    if (tecla == TECLA_IZQUIERDA) {
                        cursorCol--;
                        if (cursorCol < 0) {
                            cursorCol = 7;
                            cursorFila--;
                            if (cursorFila < 0) cursorFila = 7;
                        }
                    }
                    if (tecla == TECLA_DERECHA) {
                        cursorCol++;
                        if (cursorCol > 7) {
                            cursorCol = 0;
                            cursorFila++;
                            if (cursorFila > 7) cursorFila = 0;
                        }
                    }
                } else if (tecla == TECLA_ENTER) {
                    f = cursorFila;
                    c = cursorCol;
                    seleccionado = true;
                } else if (tecla == TECLA_ESC) {
                    char ganador = (turno == 'x') ? 'o' : 'x';
                    cout << "\n¡El jugador [" << turno << "] se ha rendido! ¡Gana el jugador [" << ganador << "]!\n";
                    return 0;
                }
                mostrar(cursorFila, cursorCol);
                cout << "\nTurno del Jugador [" << turno << "] (Limite: " << TIEMPO_LIMITE << "s)\n";
                cout << "Usa FLECHA IZQ / DER para recorrer casillas, ENTER para seleccionar, ESC para rendirte.\n";
                mostrarHistorial();
            }

            auto actual = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::seconds>(actual - inicio).count() > TIEMPO_LIMITE) {
                cout << "\n¡Tiempo agotado! Se pasa el turno.\n";
                turno = (turno == 'x') ? 'o' : 'x';
                _getch();
                break;
            }
        }

        if (!seleccionado) continue;

        if (tablero[f][c] != turno) {
            cout << "\n¡Selecciona una casilla con una de tus fichas!\n";
            _getch();
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
            cout << "\n¡Esta ficha no tiene movimientos disponibles!\n";
            _getch();
            continue;
        }

        cout << "\n¿Hacia donde mover?\n";
        if (puedeIzq) cout << "  FLECHA IZQUIERDA " << (comerIzq ? "(Comer)" : "") << "\n";
        if (puedeDer) cout << "  FLECHA DERECHA " << (comerDer ? "(Comer)" : "") << "\n";
        cout << "  ESC) Rendirse\n";
        
        bool movido = false;
        while (!movido) {
            int tecla = _getch();
            if (tecla == 0 || tecla == 224) {
                tecla = _getch();
                if (tecla == TECLA_IZQUIERDA && puedeIzq) {
                    int salto = comerIzq ? 2 : 1;
                    tablero[f + dir * salto][c - salto] = turno;
                    tablero[f][c] = '.';
                    if (comerIzq) tablero[f + dir][c - 1] = '.';
                    
                    string jugada = string("Jugador ") + turno + ": " + char('A' + c) + to_string(f+1) + " -> " + 
                             char('A' + (c - salto)) + to_string(f + dir*salto + 1);
                    historial.push_back(jugada);
                    turno = (turno == 'x') ? 'o' : 'x';
                    movido = true;
                } 
                else if (tecla == TECLA_DERECHA && puedeDer) {
                    int salto = comerDer ? 2 : 1;
                    tablero[f + dir * salto][c + salto] = turno;
                    tablero[f][c] = '.';
                    if (comerDer) tablero[f + dir][c + 1] = '.';
                    
                    string jugada = string("Jugador ") + turno + ": " + char('A' + c) + to_string(f+1) + " -> " + 
                             char('A' + (c + salto)) + to_string(f + dir*salto + 1);
                    historial.push_back(jugada);
                    turno = (turno == 'x') ? 'o' : 'x';
                    movido = true;
                }
            } else if (tecla == TECLA_ESC) {
                char ganador = (turno == 'x') ? 'o' : 'x';
                cout << "\n¡El jugador [" << turno << "] se ha rendido! ¡Gana el jugador [" << ganador << "]!\n";
                return 0;
            }
        }
    }

    return 0;
}