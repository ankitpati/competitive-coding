#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long bigint;
#define BIGINTFMT "llu"

bigint bigsqrt(bigint n)
{
    bigint i;
    for (i = 0; i * i <= n; ++i);
    return i - 1;
}

void print_divisors(bigint n)
{
    bigint f;
#define INSERT(factor) do { \
    f = (factor); \
    if (!d) { \
        divs[d++] = f; \
        break; \
    } \
\
    for (j = 0; j < d && divs[j] < f; ++j); \
    if (divs[j] == f) break; \
\
    for (k = d++; k > j; --k) divs[k] = divs[k - 1]; \
    divs[j] = f; \
} while (0)

    bigint i, c, *divs, d, j, k;

    /* allocate memory for maximum number of possible factors */
    divs = malloc((c = bigsqrt(n) + 1) * 2 * sizeof(*divs));

    d = 0;

    for (i = 1; i <= c; ++i) {
        if (n % i) continue;
        INSERT(n / i);
        INSERT(i);
    }

    for (j = 0; j < d; ++j) printf("%" BIGINTFMT " ", divs[j]);

    putchar('\n');
    free(divs);
}

int main()
{
    bigint n;

    puts("Enter numbers to factorise. 0 to terminate.");

    do {
        scanf(" %" BIGINTFMT "%*c", &n);
        print_divisors(n);
        putchar('\n');
    } while (n);

    return 0;
}
