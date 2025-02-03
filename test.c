#include "libasm.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

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

int main(void)
{
    test_ft_strlen();
    test_ft_strcmp();
    test_ft_strcpy();
    test_ft_strdup();
    test_ft_read();
    test_ft_write();

    return 0;
}
