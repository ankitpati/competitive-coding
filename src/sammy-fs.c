/* User Code */
#include <malloc.h>

void my_strcpy(char *dst, char *src)
{
    while ((*dst++ = *src++));
}

int my_strcmp(char *a, char *b)
{
    while (*a && *b && *a == *b) ++a, ++b;
    return *a - *b;
}

void init()
{
}

void createUser(char *userName, char *groupName)
{
}

int createDirectory(char *userName, char *path, char *directoryName, int permission)
{
}

int createFile(char *userName, char *path, char *fileName, char *fileExt)
{
}

int find(char *userName, char *pattern)
{
}
/* End of User Code */

/* Main Code */
#include <stdio.h>

static int run(int ans)
{
    int i, n; /* counters */
    int permission, expectedAnswer, type, userAnswer;
    char userName[8], groupName[8], path[500], directoryName[8], fileName[8], fileExt[8], pattern[500];

    scanf(" %d%*c", &n);
    init();

    for (i = 0; i < n; ++i) {
        scanf(" %d%*c", &type);

        switch (type) {
            case 1:
                scanf(" %s %s%*c", userName, groupName);
                createUser(userName, groupName);
                break;

            case 2:
                scanf(" %s %s %s %d%*c", userName, path, directoryName, &permission);
                userAnswer = createDirectory(userName, path, directoryName, permission);

                scanf(" %d%*c", &expectedAnswer);
                if (userAnswer != expectedAnswer)
                    ans = 0;

                break;

            case 3:
                scanf(" %s %s %s %s%*c", userName, path, fileName, fileExt);
                userAnswer = createFile(userName, path, fileName, fileExt);

                scanf(" %d%*c", &expectedAnswer);
                if (userAnswer != expectedAnswer)
                    ans = 0;

                break;

            default:
                break;
        }
    }

    return ans;
}

int main()
{
    int tc, t, ans;

    scanf(" %d %d%*c", &t, &ans);
    for (tc = 1; tc <= t; ++tc)
        printf("#%d %d\n", tc, run(ans));

    return 0;
}
/* End of Main Code */
