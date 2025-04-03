#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ROWS 40
#define COLS 200
#define GENERATIONS 100
#define ALIVE_CHAR 'O'
#define DEAD_CHAR  '.'
#define ALIVE_COLOR "\033[1;32m"
#define DEAD_COLOR  "\033[1;31m"
#define BORDER_COLOR "\033[1;33m"
#define ALIVE_PROBABILITY 10

void initializeGrid(int grid[ROWS][COLS]);
void displayGrid(int grid[ROWS][COLS]);
void updateGrid(int grid[ROWS][COLS]);
int countNeighbors(int grid[ROWS][COLS], int x, int y);

int main() {
    int grid[ROWS][COLS];
    initializeGrid(grid);

    printf("\033[1;34mGeneration 1:\033[0m\n");
    displayGrid(grid);

    for (int gen = 0; gen < GENERATIONS; gen++) {
        Sleep(300);
        system("cls");
        updateGrid(grid);
        printf("\033[1;34mGeneration %d:\033[0m\n", gen + 1);
        displayGrid(grid);
    }

    printf("\n\033[1;32mFinal Generation:\033[0m\n");
    displayGrid(grid);

    return 0;
}

void initializeGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = (rand() % 100 < ALIVE_PROBABILITY) ? 1 : 0;
        }
    }
}

void displayGrid(int grid[ROWS][COLS]) {
    printf(BORDER_COLOR "+");
    for (int j = 0; j < COLS; j++) printf("-");
    printf("+\033[0m\n");

    for (int i = 0; i < ROWS; i++) {
        printf(BORDER_COLOR "|\033[0m");
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == 1) {
                printf(ALIVE_COLOR "%c\033[0m", ALIVE_CHAR);
            } else {
                printf(DEAD_COLOR "%c\033[0m", DEAD_CHAR);
            }
        }
        printf(BORDER_COLOR "|\033[0m\n");
    }

    printf(BORDER_COLOR "+");
    for (int j = 0; j < COLS; j++) printf("-");
    printf("+\033[0m\n");
}

void updateGrid(int grid[ROWS][COLS]) {
    int newGrid[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = countNeighbors(grid, i, j);
            newGrid[i][j] = (grid[i][j] == 1) ? (neighbors == 2 || neighbors == 3) : (neighbors == 3);
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

int countNeighbors(int grid[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && grid[nx][ny] == 1)
                count++;
        }
    }
    return count;
}
