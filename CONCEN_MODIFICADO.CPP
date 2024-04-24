#include <iostream>   // cout, cin
#include <vector>     // vector
#include <cstdlib>    // srand, rand
#include <ctime>      // time
#include <algorithm>  // shuffle
#include <unistd.h>   // usleep

using namespace std;

const int MAX_SIZE = 10;

// Estructura para representar una carta en el tablero
struct Card {
    char symbol;
    bool flipped;
};

// Funciones
void clearBoard(vector<vector<Card>> &board);
void initializeSymbols(vector<char> &symbols, int size);
void shuffleSymbols(vector<char> &symbols);
void initializeBoard(vector<vector<Card>> &board, int size, const vector<char> &symbols);
void displayBoard(const vector<vector<Card>> &board);
bool chooseCard(const vector<vector<Card>> &board, int &row, int &col);
void flipCard(vector<vector<Card>> &board, int row, int col);
bool checkMatch(const vector<vector<Card>> &board, int row1, int col1, int row2, int col2);

int main() {
    int size;
    cout << "Ingrese el tamaño del tablero (2-10): ";
    cin >> size;

    if (size < 2 || size > MAX_SIZE) {
        cout << "Tamaño de tablero inválido. Debe estar entre 2 y 10." << endl;
        return 1;
    }

    vector<vector<Card>> board(size, vector<Card>(size));
    clearBoard(board);

    vector<char> symbols(size * size / 2);
    initializeSymbols(symbols, size);
    shuffleSymbols(symbols);
    initializeBoard(board, size, symbols);

    displayBoard(board);

    int pairsFound = 0;
    while (pairsFound < size * size / 2) {
        int row1, col1, row2, col2;
        cout << "Elija una carta (fila columna): ";
        if (chooseCard(board, row1, col1)) {
            flipCard(board, row1, col1);
            displayBoard(board);

            cout << "Elija otra carta (fila columna): ";
            if (chooseCard(board, row2, col2)) {
                flipCard(board, row2, col2);
                displayBoard(board);

                if (checkMatch(board, row1, col1, row2, col2)) {
                    cout << "¡Coincidencia encontrada!" << endl;
                    pairsFound++;
                } else {
                    cout << "No coincide. Inténtalo de nuevo." << endl;
                    flipCard(board, row1, col1);
                    flipCard(board, row2, col2);
                }
            } else {
                flipCard(board, row1, col1);
            }
        }
    }

    cout << "¡Felicidades! Has encontrado todos los pares." << endl;

    return 0;
}

// Limpia el tablero
void clearBoard(vector<vector<Card>> &board) {
    for (auto &row : board) {
        for (auto &card : row) {
            card.symbol = ' ';
            card.flipped = false;
        }
    }
}

// Inicializa los símbolos en el tablero
void initializeSymbols(vector<char> &symbols, int size) {
    for (int i = 0; i < size * size / 2; ++i) {
        symbols[i] = 'A' + i;
    }
}

// Baraja los símbolos
void shuffleSymbols(vector<char> &symbols) {
    srand(time(nullptr));
    random_shuffle(symbols.begin(), symbols.end());
}

// Inicializa el tablero con los símbolos barajados
void initializeBoard(vector<vector<Card>> &board, int size, const vector<char> &symbols) {
    int symbolIndex = 0;
    for (auto &row : board) {
        for (auto &card : row) {
            card.symbol = symbols[symbolIndex++];
        }
    }
}

// Muestra el tablero en la consola
void displayBoard(const vector<vector<Card>> &board) {
    system("clear");  // Cambiar a "cls" en Windows
    for (const auto &row : board) {
        for (const auto &card : row) {
            if (card.flipped) {
                cout << card.symbol << " ";
            } else {
                cout << "* ";
            }
        }
        cout << endl;
    }
}

// El jugador elige una carta
bool chooseCard(const vector<vector<Card>> &board, int &row, int &col) {
    cin >> row >> col;
    row--;  // Ajustar a base 0
    col--;
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col].flipped) {
        cout << "Posición inválida. Inténtalo de nuevo." << endl;
        return false;
    }
    return true;
}

// Voltea la carta seleccionada
void flipCard(vector<vector<Card>> &board, int row, int col) {
    board[row][col].flipped = !board[row][col].flipped;
}

// Verifica si hay una coincidencia entre dos cartas
bool checkMatch(const vector<vector<Card>> &board, int row1, int col1, int row2, int col2) {
    return board[row1][col1].symbol == board[row2][col2].symbol;
}
