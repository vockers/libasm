#include "libasm.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *str = "Hello, World!";

    assert(ft_strlen(str) == strlen(str));
    assert(ft_strlen("A") == strlen("A"));
    assert(ft_strlen("") == strlen(""));
    assert(ft_strlen(NULL) == 0);

    return 0;
}
