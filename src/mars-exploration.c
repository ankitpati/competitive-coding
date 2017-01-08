#include <stdio.h>

#define MAX_CHARS (99*3 + 2)

int main()
{
    unsigned i, changed;
    char s[MAX_CHARS];
    fgets(s, MAX_CHARS, stdin);
    for (i = changed = 0; s[i] && s[i] != '\n'; ++i)
        if (s[i] != "SOS"[i % 3]) ++changed;
    printf("%u\n", changed);
    return 0;
}
