#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void generarLaberinto(int filas, int columnas, float densidad) {
    int **matriz;
    matriz = new int *[filas];

    int FParedes = densidad * 8;
    densidad = filas * columnas * densidad / 4;

    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    // Inicializamos la semilla para rand
    srand(time(NULL));

    //valores
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1) {
                matriz[i][j] = 1;
            }
            else {
                matriz[i][j] = 0;
            }
        }
    }

    //laberinto
    for (int i = 0; i < densidad; i++) {
        int x = rand() % (columnas - 4) + 2; // 2 18
        x = (x / 2) * 2;
        int y = rand() % (filas - 4) + 2;
        y = (y / 2) * 2;
        matriz[y][x] = 1;
        for (int j = 0; j < FParedes; j++) {
            int mx[4] = { x,  x,  x + 2, x - 2 };
            int my[4] = { y + 2, y - 2, y,  y };
            int r = rand() % 4;
            if (matriz[my[r]][mx[r]] == 0) {
                matriz[my[r]][mx[r]] = 1;
                matriz[my[r] + (y - my[r]) / 2][mx[r] + (x - mx[r]) / 2] = 1;
            }
        }
    }

    // Posición inicial del jugador
    int jugadorX = 1;
    int jugadorY = 1;
    int jugadorXAnterior = jugadorX;
    int jugadorYAnterior = jugadorY;
    matriz[jugadorY][jugadorX] = 2; // 2 para representar al jugador

    // Mostrar el laberinto inicial
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == 1) {
                cout << char(219) << char(219);
            }
            else if (matriz[i][j] == 0) {
                cout << "  ";
            }
            else if (matriz[i][j] == 2) {
                cout << "O ";
            }
        }
        cout << "\n";
    }

    // Loop del juego
    char movimiento;
    while (true) {
        cout << "Ingresa una dirección (W, A, S, D) o Q para salir: ";
        cin >> movimiento;

        if (movimiento == 'Q' || movimiento == 'q') {
            break;
        }

        // Borrar la posición actual del jugador
        matriz[jugadorY][jugadorX] = 0;

        // Mover al jugador en la dirección especificada
        if (movimiento == 'W' || movimiento == 'w') {
            jugadorY--;
        } else if (movimiento == 'S' || movimiento == 's') {
            jugadorY++;
        } else if (movimiento == 'A' || movimiento == 'a') {
            jugadorX--;
        } else if (movimiento == 'D' || movimiento == 'd') {
            jugadorX++;
        }

        // Verificar si el jugador ha llegado a la salida
        if (jugadorY == filas - 2 && jugadorX == columnas - 2) {
            
            system("cls");

            // Mostrar mensaje y carita
	cout << "\n       x x    ";
	cout << "\n      x   x";                 
	cout << "\n  x   x   x   x";
	cout << "\n    x   x    x";
	cout << "\n      x x  x";
	cout << "\n       x x ";
	cout << "\n        x";
	cout << "\n        x";
    cout << "\n        x";
	cout << "\n       x x";
	cout << "\n      x   x";                 
	cout << "\n     x     x";
	cout << "\n=====================================================================================================================";
    cout << "\n     H     H       A       SSSSSSSSS          GGGGGG           A      NN     NN      A      DDDD      OOOOOOOO";
	cout << "\n     H     H     A   A     SS                G               A   A    NN N   NN    A   A    DD  DD   OO      OO";                 
	cout << "\n     H H H H    A     A    SSSSSSSSS        GG     GGGG     A     A   NN  N  NN   A     A   DD   DD  OO      OO";
	cout << "\n     H     H   AAAAAAAAA          SS        GG       GG    AAAAAAAAA  NN   N NN  AAAAAAAAA  DD  DD   OO      OO";
	cout << "\n     H     H  A         A  SSSSSSSSS           GGGGGGG    A         A NN     NN A         A DDDD      OOOOOOOO";
	cout << "\n========================================================================================================================";
            
            break;
        }

        // Verificar si el movimiento es válido
        if (matriz[jugadorY][jugadorX] == 1) {
            // El jugador no puede moverse a una pared
            jugadorX = jugadorXAnterior;
            jugadorY = jugadorYAnterior;
        }

        // Guardar la posición actual del jugador
        matriz[jugadorY][jugadorX] = 2;

        // Mostrar el estado actual del laberinto
        system("cls"); // Limpiar la pantalla (solo funciona en Windows)
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (matriz[i][j] == 1) {
                    cout << char(219) << char(219);
                } else if (matriz[i][j] == 0) {
                    cout << "  ";
                } else if (matriz[i][j] == 2) {
                    cout << "O ";
                }
            }
            cout << "\n";
        }

        // Guardar la posición anterior del jugador
        jugadorXAnterior = jugadorX;
        jugadorYAnterior = jugadorY;
    }
}

int main() {
	int opc;
	
    do{
    	system ("cls");
        cout << "Laberinto - Menu:" << endl;
        cout << "1. Iniciar juego" << endl;
        cout << "2. Salir del juego" << endl;
        cout << "Selecciona una opción: "<<endl;
        cin >> opc;

        switch (opc) {
            case 1:
            	system ("cls");
                int filas, columnas;
                float densidad;
                cout << "Ingresa el número de filas: ";
                cin >> filas;
                cout << "Ingresa el número de columnas: ";
                cin >> columnas;
                cout << "Ingresa la densidad (entre 0 y 1): ";
                cin >> densidad;
                 system("pause");
                 
                system ("cls");
                generarLaberinto(filas, columnas, densidad);
                system("pause");
                break;
            case 2:
            	system ("cls");
                cout << "Saliendo del programa." << endl;
                cout << "Muchas Gracias por jugar." << endl;
                cout << "\n===========================================================";
 				cout << "\n          A      DDDD    IIIIII  OOOOOOOO   SSSSSSSSS";
 				cout << "\n        A   A    DD  DD    II   OO      OO  SS";
 				cout << "\n       A     A   DD   DD   II   OO      OO  SSSSSSSSS";
 				cout << "\n      AAAAAAAAA  DD  DD    II   OO      OO         SS";
 				cout << "\n     A         A DDDD    IIIIII  OOOOOOOO   SSSSSSSSS"; 
 				cout << "\n==========================================================="<<endl;
                system("pause");
                break;
        }
    }while(opc!=2);
    return 0;
}

