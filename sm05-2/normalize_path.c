#include <stdio.h>
#include "norm_path.h"
#include <ctype.h>

volatile int flag = 0; // first slash

void normalize_path(char *buf)
{
    if (!buf)
        return;

    char *t_buf = buf;

    while (*buf != '\0')
    {
        if (*buf == '/')
        {
            if (!flag)
            {
                flag = 1; // to avoid next slash
                *t_buf = *buf; // slash
                buf++;
                t_buf++;
            }
            else
                buf++; // met slash again, go next
        } else if (!isspace(*buf))
        {
            flag = 0; // to write next slash
            *t_buf = *buf; // not slash
            buf++;
            t_buf++;
        } else {
            buf++;
        }
    }
    *t_buf = '\0'; // end of str
}
