#pragma once

#include <stddef.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>

ssize_t ft_read(int fd, void* buf, size_t count);
ssize_t ft_write(int fd, const void* buf, size_t count);
int     ft_strcmp(const char* s1, const char* s2);
char*   ft_strcpy(char* dst, const char* src);
size_t  ft_strlen(const char* str);
