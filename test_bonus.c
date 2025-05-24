#include "libasm_bonus.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define TEST_ATOI_BASE(str, base, expected) \
    { \
        int result = ft_atoi_base(str, base); \
        assert(result == expected); \
    } \

void test_ft_atoi_base(void)
{
    TEST_ATOI_BASE("", "0123456789", 0);
    TEST_ATOI_BASE("0", "0123456789", 0);
    TEST_ATOI_BASE("1", "0123456789", 1);
    TEST_ATOI_BASE("42", "0123456789", 42);
    TEST_ATOI_BASE("100", "0123456789", 100);
    TEST_ATOI_BASE("255", "0123456789", 255);

    // Test whitespace handling
    TEST_ATOI_BASE(" 10", "0123456789", 10);
    TEST_ATOI_BASE("42  ", "0123456789", 42);
    TEST_ATOI_BASE("  100", "0123456789", 100);
    TEST_ATOI_BASE("\n255", "0123456789", 255);
    TEST_ATOI_BASE("1000\t", "0123456789", 1000);
    TEST_ATOI_BASE("\f1234567890", "0123456789", 1234567890);

    // Mixed whitespace and signs
    TEST_ATOI_BASE("  -42", "0123456789", -42);
    TEST_ATOI_BASE("  +100", "0123456789", 100);
    TEST_ATOI_BASE("  +255", "0123456789", 255);
    TEST_ATOI_BASE("  -1000", "0123456789", -1000);
    TEST_ATOI_BASE("  -1234567890", "0123456789", -1234567890);
    TEST_ATOI_BASE("--42", "0123456789", 42);
    TEST_ATOI_BASE("++42", "0123456789", 42);
    TEST_ATOI_BASE("---42", "0123456789", -42);
    TEST_ATOI_BASE("  \n\t \v---+--+1234ab567", "0123456789", -1234);

    // Test minimum and maximum integer values
    TEST_ATOI_BASE("-2147483648", "0123456789", -2147483648);
    TEST_ATOI_BASE("2147483647", "0123456789", 2147483647);

    // Base with less than 2 characters
    TEST_ATOI_BASE("42", "", 0);
    TEST_ATOI_BASE("42", "0", 0);
    // Base with invalid characters (whitespace, '-', '+')
    TEST_ATOI_BASE("42", "01-", 0); // Invalid characters in base
    TEST_ATOI_BASE("42", "+0123456789", 0); // Invalid characters in base
    // Check for duplicate characters in base
    TEST_ATOI_BASE("42", "01234567890", 0);
    TEST_ATOI_BASE("42", "011", 0);
    TEST_ATOI_BASE("42", "01231", 0);

    // Base16
    TEST_ATOI_BASE("42", "0123456789abcdef", 66);
    TEST_ATOI_BASE("42", "0123456789ABCDEF", 66);
    TEST_ATOI_BASE("FF", "0123456789ABCDEF", 255);
    TEST_ATOI_BASE("10g1", "0123456789abcdef", 16);
    TEST_ATOI_BASE("FF", "0123456789abcdef", 0);
    TEST_ATOI_BASE("FF", "0123456789abcdeF", 255);
    TEST_ATOI_BASE("1e", "0123456789abcdef", 30);
    TEST_ATOI_BASE("100", "0123456789abcdeF", 256);
    TEST_ATOI_BASE("10e", "0123456789abcdeF", 270);
    // Base 17
    TEST_ATOI_BASE("G", "0123456789ABCDEFG", 16);
    TEST_ATOI_BASE("GG", "0123456789ABCDEFG", 288);
    TEST_ATOI_BASE("101", "0123456789ABCDEFG", 290);
    // Binary base
    TEST_ATOI_BASE("101010", "01", 42);
    TEST_ATOI_BASE("010101", "10", 42);
    TEST_ATOI_BASE("101011", "01", 43);
    // Base 8
    TEST_ATOI_BASE("52", "01234567", 42);
}

int main(void)
{
    test_ft_atoi_base();

    return 0;
}
