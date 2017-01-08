#include <stdio.h>
#include <stdlib.h>

int cmp(unsigned *a, unsigned *b)
{
    return *a - *b;
}

int main()
{
    unsigned n, i, c[100], pairs;

    scanf("%u%*c", &n);

    for (i = 0; i < n; ++i)
        scanf("%u%*c", c + i);

    qsort(c, n, sizeof(*c), (int (*)(const void *, const void *)) cmp);

    for (i = pairs = 0; i < n - 1; ++i)
        if (c[i] == c[i + 1]) {
            ++pairs;
            ++i;
        }

    printf("%u\n", pairs);

    return 0;
}
