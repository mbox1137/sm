#include <stdio.h>
#include <string.h>
#include <time.h>

#define NN 1000

int main(int argc, char **argv)
{
    char fn[80]="main.dat";
    FILE *f;
    char str[NN];
    char delim[]=" \t\r\n";
    char *dat, *tim;
    int y, mon, d, h, m, s;
    time_t t0, t, dt;
    struct tm tm;
    if(argc==2)
        sscanf(argv[1],"%s",fn);
    else
        printf("./main [main.dat]\n");
    t0=0;
    f=fopen(fn,"r");
    while(!feof(f)) {
        if (fgets(str, NN, f) == NULL)
            break;
//        printf("Source:\t%s",str);
        dat = strtok(str, delim);
        tim = strtok(NULL, delim);
        printf("Clean:\t%s %s\n", dat, tim);
        sscanf(dat,"%d/%d/%d",&y,&mon,&d);
        sscanf(tim,"%d:%d:%d",&h,&m,&s);
//        printf("Ints:\t%d %d %d %d %d %d\n", y, mon, d, h, m, s);
        tm.tm_sec	= s;		// Seconds (0-60) 
        tm.tm_min	= m;		// Minutes (0-59) 
        tm.tm_hour	= h;		// Hours (0-23) 
        tm.tm_mday	= d;		// Day of the month (1-31) 
        tm.tm_mon	= mon-1;	// Month (0-11) 
        tm.tm_year	= y-1900;	// Year - 1900 
/*
        tm.tm_wday;			// Day of the week (0-6, Sunday = 0) 
        tm.tm_yday;			// Day in the year (0-365, 1 Jan = 0) 
*/
        tm.tm_isdst	= 1;		// Daylight saving time 
        t=mktime(&tm);
        printf("%s", ctime(&t));
        if(t0!=0)
        {
            dt=t-t0;
            printf("%ld\n", dt);
        }
        t0=t;
        printf("\n");
    }
    fclose(f);
    return(0);
}
