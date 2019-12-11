#include <stdio.h>

#define MINCHAR 'a'
#define MAXCHAR 'z'

size_t s[MAXCHAR + 1];

int main()
{
    int c, is_high_or_one;
    size_t count_min;

    for (;;) {
        c = getchar();
        if (c == '\n' || feof(stdin)) break;

        ++s[c];
    }

    count_min = ~(size_t)0;
    for (c = MINCHAR; c <= MAXCHAR; ++c)
        if (s[c] > 1 && s[c] < count_min)
            count_min = s[c];

    is_high_or_one = 0;
    for (c = MINCHAR; c <= MAXCHAR; ++c) {
        if (!s[c] || s[c] == count_min) continue;

        if (s[c] == count_min + 1 || s[c] == 1) {
            if (is_high_or_one) break;
            is_high_or_one = 1;
        }

        else break;
    }

    puts(c > MAXCHAR ? "YES" : "NO");

    return 0;
}
