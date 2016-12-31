#include <stdio.h>

int main()
{
    unsigned n, p;
    scanf("%u %u%*c", &n, &p);
    printf("%u\n", (p <= n-p ? p : n-p + !(n%2)) / 2);
    return 0;
}
