/* jailjump.c */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;
    size_t j, climb, slide, height, jumps, reached, answer;

    if (argc < 3) {
        fprintf(stderr,
                "Usage:\n\tjailjump <climb> <slide> [wall height]...\n");
        return 1;
    }

    climb = strtoull(argv[1], NULL, 10);
    slide = strtoull(argv[2], NULL, 10);

    answer = 0;

    for (i = 3; i < argc; ++i) {
        if (climb < (height = strtoull(argv[i], NULL, 10)) && climb <= slide) {
            answer = ~0ull;
            break;
        }

        for (j = jumps = reached = 0; reached < height; ++j) {
            if (j % 2)
                reached -= slide;
            else {
                ++jumps;
                reached += climb;
            }

            if (reached >= height) break;
        }

        answer += jumps;
    }

    printf(answer == ~0ull ? "Jumps: infinite\n" : "Jumps: %zu\n", answer);

    return 0;
}
