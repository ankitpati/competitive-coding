/* crunch.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 100 strings of (80 characters + 1 '\0') each. */
#define NUM_STR       100
#define CHARS_PER_STR (80 + 1)

/* Non-repeating rand, within given upper and lower limits. */
int nr_rand(int lower, int upper)
{
    static int seen[NUM_STR], num_seen;

    int i, lrand, rand_step;

    /* `seen` persists across calls. Set any arg as -ve to reset. */
    if (lower < 0 || upper < 0) {
        num_seen = 0;
        return 0;
    }

    /* Limit `lrand` to given upper and lower limits, both inclusive. */
    lrand = abs(rand()) % (upper - lower + 1) + lower;

    /* If `lrand` is not at the top, step up; otherwise, step down.
     * The code below reverses the direction when we hit a limit.
     */
    rand_step = lrand == upper ? -1 : 1;

    while (num_seen < NUM_STR) {
        for (i = 0; i < num_seen && lrand != seen[i]; ++i);

        /* `lrand` has not been seen before. Store and return it. */
        if (i == num_seen) return seen[num_seen++] = lrand;

        lrand += rand_step;
        if (lrand == lower || lrand == upper) rand_step = -rand_step;
    }

    /* Will only happen if `lower` and/or `upper` are set incorrectly. */
    return -1;
}

/* Reimplement strcmp(3), because we cannot use <strings.h>. */
int sub_strcmp(char *a, char *b)
{
    while (*a && *b && *a == *b) a++, b++;
    return *a - *b;
}

/* Reimplement strlen(3), because we cannot use <strings.h>. */
int sub_strlen(char *str)
{
    int len = 0;
    while (str[len]) ++len;
    return len;
}

/* Reimplement isdigit(3), because we cannot use <ctype.h>. */
int sub_isdigit(char d)
{
    /* Make no assumptions. No cute logic like `d > '0' && d < '9'`. */
    return d == '0' || d == '1' || d == '2' || d == '3' || d == '4' ||
           d == '5' || d == '6' || d == '7' || d == '8' || d == '9' ;
}

/* Ensure only +ve values on cmd-line. String and -ve signalled by (-1). */
int get_param_value(char *str)
{
    int i = 0;
    while (str[i] && sub_isdigit(str[i])) ++i;
    return str[i] ? -1 : atoi(str);
}

#define MAX_PARAMS 7
void process_command_line(int argc, char **argv, int *D, int *M, int *N, int *S)
{
    int i;
    char *arg;

    /* Defaults. */
    *D = 4;
    *M = 6;
    *N = 1;
    *S = 0;

    /* We can take at most 7 parameters, + 1 for program name. */
    if (argc > 1 + MAX_PARAMS) goto fail;

    for (i = 1; i < argc; ++i) {
        arg = argv[i];

        /* Nothing but `-` options should be visible immediately. */
             if (!sub_strcmp(arg, "-s")) *S = 1;
        else if (!sub_strcmp(arg, "-d")) *D = get_param_value(argv[++i]);
        else if (!sub_strcmp(arg, "-m")) *M = get_param_value(argv[++i]);
        else if (!sub_strcmp(arg, "-n")) *N = get_param_value(argv[++i]);
        else                             goto fail;
    }

    /* Negative means incorrect input, and we cannot really handle 0, so... */
    if (*D < 1 || *M < 1 || *N < 1) goto fail;

    return;

fail:
    fprintf(stderr, "Usage:\n\t"
                    "crunch [-d <degree>] [-m <size>] [-n <count>] [-s]\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    char s[NUM_STR][CHARS_PER_STR];
    int num_words, i, n, d;

    /* Command-line parameters.
     *  D : Number of words in each crunched output.
     *  M : Minimum number of characters in each word.
     *  N : Number of crunched strings to produce.
     *  S : (boolean) Space out the strings or not.
     */
    int D, M, N, S;

    process_command_line(argc, argv, &D, &M, &N, &S);

    num_words = 0;
    while (num_words < NUM_STR && !feof(stdin) && !ferror(stdin)) {
        /* The `if...continue` construct is to deal with empty files. */
        if (scanf(" %80s ", s[num_words]) != 1) continue;

        /* Word length less than minimum required. Drop it. */
        if (sub_strlen(s[num_words]) < M) continue;

        for (i = 0; i < num_words && sub_strcmp(s[num_words], s[i]); ++i);

        /* Word was not seen before. Move on. It is already stored. */
        if (i == num_words) ++num_words;
    }

    if (D > num_words) {
        fprintf(stderr, "crunch: Cannot satisfy degree and minimum length!\n");
        exit(EXIT_FAILURE);
    }

    /* Seed the RNG with current time.
     * If you're writing a crypto utility, don't quote me.
     */
    srand(time(NULL));

    for (n = 0; n < N; ++n) {
        /* Reset `nr_rand` for each crunch. */
        nr_rand(-1, -1);

        for (d = 0; d < D; ++d)
            printf("%s%s", s[nr_rand(0, num_words - 1)], S ? " " : "");

        /* End each crunch with a newline. */
        putchar('\n');
    }

    return EXIT_SUCCESS;
}
/* end of crunch.c */
