#pragma once

#include <stddef.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>

typedef struct s_list
{
    void *data;
    struct s_list *next;
} t_list;

void ft_list_push_front(t_list **begin_list, void *data);
int  ft_list_size(t_list *begin_list);
void ft_list_sort(t_list **begin_list, int (*cmp)());

int ft_atoi_base(char *str, char *base);

ssize_t ft_read(int fd, void* buf, size_t count);
ssize_t ft_write(int fd, const void* buf, size_t count);
int     ft_strcmp(const char* s1, const char* s2);
char*   ft_strcpy(char* dst, const char* src);
char*   ft_strdup(const char* str);
size_t  ft_strlen(const char* str);
