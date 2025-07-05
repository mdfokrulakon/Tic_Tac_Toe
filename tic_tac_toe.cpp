#include <iostream>
using namespace std;

// GLOBAL VARIABLES INITIALIZE
char board[10] = {'0','1','2','3','4','5','6','7','8','9'};
char current_marker;
int scoreX = 0;
int scoreO = 0;
int draws = 0;
bool vsComputer = false;

// DISPLAY THE BOARD
void displayBoard() {
    cout << "\n";
    cout << " " << board[1] << " | " << board[2] << " | " << board[3] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[4] << " | " << board[5] << " | " << board[6] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[7] << " | " << board[8] << " | " << board[9] << "\n\n";
}

// SWITCH PLAYER
void switchPlayer() {
    if (current_marker == 'X') current_marker = 'O';
    else current_marker = 'X';
}

// DISPLAY SCORE
void displayScore() {
    cout << "Scoreboard:\n";
    cout << "Player X: " << scoreX << "\n";
    cout << "Player O: " << scoreO << "\n";
    cout << "Draws   : " << draws << "\n\n";
}

// CHECK WIN
bool checkWin() {
    return (board[1] == board[2] && board[2] == board[3]) ||
           (board[4] == board[5] && board[5] == board[6]) ||
           (board[7] == board[8] && board[8] == board[9]) ||
           (board[1] == board[4] && board[4] == board[7]) ||
           (board[2] == board[5] && board[5] == board[8]) ||
           (board[3] == board[6] && board[6] == board[9]) ||
           (board[1] == board[5] && board[5] == board[9]) ||
           (board[3] == board[5] && board[5] == board[7]);
}

// CHECK DRAW
bool checkDraw() {
    return (board[1] != '1' && board[2] != '2' && board[3] != '3' &&
            board[4] != '4' && board[5] != '5' && board[6] != '6' &&
            board[7] != '7' && board[8] != '8' && board[9] != '9');
}

// MINIMAX ALGORITHM
int minimax(bool isComputer) {
    if (checkWin()) {
        if (isComputer) return -10; // Player won
        else return 10;             // Computer won
    }
    if (checkDraw()) return 0;

    int bestScore = isComputer ? -1000 : 1000;

    for (int i = 1; i <= 9; i++) {
  if (board[i] == '0' + i) {
    char temp = board[i];

    if (isComputer) {
        board[i] = 'O';
    } else {
        board[i] = 'X';
    }

    int score = minimax(!isComputer);
    board[i] = temp;

    if (isComputer && score > bestScore) {
        bestScore = score;
    }
    if (!isComputer && score < bestScore) {
        bestScore = score;
    }
}
  }
    return bestScore;
}

int findBestMove() {
    int bestScore = -1000;
    int move = 0;

    for (int i = 1; i <= 9; i++) {
        if (board[i] == '0' + i) {
            char temp = board[i];
            board[i] = 'O';
            int score = minimax(false);
            board[i] = temp;

            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

void resetGame();

// START GAME
void startGame() {
    int mode;
    cout << "Choose mode:\n1. Player vs Player\n2. Player vs Computer\nEnter choice: ";
    cin >> mode;
    vsComputer = (mode == 2);

    cout << "Choose your marker (X or O): ";
    cin >> current_marker;
    if (current_marker != 'X' && current_marker != 'O') {
        cout << "Invalid marker. Defaulting to X.\n";
        current_marker = 'X';
    }

    displayBoard();

    while (true) {
        int position;

        if (vsComputer && current_marker == 'O') {
            position = findBestMove();
            cout << "Computer chooses position: " << position << "\n";
        } else {
            cout << "Player (" << current_marker << ") - Enter position (1-9): ";
            cin >> position;
        }

        if (position >= 1 && position <= 9 && board[position] == '0' + position) {
            board[position] = current_marker;
        } else {
            cout << "Invalid input or position taken. Try again.\n";
            continue;
        }

        displayBoard();

        if (checkWin()) {
            cout << "Player (" << current_marker << ") wins!\n";
            if (current_marker == 'X') scoreX++;
            else scoreO++;
            displayScore();
            break;
        }

        if (checkDraw()) {
            cout << "It's a draw!\n";
            draws++;
            displayScore();
            break;
        }

        switchPlayer();
    }

    char again;
    cout << "Do you want to play again? (Y/N): ";
    cin >> again;
    if (again == 'Y' || again == 'y') resetGame();
    else return;
}

// RESET GAME
void resetGame() {
    board[1] = '1'; board[2] = '2'; board[3] = '3';
    board[4] = '4'; board[5] = '5'; board[6] = '6';
    board[7] = '7'; board[8] = '8'; board[9] = '9';
    startGame();
}

// MAIN FUNCTION
int main() {
    int option;
    cout << "\n\t========== EAST WEST UNIVERSITY ==========\n";
    cout << "\n\t========== TIC TAC TOE ==========\n";
    cout << "\t\t 1. Start Game\n";
    cout << "\t\t 2. Exit\n";
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1:
            startGame();
            break;
        case 2:
            cout << "Exiting game. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Exiting. You can write again ..\n";
    }

    cout << "Thanks for playing ... come again ...\n";
    return 0;
}
