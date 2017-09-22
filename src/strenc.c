#include <stdio.h>
#include <ctype.h>

int main()
{
    int t, n, k, ti, ni, ki, i, c, o;
    char a[150], A, B, ci, digit, prevci, output[500];

    scanf(" %d%*c", &t);

    for (ti = 0; ti < t; ++ti) {
        printf("#%d\n", ti + 1);
        for (i = 'a'; i <= 'z'; ++i) a[i] = '\0';

        scanf(" %d%*c", &n);
        for (ni = 0; ni < n; ++ni) {
            scanf(" %c %c%*c", &A, &B);
            a[A] = B;
        }

        scanf(" %d%*c", &k);
        for (ki = 0; ki < k; ++ki) {
            o = 0;
            while ((c = getchar()) != EOF && c != '\n') {
                if (isdigit(a[c])) output[o++] = a[c];
                else {
                    for (ci = a[c]; ci && ci != c && !isdigit(ci); ci = a[ci]);

                    if (!ci) {
                        puts("-1");
                        while ((c = getchar()) != EOF && c != '\n');
                        goto nextstring;
                    }

                    if (isdigit(ci)) digit = ci;
                    else digit = '0';

                    ci = a[c];
                    while (ci != c && !isdigit(ci)) {
                        prevci = ci;
                        ci = a[ci];
                        a[prevci] = digit;
                    }
                    output[o++] = a[c] = digit;
                }
            }
            output[o] = '\0';
            puts(output);

        nextstring: ;
        }
    }

    return 0;
}
