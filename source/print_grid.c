#include "grid.h"
#include <stdio.h>
#include <string.h>

void show_color(cell_t *cell)
{
    if (strcmp(cell->color, "blue") == 0) {
        printf("\e[1;34m");
    } else if (strcmp(cell->color, "yellow") == 0) {
        printf("\e[1;33m");
    }
    if (strcmp(cell->color, "green") == 0) {
        printf("\e[1;32m");
    } else if (strcmp(cell->color, "red") == 0) {
        printf("\e[1;31m");
    }
}

void print_grid(grid_t *grid)
{
    for (int i = 0 ; i < grid->height ; i++) {
        for (int j = 0 ; j < grid->width ; j++) {
            if (grid->cells[i][j] == NULL) {
                printf("  ");
                continue;
            }
            if (i == grid->pos.y && j == grid->pos.x)
                printf("\e[7m");
            show_color(grid->cells[i][j]);
            printf("%c", grid->cells[i][j]->number);
            printf("\e[0m\e[39m ");
        }
        printf("\n");
    }
    cell_t *cell = grid->cells[grid->pos.y][grid->pos.x];
    printf("\n--- line: %d, column: %d, chain: ",
        cell->pos.y + 1, cell->pos.x + 1);
    show_color(cell);
    printf("%s\e[0m\e[39m ---\n", cell->color);
}

