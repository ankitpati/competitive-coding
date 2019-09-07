#include <stdio.h>

int find_moves(int n)
{
    return 4*n * (n + 3) + 8 + !!n;
}

int main()
{
    int n;
    scanf(" %d%*c", &n);
    printf("%d\n", find_moves(n));
    return 0;
}
