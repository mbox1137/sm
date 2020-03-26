#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    char *fn=".";
    if(argc > 1)
        fn=argv[1];

    DIR* direct = opendir(fn);

    if (!direct)
    {
        printf("0\n");
        return 0;
    }

    struct dirent* entry;

    unsigned long long sum_size = 0;

    uid_t uid = getuid();

    while ((entry = readdir(direct))!=NULL)
    {
        char buf[PATH_MAX + 1];

        snprintf(buf, PATH_MAX, "%s/%s", fn, entry->d_name);

        struct stat file_stat;

        if (stat(buf, &file_stat) != 0)
            continue;

        if(!(S_ISREG(file_stat.st_mode)))
            continue;

        if(uid != file_stat.st_uid)
            continue;

        if(!(isupper(entry->d_name[0])))
            continue;

//        printf("%s %ld\n", entry->d_name, file_stat.st_size);
        sum_size += file_stat.st_size;

    }

    closedir(direct);

    printf("%llu\n", sum_size);

    return 0;
}
