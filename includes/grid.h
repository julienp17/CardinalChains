#ifndef GRID_H_
#define GRID_H_

#include <stdlib.h>

typedef struct pos {
    int x;
    int y;
} pos_t;

typedef struct cell {
    char number;
    pos_t pos;
    char *color;
    struct cell *previous;
    struct cell *next;
} cell_t;

cell_t *make_cell(int x, int y, char number);

typedef struct grid {
    pos_t pos;
    int width;
    int height;
    cell_t ***cells;
    int nb_chains;
    pos_t *chain_pos;
    int chain_index;
} grid_t;

grid_t *make_grid(char *filename);
void setup_grid(grid_t *grid, char **lines);
void print_grid(grid_t *grid);

#endif
