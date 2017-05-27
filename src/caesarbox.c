#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getstr()
{
    int c;
    size_t n;
    char *s, *t;
    if(!(s = t = malloc(1))) return NULL;
    for(n=0; (c=getchar())!=EOF && c-'\n' && (t=realloc(s, n+2)); s[n++]=c) s=t;
    if(!t){
        free(s);
        return NULL;
    }
    s[n] = '\0';
    return s;
}

void box(char *str, size_t fac)
{
    size_t i, l;

    l = 0;
    while (str[l]) {
        for (i = 0; str[l] && i < fac; ++i, ++l)
            putchar(str[l]), putchar(' ');

        putchar('\n');
    }
    putchar('\n');
}

int main()
{
    size_t i, l;
    char *s;
	
	s = getstr();
    l = strlen(s);

    for (i = l/2; i; --i)
        if (!(l % i))
            box(s, i);

    return 0;
}
