#include <stdio.h>
#include "norm_path.h"

void ans(char *buf)
{
    if (!buf)
        return;

    if (*buf == '\0')
        return;

    char *t_buf = buf;
    while (*buf != '\0')
    {
        ++buf;
        if (*buf == '/')
        {
            if (*buf != *t_buf)
            {
                ++t_buf;
                *t_buf = *buf;
            }
        } else {
            ++t_buf;
            *t_buf = *buf;
        }
    }

    while(*t_buf != '\0')
    {
        ++t_buf;
        *t_buf = '\0';
    }
}
