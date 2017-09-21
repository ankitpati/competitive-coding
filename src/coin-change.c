#include <stdio.h>
#include <stdlib.h>

size_t count(size_t n, size_t *c, size_t m)
{
    return n ? n < *c ? 0 : m ?
        count(n, c + 1, m - 1) + count(n - *c, c, m)
        : 0 : 1;
}

int cmp(const void *a, const void *b)
{
    return *(size_t *)a - *(size_t *)b;
}

int main()
{
    size_t n, m, *c, i;

    scanf(" %zu %zu%*c", &n, &m);

    c = malloc(m * sizeof(*c));
    for (i = 0; i < m; ++i) scanf(" %zu%*c", c + i);

    qsort(c, m, sizeof(*c), cmp);
    printf("%zu\n", count(n, c, m));

    return 0;
}
