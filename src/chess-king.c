#include <stdio.h>
#include <math.h>

int find_moves(int n)
{
    return n ? pow((n + 1)*2 + 1, 2) : 8;
}

int main()
{
    int n;
    scanf(" %d%*c", &n);
    printf("%d\n", find_moves(n));
    return 0;
}
