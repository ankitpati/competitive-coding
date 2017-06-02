#include <stdio.h>
#include <stdlib.h>

int cols; /* grid is row major */

/* treat flat array as 2D array */
inline int *ind(int *m, int r, int c) { return m + cols*r + c; }

void find_nbr_ind(int row, int col, int nbr_indices[][2])
{
    nbr_indices[0][0] = row - 1;
    nbr_indices[0][1] = col - 1;

    nbr_indices[1][0] = row - 1;
    nbr_indices[1][1] = col;

    nbr_indices[2][0] = row - 1;
    nbr_indices[2][1] = col + 1;

    nbr_indices[3][0] = row;
    nbr_indices[3][1] = col - 1;

    nbr_indices[4][0] = row;
    nbr_indices[4][1] = col + 1;

    nbr_indices[5][0] = row + 1;
    nbr_indices[5][1] = col - 1;

    nbr_indices[6][0] = row + 1;
    nbr_indices[6][1] = col;

    nbr_indices[7][0] = row + 1;
    nbr_indices[7][1] = col + 1;
}

/* DC: Don't Care */
int *survivalcells(int DC1_, int *stats, int DC2_, int *grid, int *output_n)
{
    /* nbr: matrix with number of neighbours */
    int rows, s1, s2, b1, b2, g, *nbr, i, j, k, nbr_count, nbr_indices[8][2];

    rows = stats[0];
    cols = stats[1];
    s1   = stats[2];
    s2   = stats[3];
    b1   = stats[4];
    b2   = stats[5];
    g    = stats[6];

    *output_n = rows * cols;

    nbr = malloc(rows * cols * sizeof(*nbr));

    while (g--) {
        for (i = 0; i < rows; ++i)
            for (j = 0; j < cols; ++j) {
                find_nbr_ind(i, j, nbr_indices);

                nbr_count = 0;
                for (k = 0; k < 8; ++k)
                    if (
                        nbr_indices[k][0] >= 0 && nbr_indices[k][0] < rows &&
                        nbr_indices[k][1] >= 0 && nbr_indices[k][1] < cols &&
                        *ind(grid, nbr_indices[k][0], nbr_indices[k][1])
                    ) ++nbr_count;

                *ind(nbr, i, j) = nbr_count;
            }

        for (i = 0; i < rows; ++i)
            for (j = 0; j < cols; ++j)
                *ind(grid, i, j) =
                    *ind(grid, i, j) ?
                        *ind(nbr, i, j) >= s1 && *ind(nbr, i, j) <= s2 :
                        *ind(nbr, i, j) >= b1 && *ind(nbr, i, j) <= b2 ;
    }

    return grid;
}

int main()
{
    int i, stats_n, *stats, grid_n, *grid, output_n, *output;

    scanf(" %d%*c", &stats_n);
    stats = malloc(stats_n * sizeof(*stats));
    for (i = 0; i < stats_n; ++i) scanf(" %d%*c", stats + i);

    scanf(" %d%*c", &grid_n);
    grid = malloc(grid_n * sizeof(*grid));
    for (i = 0; i < grid_n; ++i) scanf(" %d%*c", grid + i);

    output = survivalcells(stats_n, stats, grid_n, grid, &output_n);

    for (i = 0; i < output_n; ++i) printf("%d ", output[i]);
    putchar('\n');

    return 0;
}
