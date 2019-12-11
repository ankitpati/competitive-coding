/* replace_next_word.c */
/* Date   : 13 March 2019
 * Author : Ankit Pati
 * Licence: GNU GPL v3
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

/* Efficiently read a file into a dynamically allocated string. */
char *bin2str(char *filename, size_t *str_size)
{
    size_t str_index, bytes_read, block_count;
    char *str, *realloc_canary;
    FILE *fin;

    /* Open the file. */
    fin = fopen(filename, "rb");
    if (!fin) return NULL;

    /* We read in blocks of `BUFSIZ` size for performance. */
    block_count = 0;

    /* Allocate the first block. We need something to read into. */
    str = realloc_canary = malloc(BUFSIZ * ++block_count);
    if (!str) return NULL;

    /* We have not read anything yet, so... */
    str_index = 0;

    for (;;) {
        /* Attempt to read `BUFSIZ` bytes. */
        bytes_read = fread(str + str_index, 1, BUFSIZ, fin);

        /* Point `str_index` to a place where we can write next. */
        str_index += bytes_read;

        /* If we don't get `BUFSIZ` bytes, then either we
               1. reached the end of the file, or
               2. encountered an error.
         */
        if (bytes_read != BUFSIZ) break;

        /* Allocate another block for the next read. */
        realloc_canary = realloc(str, BUFSIZ * ++block_count);

        /* If Memory Allocation fails, we must abort. */
        if (!realloc_canary) break;

        /* Use the newly-enlarged memory with the new block. */
        str = realloc_canary;
    }

    /* If a Memory Allocation or I/O error occurs, free up memory & abort. */
    if (!realloc_canary || ferror(fin)) {
        free(str);
        return NULL;
    }

    /* This is binary data, so we must let the caller know where it ends. */
    *str_size = str_index;

    /* We always allocate more memory than we need for the string.
     * At least one byte extra, and at max `BUFSIZ` bytes extra.
     *
     * Let's make use of that to ensure the caller does not trip up if
     * they ignore `str_size` or treat the string as a null-terminated
     * character array. This will not affect those callers who respect
     * the `str_size`, anyways, so it is the safer and saner option.
     *
     * Close the string with a null-character.
     */
    str[str_index] = '\0';

    /* Close the file. */
    fclose(fin);

    return str;
}

/* Reverse of the above. Dump a string into a named file. */
char *str2bin(char *filename, char *str, size_t len)
{
    FILE *fout;

    /* Open the file. */
    fout = fopen(filename, "wb");
    if (!fout) return NULL;

    /* Write everything to the file. */
    fwrite(str, 1, len, fout);

    /* Let the caller know if we failed. */
    if (ferror(fout)) return NULL;

    /* Close the file. */
    fclose(fout);

    return str;
}

/* Replace the word next to the all occurrences of `find`. */
/* ARGUMENTS
 * - str
 *     Must be an malloc(3)-allocated buffer, because resizing may be necessary.
 * - len
 *     Length of the actual data in `str`.
 * - find
 *     Word to search for.
 * - replace_next
 *     Word to replace the next word with.
 *
 * RETURN
 * - Success
 *     Memory address of modified string. May not be same as original.
 * - Failure
 *     `NULL`
 */
char *replace_next_word(char *str, size_t *len, char *find, char *replace_next)
{
    size_t str_i, next_len, replace_len, cp_i, cp_j;
    char *occurrence, *realloc_canary;

    replace_len = strlen(replace_next);

    for (
        str_i = 0;
        (occurrence = memmem(str + str_i, *len, find, strlen(find)));
        str_i += replace_len
    ) {
        str_i = occurrence - str;

        /* Discard current occurrence of `find`. */
        while (*len && !isspace(str[str_i])) --*len, ++str_i;

        /* Discard all whitespace following the current occurrence. */
        while (*len && isspace(str[str_i])) --*len, ++str_i;

        for (next_len = 0; *len && !isspace(str[str_i + next_len]); ++next_len);

        if (replace_len == next_len) {
            /* Do nothing. */
        }

        else if (replace_len < next_len) {
            for (
                cp_i = str_i + replace_len, cp_j = cp_i + next_len;
                cp_j < *len;
                ++cp_i, ++cp_j
            ) str[cp_i] = str[cp_j];

            *len -= cp_i + 1;
        }

        /* Only reallocate if we need more memory, for performance.
         * TODO: Mind the block sizes. */
        else {
            *len += replace_len - next_len;
            realloc_canary = realloc(str, *len + 1);

            /* Memory allocation failed. Free `str`, and bail out! */
            if (!realloc_canary) {
                free(str);
                return NULL;
            }

            str = realloc_canary;

            for (
                cp_i = str_i + *len - 1, cp_j = cp_i - replace_len + next_len;
                cp_j >= str_i + next_len;
                --cp_i, --cp_j
            ) str[cp_i] = str[cp_j];
        }

        /* Copy replacement string to the space previously held by next word. */
        memcpy(str + str_i, replace_next, replace_len);
    }

    str[*len] = '\0';
    return str;
}

int main(int argc, char **argv)
{
    size_t len;
    char *str, *filename, *find, *replace_next;

    /* Check if
     * - Filename,
     * - String to Find, and
     * - String to Replace Next Word With
     * are given on the command line. */
    if (argc != 4) {
        fprintf(stderr, "Usage:\n\t"
                        "replace_next_word <filename> <find> <replace-next>\n");
        exit(EXIT_FAILURE);
    }

    filename = argv[1];
    find = argv[2];
    replace_next = argv[3];

    str = bin2str(filename, &len);

    /* I/O & Memory Allocation are error-prone. Check if they failed. */
    if (!str)
        fprintf(stderr, "%s: Could not read file!\n", filename);

    /* Perform the replacement. */
    replace_next_word(str, &len, find, replace_next);

    /* Dump the changed string back into the file. */
    if (!str2bin(filename, str, len))
        fprintf(stderr, "%s: Could not write file!\n", filename);

    /* `str` is dynamically allocated. free(3) after use. */
    free(str);

    return EXIT_SUCCESS;
}
/* end of replace_next_word.c */
