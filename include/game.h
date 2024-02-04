#include <stddef.h>
#include <stdbool.h>

void runGame();
void initialiseGrid(char* grid[], const size_t GRID_WIDTH, const size_t GRID_HEIGHT);
void printGrid(char* grid[], const size_t GRID_WIDTH, const size_t GRID_HEIGHT);
void pushCounter(char* grid[], const size_t GRID_WIDTH, const size_t GRID_HEIGHT, const size_t column, const char counter);
bool isDiamond(char* grid[], const size_t GRID_WIDTH, const size_t GRID_HEIGHT, const char counter);
bool isGridFull(char* grid[], const size_t GRID_WIDTH);
