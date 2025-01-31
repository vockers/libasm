#include "../libasm.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
    //
    // Test ft_strlen
    //
    char *str = "Hello, World!";

    assert(ft_strlen(str) == strlen(str));
    assert(ft_strlen("A") == strlen("A"));
    assert(ft_strlen("") == strlen(""));
    assert(ft_strlen(NULL) == 0);

    //
    // Test ft_strcpy
    //
    char dest[100];
    char* dest_ptr = ft_strcpy(dest, "Hello, World!");
    assert(strcmp(dest, "Hello, World!") == 0);
    assert(strlen(dest) == strlen("Hello, World!"));
    assert(dest_ptr == dest);

    dest_ptr = ft_strcpy(dest, "");
    assert(strcmp(dest, "") == 0);
    assert(strlen(dest) == strlen(""));
    assert(dest_ptr == dest);
    
    //
    // Test ft_read
    //
    int fd = open("tests/test.txt", O_RDONLY);

    char buf[256] = {0};

    ssize_t bytes_read = ft_read(fd, buf, 10);
    assert(bytes_read == 10);
    assert(memcmp(buf, "Lorem ipsu", 10) == 0);

    bytes_read = ft_read(fd, NULL, 10);
    assert(bytes_read == -1);
    assert(errno == EFAULT);

    bytes_read = ft_read(fd, buf, 10);
    assert(memcmp(buf, "m dolor si", 10) == 0);

    bytes_read = ft_read(fd, buf, 10);
    assert(bytes_read == 7);
    assert(memcmp(buf, "t amet\n", 7) == 0);

    bytes_read = ft_read(-1, buf, 10);
    assert(bytes_read == -1);
    assert(errno == EBADF);

    close(fd);

    return 0;
}
