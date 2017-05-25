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

    for (part[last = 0] = n; ; part[++last] = rest) {
        benefit(part, last + 1);

        for (rest = 0; last >= 0 && part[last] == 1; --last)
            rest += part[last];
 
        if (last < 0) return;
 
        for (--part[last], ++rest; rest > part[last]; ++last)
            rest -= part[last + 1] = part[last];
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
