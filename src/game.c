#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RED   "\x1B[31m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

void runGame() {
    const size_t GRID_WIDTH = 7;
    const size_t GRID_HEIGHT = 6;

    char** grid = malloc(GRID_HEIGHT * sizeof(char*));

    if (grid == NULL) {
        printf("ERROR: Grid memory allocation failed.\n");
        return;
    }

    initialiseGrid(grid, GRID_WIDTH, GRID_HEIGHT);
    
    bool gameOver = false;

    size_t turn = 1;
    size_t column;
    bool valid;

    while (!gameOver) {
        printGrid(grid, GRID_WIDTH, GRID_HEIGHT);
        
        do {
            scanf("%zu", &column);

            if (column >= 1 && column <= 7) {
                column--;

                if (grid[0][column] != 'E') {
                    valid = false;
                    printf("Column is full.\n");
                    continue;
                }

                valid = true;
            } else {
                valid = false;
                printf("Please enter a value between 1 and 7.\n");
            }
        } while (!valid);

        if (turn % 2 == 1) {
            pushCounter(grid, GRID_WIDTH, GRID_HEIGHT, column, 'R');
        } else {
            pushCounter(grid, GRID_WIDTH, GRID_HEIGHT, column, 'Y');
        }

        gameOver = isDiamond(grid, GRID_WIDTH, GRID_HEIGHT, 'R') || 
                   isDiamond(grid, GRID_WIDTH, GRID_HEIGHT, 'Y') || 
                   isGridFull(grid, GRID_WIDTH);
        
        if (gameOver) break;

        turn++;
    }

    printGrid(grid, GRID_WIDTH, GRID_HEIGHT);
    printf("Game Over!\n");
    free(grid);
}

void initialiseGrid(char* grid[], const size_t GRID_WIDTH, const size_t GRID_HEIGHT) { 
    for (size_t i = 0; i < GRID_HEIGHT; i++) {
        grid[i] = malloc(GRID_WIDTH * sizeof(char));

        for (size_t j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = 'E';
        }
    }
}

void printGrid(char* grid[], const size_t GRID_WIDTH, const size_t GRID_HEIGHT) { 
    for (size_t i = 0; i < GRID_HEIGHT; i++) {
        for (size_t j = 0; j < GRID_WIDTH; j++) {
            if (grid[i][j] == 'E') {
                printf("%c ", grid[i][j]);
                continue;
            }

            if (grid[i][j] == 'R') {
                printf(RED "%c " RESET, grid[i][j]);
                continue;
            }

            if (grid[i][j] == 'Y') {
                printf(YEL "%c " RESET, grid[i][j]);
            }
        }

        printf("\n");
    }
}

void pushCounter(char* grid[], const size_t GRID_WIDTH, const size_t GRID_HEIGHT, const size_t column, const char counter) {
    bool placed = false;
    size_t height = 0;

    if (grid[GRID_HEIGHT-1][column] == 'E') {
        grid[GRID_HEIGHT-1][column] = counter;
        return;
    }

    while (!placed) {
        if (grid[height+1][column] == 'E') {
            height++;
            continue;
        }

        grid[height][column] = counter;
        placed = true;
    }

}

bool isDiamond(char* grid[], const size_t GRID_WIDTH, const size_t GRID_HEIGHT, const char counter) {
    for (size_t height = 2; height < GRID_HEIGHT; height++) {
        for (size_t column = 1; column < GRID_WIDTH-1; column++) {
            if (grid[height][column] == counter &&
                grid[height-1][column-1] == counter &&
                grid[height-2][column] == counter &&
                grid[height-1][column+1] == counter) 
            {
                return true;
            }
        }
    }

    return false;
}

bool isGridFull(char* grid[], const size_t GRID_WIDTH) {
    size_t total = 0;

    for (size_t column = 0; column < GRID_WIDTH; column++) {
        if (grid[0][column] != 'E') {
            total++;
        }
    }

    if (total == GRID_WIDTH) return true;
    else return false;
}
