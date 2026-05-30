#include <iostream>
#include <vector>
using namespace std;

class SudokuSolver {
private:
    vector<vector<int>> grid;
    
public:
    // Constructor
    SudokuSolver() {
        grid = vector<vector<int>>(9, vector<int>(9, 0));
    }
    
    // Function to set grid (for predefined puzzles)
    void setGrid(const vector<vector<int>>& newGrid) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = newGrid[i][j];
            }
        }
    }
    
    // Function to input Sudoku grid
    void inputGrid() {
        cout << "\n========== SUDOKU INPUT ==========\n";
        cout << "Enter Sudoku puzzle (9x9):\n";
        cout << "Use 0 for empty cells\n\n";
        
        for (int i = 0; i < 9; i++) {
            cout << "Row " << i + 1 << ": ";
            for (int j = 0; j < 9; j++) {
                cin >> grid[i][j];
            }
        }
    }
    
    // Display the Sudoku grid
    void displayGrid() {
        cout << "\n=====================================\n";
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0 && i != 0) {
                cout << "-------------------------------------\n";
            }
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j != 0) {
                    cout << " | ";
                }
                if (grid[i][j] == 0) {
                    cout << ". ";
                } else {
                    cout << grid[i][j] << " ";
                }
            }
            cout << endl;
        }
        cout << "=====================================\n";
    }
    
    // Check if number is valid at given position
    bool isValid(int row, int col, int num) {
        // Check row
        for (int j = 0; j < 9; j++) {
            if (grid[row][j] == num) {
                return false;
            }
        }
        
        // Check column
        for (int i = 0; i < 9; i++) {
            if (grid[i][col] == num) {
                return false;
            }
        }
        
        // Check 3x3 subgrid
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (grid[i][j] == num) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    // Backtracking algorithm to solve Sudoku
    bool solveSudoku() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                // Find empty cell
                if (grid[i][j] == 0) {
                    // Try numbers 1-9
                    for (int num = 1; num <= 9; num++) {
                        if (isValid(i, j, num)) {
                            grid[i][j] = num;
                            
                            // Recursively solve
                            if (solveSudoku()) {
                                return true;
                            }
                            
                            // Backtrack
                            grid[i][j] = 0;
                        }
                    }
                    return false; // No valid number found
                }
            }
        }
        return true; // Puzzle solved
    }
    
    // Check if Sudoku is valid (no conflicts initially)
    bool isValidSudoku() {
        // Check all cells
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                int num = grid[i][j];
                if (num != 0) {
                    // Temporarily set to 0 to check duplicates
                    grid[i][j] = 0;
                    if (!isValid(i, j, num)) {
                        grid[i][j] = num;
                        return false;
                    }
                    grid[i][j] = num;
                }
            }
        }
        return true;
    }
    
    // Reset the grid
    void resetGrid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = 0;
            }
        }
    }
    
    // Function to solve with detailed output
    void solveAndDisplay() {
        cout << "\n========== SUDOKU SOLVER ==========\n";
        
        // Display input puzzle
        cout << "\nInput Puzzle:\n";
        displayGrid();
        
        // Validate the puzzle
        if (!isValidSudoku()) {
            cout << "\n[ERROR] Invalid Sudoku puzzle!\n";
            cout << "The puzzle has conflicting numbers.\n";
            return;
        }
        
        // Solve the puzzle
        if (solveSudoku()) {
            cout << "\n[SUCCESS] Puzzle Solved!\n";
            cout << "\nSolution:\n";
            displayGrid();
        } else {
            cout << "\n[ERROR] No solution exists for this puzzle!\n";
        }
    }
};

// Function to display menu
void showMenu() {
    cout << "\n========================================\n";
    cout << "   Code Alpha Internship - Task 3       \n";
    cout << "        Sudoku Solver (C++)             \n";
    cout << "========================================\n";
    cout << "\n1. Solve a Sudoku Puzzle\n";
    cout << "2. Solve Predefined Puzzle\n";
    cout << "3. Exit\n";
    cout << "\nEnter your choice: ";
}

// Predefined puzzles for testing
void predefinedPuzzle1(SudokuSolver &solver) {
    vector<vector<int>> puzzle = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    solver.setGrid(puzzle);  // Using setGrid function instead of direct access
}

void predefinedPuzzle2(SudokuSolver &solver) {
    vector<vector<int>> puzzle = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 8, 5},
        {0, 0, 1, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 5, 0, 7, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 1, 0, 0},
        {0, 9, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 7, 3},
        {0, 0, 2, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 9}
    };
    
    solver.setGrid(puzzle);  // Using setGrid function instead of direct access
}

int main() {
    SudokuSolver solver;
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                solver.inputGrid();
                solver.solveAndDisplay();
                break;
                
            case 2: {
                cout << "\n========== PREDEFINED PUZZLES ==========\n";
                cout << "1. Easy Puzzle (Classic)\n";
                cout << "2. Medium Puzzle\n";
                cout << "Choose puzzle (1-2): ";
                int subChoice;
                cin >> subChoice;
                
                if (subChoice == 1) {
                    predefinedPuzzle1(solver);
                    solver.solveAndDisplay();
                } else if (subChoice == 2) {
                    predefinedPuzzle2(solver);
                    solver.solveAndDisplay();
                } else {
                    cout << "[ERROR] Invalid choice!\n";
                }
                break;
            }
                
            case 3:
                cout << "\n[INFO] Exiting Sudoku Solver. Goodbye!\n";
                break;
                
            default:
                cout << "\n[ERROR] Invalid choice! Please enter 1-3.\n";
        }
        
    } while(choice != 3);
    
    return 0;
}
