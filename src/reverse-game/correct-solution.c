#include <stdio.h>

int main()
{
    unsigned t, n, k;

    scanf(" %u%*c", &t);

    while (t--) {
        scanf(" %u %u%*c", &n, &k);
        printf("%u\n", k < n/2 ? 2*k + 1 : (n - 1 - k) * 2);
    }

    return 0;
}
