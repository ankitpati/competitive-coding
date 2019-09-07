/* negzeropos.c */
#include <stdio.h>
#include <stdlib.h>

inline int sign(int x)
{
    return (x > 0) - (x < 0);
}

int cmp(const void *a, const void *b)
{
    return sign(*(int *)a) - sign(*(int *)b);
}

int main()
{
    int *arr;
    size_t i, n;

    puts("Number of integers?");
    scanf(" %zu%*c", &n);

    if (!(arr = malloc(sizeof(*arr) * n))) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(12);
    }

    printf("%zu integers?\n", n);
    for (i = 0; i < n; ++i) scanf(" %i%*c", arr + i);

    qsort(arr, n, sizeof(*arr), cmp);

    puts("Negative-Zero-Positive sorted integers:");
    for (i = 0; i < n; ++i) printf("%i\n", arr[i]);

    free(arr);
    return 0;
}
/* end of negzeropos.c */

/* OUTPUT

Number of integers?
15

12 integers?
2 -1 0 3 4 0 0 -1 0 -6 9 0 9 -9 1

Negative-Zero-Positive sorted integers:
-6
-1
-9
-1
0
0
0
0
0
1
3
4
9
9
2

*/
