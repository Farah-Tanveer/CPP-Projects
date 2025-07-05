#include<iostream>
using namespace std;

int currentPlayer;
char currentMarker;
char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n";
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if(board[row][col] != 'X' && board[row][col] != '0') {
        board[row][col] = currentMarker;  
        return true;
    }
    return false;
}

int winner() {
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return currentPlayer;
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return currentPlayer;
    }

    // Diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return currentPlayer;

    if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return currentPlayer;

    return 0;
}

void swapPlayerAndMarker() {
    if(currentMarker == 'X')
        currentMarker = '0';
    else
        currentMarker = 'X';

    if(currentPlayer == 1)
        currentPlayer = 2;
    else
        currentPlayer = 1;
}

void game() {
    cout << "Player 1, choose your marker (X or 0): ";
    char markerP1;
    cin >> markerP1;

    while(markerP1 != 'X' && markerP1 != '0') {
        cout << "Invalid marker. Choose X or 0: ";
        cin >> markerP1;
    }

    char markerP2 = (markerP1 == 'X') ? '0' : 'X';

    currentPlayer = 1;
    currentMarker = markerP1;

    drawBoard();
    int playerWon;

    for(int i = 0; i < 9; i++) {
        cout << "Player " << currentPlayer << ", enter your slot: ";
        int slot;
        cin >> slot;

        if(slot < 1 || slot > 9) {
            cout << "Invalid slot. Try again!\n";
            i--;
            continue;
        }

        if(!placeMarker(slot)) {
            cout << "Slot already occupied. Try again!\n";
            i--;
            continue;
        }

        drawBoard();

        playerWon = winner();
        if(playerWon == 1 || playerWon == 2) {
            cout << "Player " << playerWon << " wins!\n";
            
            return;
        }

        swapPlayerAndMarker();
    }

    cout << "It's a tie!\n";
}

int main() {
    game();
    cout<<"Developed by: Farah Tanveer";
    return 0;
}
