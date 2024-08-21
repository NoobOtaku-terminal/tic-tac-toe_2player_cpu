# tic-tac-toe_2player_cpu

This C++ program implements a Tic-Tac-Toe game that offers two modes: Player vs. CPU and a 2-player mode where two human players can compete against each other. It allows the user to select a difficulty level for the CPU opponent in the Player vs. CPU mode. The available difficulties are Easy, Medium, and Hard, each providing varying levels of challenge.

### Key Features:

1. **Game Board Representation**: The game board is represented as a 3x3 grid using a 2D character array `board[3][3]`, where each cell stores either 'X', 'O', or a blank space.

2. **Game Initialization**: The `initializeBoard()` function sets up an empty game board by filling each cell with a blank space. The `moves` counter is initialized to zero to track the number of moves made during the game.

3. **Game Display**: The `printBoard()` function visually represents the current state of the board using a grid format.

4. **Player Moves**: In both game modes, the player makes a move by selecting a position (1-9). The `playerMove()` function validates the move to ensure it's legal and updates the board accordingly.

5. **CPU Moves**: The `cpuMove()` function handles the CPU's move based on the chosen difficulty:
   - **Easy Difficulty**: The CPU selects a random empty cell.
   - **Medium Difficulty**: The CPU tries to block the player's winning move or selects a random move if no block is needed.
   - **Hard Difficulty**: The CPU employs the minimax algorithm, making it an unbeatable opponent by exploring all possible moves and selecting the optimal one.

6. **Minimax Algorithm**: The `minimax()` function implements the minimax algorithm for the Hard difficulty mode. This function recursively evaluates all possible game states, attempting to maximize the CPU's score and minimize the player's score.

7. **Win and Draw Conditions**: The `isWinning()` function checks if a player has won by evaluating rows, columns, and diagonals. The `isDraw()` function checks if the game is a draw when all cells are filled without a winner.

8. **Game Modes**:
   - **Player vs. CPU**: The player competes against the CPU. The player can choose the difficulty level, and the CPU makes moves based on the chosen level.
   - **2-Player Mode**: Two players alternate turns, and the game checks for a winner or draw after each move.

9. **Game Loop**: The `playGame()` function contains the main game loop, alternating turns between the player and CPU or the two players, checking for win/draw conditions after each move, and printing the game board.

10. **Main Function**: The `main()` function serves as the entry point of the program. It prompts the user to select the game mode and, if applicable, the difficulty level for the CPU before starting the game.

### Overall:
This program provides an interactive Tic-Tac-Toe experience in the console, catering to both single-player and two-player modes with varying difficulty levels for the CPU. The implementation of the minimax algorithm ensures that the Hard mode provides a challenging, nearly unbeatable opponent.
