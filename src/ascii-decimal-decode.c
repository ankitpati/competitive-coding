#include <stdio.h>
#include <stdlib.h>

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


int main()
{
    char *s;

    while (*(s = getstr())) {
        putchar(atoi(s));
        free(s);
    }

    return 0;
}
