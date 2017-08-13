#include <stdio.h>
#include <stdlib.h>

/* Failure of malloc has not been checked throughout this code because
    1. The code is expected to run on Linux, where malloc _almost_ never fails.
    2. In case malloc fails on any OS,
        there is not much recovery that the program can attempt anyways.
    3. Checking return values has a performance penalty.
*/

char *getstr(char separator)
{
    int c;
    size_t n;
    char *s = NULL;

    for (n = 0; (c = getchar()) != separator; s[n++] = c) s = realloc(s, n + 2);

    s[n] = '\0';
    return s;
}

size_t lcs(char *str1, char *str2)
{
    size_t len1, len2, **suflen, i, j;

    for (len1 = 0; str1[len1]; ++len1);
    for (len2 = 0; str2[len2]; ++len2);

    suflen = malloc(sizeof(*suflen) * (len1 + 1)); /* 1 */
    for (i = 0; i <= len1; ++i)
        suflen[i] = malloc(sizeof(**suflen) * (len2 + 1)); /* 2 */

    for (i = 0; i <= len1; ++i)
        for (j = 0; j <= len2; ++j)
            if (!(i && j))
                suflen[i][j] = 0;
            else if (str1[i - 1] == str2[j - 1])
                suflen[i][j] = 1 + suflen[i - 1][j - 1];
            else
                suflen[i][j] = suflen[i - 1][j] > suflen[i][j - 1] ?
                                            suflen[i - 1][j] : suflen[i][j - 1];

    for (i = 0; i <= len1; ++i) free(suflen[i]); /* 2 */
    free(suflen); /* 1 */

    return suflen[len1][len2];
}

int main()
{
    unsigned t, n;
    size_t maxlen, sublen;
    char *str1, *str2;

    scanf(" %u%*c", &t);

    while (t--) {
        str1 = getstr('\n'); /* 1 */

        scanf(" %u%*c", &n);

        maxlen = 0;

        while (n--) {
            str2 = getstr(n ? ' ' : '\n'); /* 2 */

            sublen = lcs(str1, str2);
            maxlen = maxlen > sublen ? maxlen : sublen;

            free(str2); /* 2 */
        }

        printf("%zu\n", maxlen);

        free(str1); /* 1 */
    }

    return 0;
}
