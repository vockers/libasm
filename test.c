#include "libasm.h"

#include <stdio.h>

int main(void)
{
    char *str = "Hello, World!";
    printf("%zu\n", (size_t)str);
    printf("ft_strlen(\"%s\") = %zu\n", str, ft_strlen(str));
    return 0;
}
