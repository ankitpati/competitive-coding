#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

double ocseries(unsigned long long n)
{
    unsigned long long i;
    double ret;

    if (n < 2)
        return n;

    ret = sqrt(1 + n);

    for (i = n - 1; i != 1; --i)
        ret = sqrt(1 + i*ret);

    return ret;
}

int main(int argc, char **argv)
{
    unsigned long long i, n;

    if (argc != 2) {
        fprintf(stderr, "Usage:\n\tocseries <number-to-count-upto>\n");
        exit(1);
    }

    n = strtoull(argv[1], NULL, 10);

    /* n = ULLONG_MAX; */     /* newer GCC, Linux  */
    /* n = ULONG_LONG_MAX; */ /* older GCC, Cygwin */

    for (i = 0; i <= n; ++i)
        printf("%llu → %.16lf\n", i, ocseries(i));

    return 0;
}
