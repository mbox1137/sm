#define DEBUG 0

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
        exit(EXIT_FAILURE);

    char *fn, *min_fn = "";
    fn = argv[1];

    DIR* direct = opendir(fn);

    if (direct == NULL)
        exit(EXIT_FAILURE);

    struct dirent* entry;

    int flag = 0;
    long long max_size, max_file, sum_size = 0;

    if (sscanf(argv[2], "%lld", &max_size) != 1)
        exit(EXIT_FAILURE);

    while ((entry = readdir(direct)) != NULL)
    {
        char buf[PATH_MAX + 1];
        snprintf(buf, PATH_MAX, "%s/%s", fn, entry->d_name);

        struct stat file_stat;

        if (lstat(buf, &file_stat) != 0)
            continue;
        if (!(S_ISREG(file_stat.st_mode)))
            continue;
        if (S_ISLNK(file_stat.st_mode))
            continue;

        if (!flag)
        {
            flag = 1;
            max_file = file_stat.st_size;
            min_fn = entry->d_name;
        }

        if (file_stat.st_size >= max_file)
        {
            if (file_stat.st_size == max_file)
            {
                if (strcmp(min_fn, entry->d_name) > 0)
                    min_fn = entry->d_name;
            } else {
                max_file = file_stat.st_size;
                min_fn = entry->d_name;
            }
        }

        sum_size += file_stat.st_size;

#if DEBUG
        printf("cur_file = %s\n", entry->d_name);
        printf("cur_size = %lld\n", sum_size);
        printf("cur_max  = %s\n\n", min_fn);
#endif
    }

    closedir(direct);

    if (sum_size > max_size)
        printf("%s\n", min_fn);

    exit(EXIT_SUCCESS);
}
