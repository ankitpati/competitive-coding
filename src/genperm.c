#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a ;
    *a  = *b ;
    *b  = tmp;
}

int N, K, sum, *array;

int permute(int offset)
{
    int i;

    if (offset == N - 1) {
        sum = 0;
        for (i = 0; i < N - 1; ++i)
            sum += MAX(array[i], array[i + 1]);

        if (sum == K)
            return 1;

        return 0;
    }

    for (i = offset; i < N; ++i) {
        swap(array + offset, array + i);

        if (permute(offset + 1))
            return 1;

        swap(array + offset, array + i);
    }

    return 0;
}

int main()
{
    int T, t, n;

    scanf(" %d%*c", &T);
    for (t = 0; t < T; ++t) {
        scanf(" %d %d%*c", &N, &K);

        array = malloc(sizeof(*array) * N);

        for (n = 0; n < N; ++n)
            array[n] = n + 1;

        if (permute(0)) {
            printf("%d", array[0]);

            for (n = 1; n < N; ++n)
                printf(" %d", array[n]);

            putchar('\n');
        }
        else
            puts("-1");

        free(array);
    }

    return 0;
}
