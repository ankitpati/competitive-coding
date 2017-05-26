#include <stdio.h>
#include <stdlib.h>

int *prices;

int benefit(int *arr, int len)
{
    static int max = 0;
    int sum;

    for (sum = 0; len--; ++arr) sum += prices[*arr - 1];
    if (sum > max) max = sum;

    return max;
}

void partition(int n)
{
    int *part, last, rest;

    part = malloc(n * sizeof(*part));

    part[last = 0] = n;

    for (;;) {
        benefit(part, last + 1);

        rest = 0;

        while (part[last] == 1) {
            rest += part[last--];
            if (last < 0) return;
        }
 
        --part[last];
        ++rest;

        while (rest > part[last]) {
            part[last + 1] = part[last];
            rest -= part[last + 1];
            ++last;
        }

        part[++last] = rest;
    }
}

int seller(int len, int *arr)
{
    prices = arr;
    partition(len);
    return benefit(NULL, 0);
}

int main()
{
    size_t i, n;
    int *arr;

    scanf("%zu\n", &n);
    arr = malloc(n * sizeof(*arr));
    for (i = 0; i < n; ++i) scanf(" %d%*c", arr + i);

    printf("%d\n", seller(8, arr));

    return 0;
}
