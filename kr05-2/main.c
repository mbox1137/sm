#define DEBUG 0

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define DAY 60*60*24

void next_day(struct tm *local_time)
{
    time_t t = mktime(local_time);
    t += DAY;
    local_time = localtime(&t);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        exit(EXIT_FAILURE);

    int year, month;

    if(sscanf(argv[1], "%d", &year) != 1)
        exit(EXIT_FAILURE);
    year -= 1900;

    if(sscanf(argv[2], "%d", &month) != 1)
        exit(EXIT_FAILURE);
    month -= 1;

#if DEBUG
    int lastwday = 0, lastfday = 0;
#endif

    int sum = 0;
    time_t t;
    time(&t);
    struct tm *loc_t = localtime(&t);

    loc_t->tm_year = year;
    loc_t->tm_mon = month;
    loc_t->tm_mday = 28;

    next_day(loc_t);

    sum += 4 * (8 * 4 + 6); // cuz each mon has 28 days at least (4 working weeks)

    while(loc_t->tm_mon == month)
    {

#if DEBUG
        printf("cur_sum = %d\n", sum);
#endif

        if (loc_t->tm_wday != 0 && loc_t->tm_wday != 6) // working days
        {
            if (loc_t->tm_wday == 5)
            {
#if DEGUG
                lastfday = loc_t->tm_mday;
#endif
                sum += 6;
            } else {
#if DEBUG
                lastwday = loc_t->tm_mday;
#endif
                sum += 8;
            }
        }

        next_day(loc_t);
    }

#if DEBUG
    printf("last working day was on %d\n", lastwday);
    printf("last friday was on %d\n", lastfday);
#endif

    printf("%d\n", sum);

    exit(EXIT_SUCCESS);
}
