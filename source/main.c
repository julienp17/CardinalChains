#include "file_reading.h"
#include "grid.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void ask_user()
{
    printf("Select a direction (N, S, E, W).\nCancel the previous move(B).\n");
    printf("Erase the chain (R).\nRestart the level (X).\n");
    printf("Select another chain (C)\n");
}

pos_t pos_from_direction(grid_t *grid, char direction)
{
    if (direction == 'N') {
        return (pos_t) {grid->pos.x, grid->pos.y - 1};
    } else if (direction == 'S') {
        return (pos_t) {grid->pos.x, grid->pos.y + 1};
    }
    if (direction == 'W') {
        return (pos_t) {grid->pos.x - 1, grid->pos.y};
    } else if (direction == 'E') {
        return (pos_t) {grid->pos.x + 1, grid->pos.y};
    }
}

bool pos_is_valid(grid_t *grid, pos_t pos)
{
    return (
        pos.x >= 0
        && pos.x < grid->width
        && pos.y >= 0
        && pos.y < grid->height
    );
}

bool move_is_valid(grid_t *grid, pos_t pos)
{
    if (pos_is_valid(grid, pos) == false) {
        return false;
    }
    cell_t *current_cell = grid->cells[grid->pos.y][grid->pos.x];
    cell_t *next_cell = grid->cells[pos.y][pos.x];

    return (
        next_cell != NULL
        && strcmp(next_cell->color, "white") == 0
        && (current_cell->number == 'X'
            || current_cell->number <= next_cell->number)
    );
}

bool level_completed(grid_t *grid)
{
    for (int i = 0 ; i < grid->height ; i++) {
        for (int j = 0 ; j < grid->width ; j++) {
            if (grid->cells[i][j] == NULL)
                continue;
            if (strcmp(grid->cells[i][j]->color, "white") == 0)
                return false;
        }
    }
    return true;
}

int main(int ac, char **av)
{
    cell_t *current_cell = NULL;
    grid_t *grid = make_grid(av[1]);
    char cmd = 0;
    bool valid = false;

    while (level_completed(grid) == false) {
        current_cell = grid->cells[grid->pos.y][grid->pos.x];
        print_grid(grid);
        ask_user();
        valid = false;
        while (valid == false) {
            printf("> ");
            cmd = fgetc(stdin);
            if (cmd == 'N' || cmd == 'S' || cmd == 'W' || cmd == 'E') {
                pos_t pos = pos_from_direction(grid, cmd);
                if (move_is_valid(grid, pos)) {
                    cell_t *new_chain_cell = grid->cells[pos.y][pos.x];

                    new_chain_cell->color = strdup(current_cell->color);
                    new_chain_cell->previous = current_cell;
                    current_cell->next = new_chain_cell;
                    grid->pos = pos;
                    valid = true;
                } else {
                    printf("Cannot move there.\n");
                }
            }
            if (cmd == 'B') {
                cell_t *previous_cell = current_cell->previous;

                if (previous_cell != NULL) {
                    current_cell->previous = NULL;
                    current_cell->color = strdup("white");
                    previous_cell->next = NULL;
                    grid->pos = previous_cell->pos;
                    valid = true;
                } else {
                    printf("Cannot go back further.\n");
                }
            }
            if (cmd == 'R') {
                cell_t *previous_cell = NULL;

                while (current_cell->previous != NULL) {
                    previous_cell = current_cell->previous;
                    current_cell->color = strdup("white");
                    current_cell->previous = NULL;
                    previous_cell->next = NULL;
                    current_cell = previous_cell;
                }
                grid->pos = current_cell->pos;
                valid = true;
            }
            if (cmd == 'X') {
                grid = make_grid(av[1]);
                valid = true;
            }
            if (cmd == 'C') {
                grid->chain_index++;
                if (grid->chain_index >= grid->nb_chains)
                    grid->chain_index = 0;

                pos_t chain_pos = grid->chain_pos[grid->chain_index];
                current_cell = grid->cells[chain_pos.y][chain_pos.x];
                while (current_cell->next != NULL)
                    current_cell = current_cell->next;
                grid->pos = current_cell->pos;
                valid = true;
            }
            fgetc(stdin);
        }
    }
}
