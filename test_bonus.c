#include "libasm_bonus.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void test_ft_atoi_base(void)
{
    assert(ft_atoi_base("0", "0123456789") == 0);
    assert(ft_atoi_base("1", "0123456789") == 1);
    assert(ft_atoi_base(" 10", "0123456789") == 10);
    assert(ft_atoi_base("42  ", "0123456789") == 42);
    assert(ft_atoi_base("   100", "0123456789") == 100);

    assert(ft_atoi_base("\n255", "0123456789") == 255);
    assert(ft_atoi_base("1000\t", "0123456789") == 1000);
    assert(ft_atoi_base("\f1234567890", "0123456789") == 1234567890);

    assert(ft_atoi_base("-42", "0123456789") == -42);
    assert(ft_atoi_base("  -100", "0123456789") == -100);
    assert(ft_atoi_base("  +255", "0123456789") == 255);
    assert(ft_atoi_base("  +1000", "0123456789") == 1000);
    assert(ft_atoi_base("  -1234567890", "0123456789") == -1234567890);
    assert(ft_atoi_base("--42", "0123456789") == 42);
    assert(ft_atoi_base("++42", "0123456789") == 42);
    assert(ft_atoi_base("---42", "0123456789") == -42);

    assert(ft_atoi_base("  \n\t \v---+--+1234ab567", "0123456789") == -1234);

    assert(ft_atoi_base("2147483647", "0123456789") == 2147483647);
    assert(ft_atoi_base("-2147483648", "0123456789") == -2147483648);

    // assert(ft_atoi_base("101010", "01") == 42);
    // assert(ft_atoi_base("FF", "0123456789ABCDEF") == 255);
    // assert(ft_atoi_base("FF", "0123456789abcdef") == -1);
    // assert(ft_atoi_base("G", "0123456789ABCDEF") == -1);
}

int main(void)
{
    test_ft_atoi_base();

    return 0;
}
