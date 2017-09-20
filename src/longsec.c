#include <stdio.h>

int main()
{
    size_t n;
    char c, first_digit;

    scanf(" %zu%*c", &n);

    while (n--) {
        first_digit = getchar();

        while ((c = getchar()) != '\n' && c == first_digit);
        if (c == '\n') goto no;

        while ((c = getchar()) != '\n' && c == first_digit);
        if (c == '\n') goto yes;

    no:
        puts("No");
        goto cleanup;

    yes:
        puts("Yes");
        goto cleanup;

    cleanup:
        while (c != '\n') c = getchar();
    }

    return 0;
}
