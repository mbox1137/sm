#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
        return 1;

    DIR* direct = opendir(argv[1]);

    if (!direct)
    {
        printf("0\n");
        return 0;
    }

    struct dirent* entry = readdir(direct);

    unsigned long long sum_size = 0;

    uid_t uid = getuid();

    while (entry)
    {
        char buf[PATH_MAX + 1];

        snprintf(buf, PATH_MAX, "%s/%s", argv[1], entry->d_name);

        struct stat file_stat;

        if (stat(buf, &file_stat) != 0)
            continue;

        if(!(S_ISREG(file_stat.st_mode)))
            continue;

        if(uid != file_stat.st_uid)
            continue;

        if(!(isupper(entry->d_name[0])))
            continue;

        sum_size += file_stat.st_size;

        entry = readdir(direct);
    }

    closedir(direct);

    printf("%llu\n", sum_size);

    return 0;
}
