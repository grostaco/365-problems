/*
 * Let there be a 10x10 grid, starting from x and y, 
 * randomly move to adjacent cells. If every cell adjacent to the current cell 
 * are all occupied, exit. If not, leave 'A' in the cell that was left and move
 * to an unoccupied cell repeat until 'Z'. An unoccupied cell will be signified by
 * a '.', an occupied cell will have an alphabet. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static unsigned abs_table[] = {9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
                               1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
static unsigned neg_abs_table[] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

static unsigned **table =
    (unsigned *[]){[0 ... 1] = neg_abs_table + 1, abs_table + 10} + 1;
#define absolute_pos(xpos, ypos, xoffset, yoffset)                             \
  ({ table[yoffset][ypos + yoffset] * 10 + table[xoffset][xpos + xoffset]; })

int main() {
  int x = 0, y = 0;
  int dx, dy;
  char c = 'A';

  char *grid = (char[10 * 10]){[0 ... 99] = '.'};
  srand48(time(NULL));

  while (c <= 'Z' && (grid[absolute_pos(x, y, 0, 0)] = c++) &&
         (grid[absolute_pos(x, y, 1, 0)] == '.' ||
          grid[absolute_pos(x, y, -1, 0)] == '.' ||
          grid[absolute_pos(x, y, 0, 1)] == '.' ||
          grid[absolute_pos(x, y, 0, -1)] == '.')) {
    do {
      dx = mrand48() % 2;
      dy = mrand48() % 2;
    } while (dx * dy != 0 || grid[absolute_pos(x, y, dx, dy)] != '.');
    x = absolute_pos(x, 0, dx, 0);
    y = absolute_pos(y, 0, dy, 0);
  }

  for (int i = 0; i < 10; i++, grid += 10) {
    fprintf(stdout, "%.10s\n", grid);
  }
}
