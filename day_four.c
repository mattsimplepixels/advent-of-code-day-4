#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROWS 142
#define MAX_COLS 142
#define WORD "XMAS"
#define WORD_LEN 4

int directions[8][2] = {
    {-1, 0},  
    {1, 0},
    {0, -1},  
    {0, 1},
    {-1, -1},
    {-1, 1},
    {1, -1},
    {1, 1}
};

int isValid(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

int dfs(char grid[MAX_ROWS][MAX_COLS], int row, int col, int dirIdx, int index, int rows, int cols) {
    if (index == WORD_LEN) {
        return 1; 
    }
    
    int newRow = row + directions[dirIdx][0];
    int newCol = col + directions[dirIdx][1];

    if (!isValid(newRow, newCol, rows, cols) || grid[newRow][newCol] != WORD[index]) {
        return 0; 
    }

    return dfs(grid, newRow, newCol, dirIdx, index + 1, rows, cols);
}

int countWordOccurrences(char grid[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == WORD[0]) { 
                for (int dirIdx = 0; dirIdx < 8; dirIdx++) {
                    if (dfs(grid, i, j, dirIdx, 1, rows, cols)) { 
                        count++; 
                    }
                }
            }
        }
    }

    return count;
}

int readGridFromFile(char grid[MAX_ROWS][MAX_COLS], const char *filename, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    *rows = 0;
    while (fgets(grid[*rows], MAX_COLS, file) != NULL) {
        size_t len = strlen(grid[*rows]);
        if (len > 0 && grid[*rows][len - 1] == '\n') {
            grid[*rows][len - 1] = '\0';
        }
        (*rows)++;
    }

    *cols = strlen(grid[0]);

    fclose(file);
    return 1;
}

int main() {
    char grid[MAX_ROWS][MAX_COLS];
    int rows, cols;

    clock_t start = clock();

    if (!readGridFromFile(grid, "grid.txt", &rows, &cols)) {
        return 1;
    }

    int result = countWordOccurrences(grid, rows, cols);

    clock_t end = clock();

    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

    printf("The word 'XMAS' appears %d times.\n", result);
    printf("Execution time: %.2f ms\n", elapsed_time);

    return 0;
}
