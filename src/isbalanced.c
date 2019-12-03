/* isbalanced.c */
/* Date   : 08 March 2019
 * Author : Ankit Pati
 * Licence: GNU GPL v3
 */

/* CAVEATS:
 * 1. Only works on ASCII.
 * 2. Silently gives erroneous results with UTF-8.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define CONTEXT 5

char *stack;
size_t top;

void push(char item)
{
    stack = realloc(stack, top++);
    if (!stack) {
        fprintf(stderr, "Cannot allocate memory!\n");
        exit(12);
    }

    stack[top - 1] = item;
}

char pop()
{
    return top ? stack[--top] : '\0';
}

int read_chunk(FILE *fin, char *str)
{
    int bytes_read;
    bytes_read = fread(str, 1, BUFSIZ, fin);
    if (ferror(fin)) return -1;
    return bytes_read;
}

int main(int argc, char **argv)
{
    int file_indx, bytes_read, ctx_indx, str_indx;
    char str[BUFSIZ], *filename, current_char, popped_char;
    FILE *fin;

    /* Check if at least one <filename> is given. */
    if (argc < 2) {
        fprintf(stderr, "Usage:\n\tisbalanced <filename>...\n");
        exit(1);
    }

    /* Process multiple files given on the command-line. */
    for (file_indx = 1; file_indx < argc; ++file_indx) {
        filename = argv[file_indx];

        fin = fopen(filename, "r");
        if (!fin) {
            fprintf(stderr, "Unable to open %s!\n", filename);
            continue;
        }

        while ((bytes_read = read_chunk(fin, str)) > 0) {
            for (str_indx = 0; str_indx < bytes_read; ++str_indx) {
                current_char = str[str_indx];

                switch (current_char) {
                case '(': case '{': case '[':
                    push(current_char);
                    break;

                case ')':
                    if (pop() != '(') goto fail;
                    break;

                case '}':
                    if (pop() != '{') goto fail;
                    break;

                case ']':
                    if (pop() != '[') goto fail;
                    break;
                }
            }
        }

        popped_char = pop();
        if (popped_char)
            printf("%s imbalanced w.r.t %c.\n", filename, popped_char);

        while (pop());
        fclose(fin);
        continue;

    fail:
        printf("%s imbalanced w.r.t %c. Context: ", filename, current_char);

        for (
            ctx_indx = 0, ++str_indx;
            ctx_indx < CONTEXT && str_indx < bytes_read;
            ++str_indx
        ) {
            current_char = str[str_indx];
            if (!isspace(current_char)) {
                putchar(current_char);
                ++ctx_indx;
            }
        }

        while (ctx_indx < CONTEXT && !feof(fin) && !ferror(fin))
            if ((current_char = fgetc(fin)) != EOF && !isspace(current_char)) {
                putchar(current_char);
                ++ctx_indx;
            }

        putchar('\n');

        while (pop());
        fclose(fin);
    }

    return 0;
}
/* end of isbalanced.c */
