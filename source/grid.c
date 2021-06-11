#include "grid.h"
#include "file_reading.h"
#include <stdio.h>
#include <string.h>

grid_t *make_grid(char *filename)
{
    grid_t *grid = malloc(sizeof(grid_t));
    char **lines = get_file_lines(filename);
    char *colors[] = {
        "blue", "green", "yellow", "red"
    };
    int color_i = 0;

    setup_grid(grid, lines);
    for (int y = 0 ; lines[y] ; y++) {
        for (int x = 0 ; lines[y][x] ; x++) {
            if (lines[y][x] == ' ') {
                grid->cells[y][x] = NULL;
                continue;
            }
            grid->cells[y][x] = make_cell(x, y, lines[y][x]);
            if (lines[y][x] == 'X') {
                grid->cells[y][x]->color = strdup(colors[color_i]);
                color_i++;
                if (color_i > 3) {
                    color_i = 0;
                }
            }
        }
    }
    return grid;
}

void setup_grid(grid_t *grid, char **lines)
{
    int y = 0;
    int x = 0;
    int max_width = 0;
    grid->nb_chains = 0;

    while (lines[y]) {
        x = 0;
        while (lines[y][x]) {
            if (lines[y][x] == 'X')
                grid->nb_chains++;
            x++;
        }
        if (x > max_width)
            max_width = x;
        y++;
    }
    grid->pos.x = 0;
    grid->pos.y = 0;
    grid->height = y;
    grid->width = max_width;
    grid->cells = malloc(sizeof(cell_t **) * (grid->height + 1));
    for (int y = 0 ; y < grid->height ; y++) {
        grid->cells[y] = malloc(sizeof(cell_t *) * (grid->width + 1));
        grid->cells[y][grid->width] = NULL;
    }
    grid->cells[grid->height] = NULL;

    grid->chain_pos = malloc(sizeof(pos_t) * grid->nb_chains);
    int index = 0;
    for (int y = 0 ; lines[y] ; y++) {
        for (int x = 0 ; lines[y][x] ; x++) {
            if (lines[y][x] == 'X') {
                grid->chain_pos[index].y = y;
                grid->chain_pos[index].x = x;
                index++;
            }
        }
    }
    grid->chain_index = 0;
    grid->pos = grid->chain_pos[0];
}

cell_t *make_cell(int x, int y, char number)
{
    cell_t *cell = malloc(sizeof(cell_t));

    cell->pos.x = x;
    cell->pos.y = y;
    cell->number = number;
    cell->color = strdup("white");
    cell->previous = NULL;
    cell->next = NULL;
    return cell;
}