#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char board[3][3];
char player, cpu;
int choice, row, col, moves;

// Forward declaration of the minimax function
int minimax(int depth, bool isMaximizing);

void initializeBoard() {
    moves = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

bool isWinning(char mark) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark))
            return true;
    }
    // Check diagonals
    if ((board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark))
        return true;
    return false;
}

bool isDraw() {
    return moves == 9;
}

void playerMove() {
    int move;
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> move;
        move--;  // Convert to 0-based index
        row = move / 3;
        col = move % 3;
        if (move >= 0 && move < 9 && board[row][col] == ' ') {
            board[row][col] = player;
            moves++;
            break;
        } else {
            cout << "Invalid move, try again.\n";
        }
    }
}

void cpuMove(int difficulty) {
    if (difficulty == 1) {
        // Easy: Random move
        while (true) {
            row = rand() % 3;
            col = rand() % 3;
            if (board[row][col] == ' ') {
                board[row][col] = cpu;
                moves++;
                break;
            }
        }
    } else if (difficulty == 2) {
        // Medium: Block or Random
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = cpu;
                    if (isWinning(cpu)) {
                        moves++;
                        return;
                    }
                    board[i][j] = player;
                    if (isWinning(player)) {
                        board[i][j] = cpu;
                        moves++;
                        return;
                    }
                    board[i][j] = ' ';
                }
            }
        }
        cpuMove(1);  // Fallback to easy if no block/win move
    } else {
        // Hard: Minimax algorithm for unbeatable AI
        int bestScore = -1000;
        int bestMoveRow, bestMoveCol;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = cpu;
                    int score = minimax(0, false);
                    board[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                        bestMoveRow = i;
                        bestMoveCol = j;
                    }
                }
            }
        }
        board[bestMoveRow][bestMoveCol] = cpu;
        moves++;
    }
}

int minimax(int depth, bool isMaximizing) {
    if (isWinning(cpu)) return 10 - depth;
    if (isWinning(player)) return depth - 10;
    if (isDraw()) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = cpu;
                    int score = minimax(depth + 1, false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player;
                    int score = minimax(depth + 1, true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

void playGame(int gameMode, int difficulty = 0) {
    initializeBoard();
    bool playerTurn = true;

    while (true) {
        printBoard();
        if (playerTurn) {
            playerMove();
            if (isWinning(player)) {
                printBoard();
                cout << "Player wins!\n";
                break;
            }
        } else {
            if (gameMode == 1) {  // Against CPU
                cpuMove(difficulty);
                if (isWinning(cpu)) {
                    printBoard();
                    cout << "CPU wins!\n";
                    break;
                }
            } else {  // 2 Player mode
                cout << "Player " << (playerTurn ? 1 : 2) << "'s turn\n";
                playerMove();
                if (isWinning(player)) {
                    printBoard();
                    cout << "Player " << (playerTurn ? 1 : 2) << " wins!\n";
                    break;
                }
            }
        }

        if (isDraw()) {
            printBoard();
            cout << "It's a draw!\n";
            break;
        }

        playerTurn = !playerTurn;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    int gameMode, difficulty;

    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Choose Game Mode:\n1. Player vs CPU\n2. 2 Player Mode\n";
    cin >> gameMode;

    if (gameMode == 1) {
        cout << "Choose Difficulty:\n1. Easy\n2. Medium\n3. Hard\n";
        cin >> difficulty;
        player = 'X';
        cpu = 'O';
    } else if (gameMode == 2) {
        player = 'X';
    }

    playGame(gameMode, difficulty);

    return 0;
}