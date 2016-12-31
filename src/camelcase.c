#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    size_t i, words;
    char *s;

    if(!(s = malloc(10240))) exit(12);

    words = 0;

    if (getchar() != EOF) ++words;

    do {
        fgets(s, 10240, stdin);
        for (i = 0; s[i]; ++i)
            if (isupper(s[i])) ++words;
    } while (!feof(stdin));

    printf("%zu\n", words);

    free(s);
    return 0;
}
