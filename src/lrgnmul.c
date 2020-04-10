/* lrgnmul.c */
/* Large Number Multiplication */

#include <stdio.h>

#define STRSIZ 32000

void getnum(char *s, int *len)
{
    int i, c;
    for (i = 0; (c = getchar()) != '\n' && c != EOF; ++i) s[i] = c - '0';
    *len = i;
}

void putnum(int *s, int len)
{
    while (len > 1)
        if (*s)
            break;
        else
            ++s, --len;

    while (len--) putchar('0' + *(s++));
}

int main()
{
    /* variables in ALL CAPS are provided by the online judge plaform */
    int TC;
    char NUM1[STRSIZ], NUM2[STRSIZ];

    /* counters */
    int tc, i, j;

    /* multiplication artefacts */
    int carry, digitprod;
    int prod[STRSIZ + STRSIZ];

    /* lengths */
    int len1, len2, lenp;

    scanf(" %d%*c", &TC);

    for (tc = 0; tc < TC; ++tc) {
        getnum(NUM1, &len1);
        getnum(NUM2, &len2);

        lenp = len1 + len2;

        for (i = 0; i < lenp; ++i)
            prod[i] = 0;

        for (i = len1 - 1; i >= 0; --i) {
            carry = 0;

            for (j = len2 - 1; j >= 0; --j) {
                digitprod = NUM1[i] * NUM2[j] + prod[i + j + 1] + carry;
                carry = digitprod / 10;
                prod[i + j + 1] = digitprod % 10;
            }

            prod[i + j + 1] += carry;
        }

        putchar('#');
        putchar('0' + tc + 1);
        putchar(' ');
        putnum(prod, lenp);
        putchar('\n');
    }

    return 0;
}
