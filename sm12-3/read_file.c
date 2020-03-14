#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4096
#define ZERO '\0'

struct FileContent
{
    ssize_t size;
    char *data;
};

struct FileContent read_err(struct FileContent content);

struct FileContent read_file(int fd)
{
    struct FileContent content = {0, NULL};
    //content.size = 0;
    //content.data = NULL;

    char buf[BUFSIZE];
    int success;

    while (success = read(fd, buf, BUFSIZE))
    {
        if (success < 0)
            return read_err(content);

        char* temp = realloc(content.data, content.size + success);
        if (temp == NULL)
            return read_err(content);

        content.data = temp;
        memcpy(content.data + content.size, buf, success);
        content.size += success;
    }

    char* temp = realloc(content.data, content.size + 1);
    if (temp == NULL)
        return read_err(content);

    content.data = temp;
    content.data[content.size] = ZERO;

    return content;
}

struct FileContent read_err(struct FileContent content)
{
    free(content.data);
    content.size = -1;
    content.data = NULL;

    return content;
}
