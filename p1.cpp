#include <iostream>
using namespace std;

int main() {
    int r = 3, c = 3;
    int TwoDArr[3][3] = { {1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9} };
    int arr[9];
    int k = 0;


    for (int x = 0; x < c; x++) {
        for (int y = 0; y < r; y++) {
            k = x * r + y;
            arr[k] = TwoDArr[y][x];
        }
    }

 
    cout << "Los elementos del array bidimensional son: " << endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << TwoDArr[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nLos elementos del array unidimensional son: " << endl;
    for (int x = 0; x < r * c; x++) {
        cout << arr[x] << " ";
    }
    cout << endl;

    return 0;
}