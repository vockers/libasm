#pragma once

#include <stddef.h>
#include <unistd.h>

ssize_t ft_read(int fd, void* buf, size_t count);
char*   ft_strcpy(char* dst, const char* src);
size_t  ft_strlen(const char* str);
