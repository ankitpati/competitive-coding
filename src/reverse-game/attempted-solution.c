#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned *rev(unsigned *s, size_t n)
{
    size_t i, j;
    unsigned t;
    for (i = 0, j = n - 1; i < j; ++i, --j) {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
    return s;
}

int main()
{
    size_t t, n, i, j;
    unsigned k;
    unsigned *s;

    scanf(" %zu%*c", &t);

    while (t--) {
        scanf(" %zu %u%*c", &n, &k);

        s = malloc(n * sizeof(*s));
        for (i = 0; i < n; ++i) s[i] = i;

        for (i = 0; i < n; ++i){
            rev(s + i, n - i);
            for (j = 0; j <= i; ++j)
                if (s[j] == k)
                    goto found;
        }

    found:
        printf("%zu\n", j);
    }

    return 0;
}
