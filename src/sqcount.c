#include <stdio.h>

int main()
{
    unsigned n;

    printf("Length of grid side in unit lengths?\n");
    scanf(" %u%*c", &n);

    printf("Number of possible squares in grid is %u.\n",
                                                (n * (n + 1) * (2*n + 1)) / 6);

    return 0;
}
