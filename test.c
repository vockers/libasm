#include "libasm.h"

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

void test_ft_strlen(void)
{
    assert(ft_strlen("Hello, World!") == 13);
    assert(ft_strlen("A") == 1);
    assert(ft_strlen("") == 0);
    assert(ft_strlen(NULL) == 0);
}

void test_ft_strcmp(void)
{
    assert(ft_strcmp("Hello, World!", "Hello, World!") == 0);
    assert(ft_strcmp("Hello, World!", "Hello, World") == 33);
    assert(ft_strcmp("Hello, World", "Hello, World!") == -33);
    assert(ft_strcmp("Hello, World!", "Hello, World!!") == -33);
    assert(ft_strcmp("Hello, World!!", "Hello, World!") == 33);
    assert(ft_strcmp("", "") == 0);
    assert(ft_strcmp("A", "A") == 0);
    assert(ft_strcmp("A", "B") == -1);
    assert(ft_strcmp("B", "A") == 1);
}

void test_ft_strcpy(void)
{
    char dest[100];
    char* dest_ptr = ft_strcpy(dest, "Hello, World!");
    assert(strcmp(dest, "Hello, World!") == 0);
    assert(strlen(dest) == strlen("Hello, World!"));
    assert(dest_ptr == dest);

    dest_ptr = ft_strcpy(dest, "");
    assert(strcmp(dest, "") == 0);
    assert(strlen(dest) == strlen(""));
    assert(dest_ptr == dest);
}

void test_ft_strdup(void)
{
    char *src = "Hello World!";
    char *dst = ft_strdup(src);
    assert(ft_strcmp(src, dst) == 0);
    assert(src != dst);

    src = "";
    dst = ft_strdup(src);
    assert(ft_strcmp(src, dst) == 0);
    assert(src != dst);
}

void test_ft_read()
{
    // Create a temporary test file
    int fd = open("./", O_RDWR | O_TMPFILE, 0644);
    char buf[256] = {0};
    char* str1 = "Lorem ipsum dolor sit amet\n";
    write(fd, str1, strlen(str1));
    lseek(fd, 0, SEEK_SET);

    // Test invalid buffer
    ssize_t bytes_read = ft_read(fd, NULL, 10);
    assert(bytes_read == -1);
    assert(errno == EFAULT);

    bytes_read = ft_read(fd, buf, 10);
    assert(bytes_read == 10);
    assert(memcmp(buf, "Lorem ipsu", 10) == 0);

    bytes_read = ft_read(fd, buf, 10);
    assert(memcmp(buf, "m dolor si", 10) == 0);

    bytes_read = ft_read(fd, buf, 10);
    assert(bytes_read == 7);
    assert(memcmp(buf, "t amet\n", 7) == 0);

    // Test invalid file descriptor
    bytes_read = ft_read(-1, buf, 10);
    assert(bytes_read == -1);
    assert(errno == EBADF);

    close(fd);
    errno = 0;
}

void test_ft_write()
{
    // Create a temporary test file
    int fd = open("./", O_RDWR | O_TMPFILE, 0643);

    // Test invalid buffer
    ssize_t bytes_written = ft_write(fd, NULL, 13);
    assert(bytes_written == -1);
    assert(errno == EFAULT);

    bytes_written = ft_write(fd, "Hello, World!", 13);
    assert(bytes_written == 13);

    lseek(fd, 0, SEEK_SET);

    char buf[256] = {0};
    read(fd, buf, 13);
    assert(memcmp(buf, "Hello, World!", 13) == 0);

    bytes_written = ft_write(fd, "test", 4);
    assert(bytes_written == 4);

    lseek(fd, 13, SEEK_SET);

    ssize_t bytes_read = read(fd, buf, 4);
    assert(memcmp(buf, "test", 4) == 0);

    // Test invalid file descriptor
    bytes_written = ft_write(-1, "Hello, World!", 13);
    assert(bytes_written == -1);
    assert(errno == EBADF);

    close(fd);
    errno = 0;
}

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

void test_ft_list(void)
{
    assert(ft_list_size(NULL) == 0);

    t_list lst;
    lst.data = "First";
    lst.next = NULL;

    t_list *head = &lst;
    assert(ft_list_size(head) == 1);
    ft_list_push_front(&head, "Second");
    assert(strcmp(head->data, "Second") == 0);
    assert(head->next == &lst);
    assert(strcmp(head->next->data, "First") == 0);
    assert(ft_list_size(head) == 2);

    ft_list_push_front(&head, "Third");
    assert(strcmp(head->data, "Third") == 0);
    assert(strcmp(head->next->data, "Second") == 0);
    assert(strcmp(head->next->next->data, "First") == 0);
    assert(head->next->next == &lst);
    assert(ft_list_size(head) == 3);

    ft_list_push_front(&head, "Fourth");
    assert(strcmp(head->data, "Fourth") == 0);
    assert(strcmp(head->next->data, "Third") == 0);
    assert(strcmp(head->next->next->data, "Second") == 0);
    assert(head->next->next->next == &lst);
    assert(ft_list_size(head) == 4);
}

int main(void)
{
    test_ft_strlen();
    test_ft_strcmp();
    test_ft_strcpy();
    test_ft_strdup();
    test_ft_read();
    test_ft_write();
    test_ft_atoi_base();
    test_ft_list();

    return 0;
}
