#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    int n = 10;
    int i = 1, j = 0, cnt = 0;
    while (i + j <= n)
    {
        if (i > j) j++;
        else i++;
        cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}