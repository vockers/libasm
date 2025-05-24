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

int ft_atoi_base(char *str, char *base);
