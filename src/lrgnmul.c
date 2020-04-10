/* lrgnmul.c */
/* Large Number Multiplication */

#include <stdio.h>
#include <stdlib.h>

#define STRSIZ 32000

void getnum(char *s, int *len)
{
    int i, c;
    for (i = 0; (c = getchar()) != '\n' && c != EOF; ++i) s[i] = c - '0';
    *len = i;
}

void putnum(int *s, int len)
{
    int i;
    for (i = len - 1; i; --i) if (s[i]) break;
    while (i >= 0) putchar('0' + s[i--]);
}

int main()
{
    /* variables in ALL CAPS are provided by the online judge plaform */
    int TC;
    char *NUM1, *NUM2;

    /* counters */
    int tc, i, j, p1, p2;

    /* multiplication artefacts */
    int carry, digitprod;
    int *prod;

    /* lengths */
    int len1, len2, lenp;

    NUM1 = malloc(STRSIZ);
    NUM2 = malloc(STRSIZ);

    scanf(" %d%*c", &TC);

    for (tc = 0; tc < TC; ++tc) {
        getnum(NUM1, &len1);
        getnum(NUM2, &len2);

        lenp = len1 + len2;

        prod = calloc(lenp, sizeof(*prod));

        for (i = len1 - 1, p1 = 0; i >= 0; --i, ++p1) {
            carry = 0;

            for (j = len2 - 1, p2 = 0; j >= 0; --j, ++p2) {
                digitprod = NUM1[i] * NUM2[j] + prod[p1 + p2] + carry;
                carry = digitprod / 10;
                prod[p1 + p2] = digitprod % 10;
            }

            if (carry)
                prod[p1 + p2] += carry;
        }

        putchar('#');
        putchar('0' + tc + 1);
        putchar(' ');
        putnum(prod, lenp);
        putchar('\n');

        free(prod);
    }

    return 0;
}
