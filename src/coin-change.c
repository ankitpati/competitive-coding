#include <stdio.h>
#include <stdlib.h>

static size_t **hash;

size_t count(size_t n, size_t *c, size_t m)
{
    size_t value = hash[m][n];
    if (value != ~(size_t)0u) return value;

    return hash[m][n] = n ? n < *c ? 0 : m ?
                            count(n, c + 1, m - 1) + count(n - *c, c, m)
                            : 0 : 1;
}

int cmp(const void *a, const void *b)
{
    return *(size_t *)a - *(size_t *)b;
}

int main()
{
    size_t n, m, *c, i, j;

    scanf(" %zu %zu%*c", &n, &m);

    c = malloc(m * sizeof(*c));
    for (i = 0; i < m; ++i) scanf(" %zu%*c", c + i);

    qsort(c, m, sizeof(*c), cmp);

    hash = malloc((m + 1) * sizeof(*hash));
    for (i = 0; i <= m; ++i) {
        hash[i] = malloc((n + 1) * sizeof(**hash));
        for (j = 0; j <= n; ++j) hash[i][j] = ~(size_t)0u;
    }

    printf("%zu\n", count(n, c, m));

    return 0;
}
