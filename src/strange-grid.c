#include <stdio.h>

int main()
{
    size_t r, c;
    scanf("%zu %zu%*c", &r, &c);
    printf("%zu", 5*(r-1) + 2*(c-1) - 4*!(r%2));
    return 0;
}
