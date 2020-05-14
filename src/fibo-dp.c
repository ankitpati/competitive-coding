#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define INVALID_FLAG ULLONG_MAX

static size_t *memo;

size_t fibcore(size_t n)
{
    return memo[n] != INVALID_FLAG ? memo[n] :
            (memo[n] = fibcore(n - 1) + fibcore(n - 2));
}

size_t fib(size_t n)
{
    size_t i, fibnum;

    switch (n) {
    case 0:
        return 0;
        break;
    case 1:
    case 2:
        return 1;
        break;
    default:
        break;
    }

    if (!(memo = malloc((n + 1) * sizeof(*memo)))) {
        fprintf(stderr, "Insufficient memory!");
        return INVALID_FLAG;
    }

    memo[0] = 0;
    memo[1] = memo[2] = 1;

    for (i = 3; i <= n; ++i)
        memo[i] = INVALID_FLAG;

    fibnum = fibcore(n);

    free(memo);
    return fibnum;
}

int main(int argc, char **argv)
{
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage:\n\tfibo-dp <fibonacci-of?>...\n");
        return 1;
    }

    for (i = 1; i < argc; ++i)
        printf("fib(%d) = %zu\n", atoi(argv[i]), fib(atoi(argv[i])));

    return 0;
}
