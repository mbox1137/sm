#define _GNU_SOURCE
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct _Data
{
    int16_t x;
    int64_t y;
} __attribute__((packed));

typedef struct _Data _Data;

_Data data [1000005];
char exec_str [1234];

int
main(void)
{
    int n, a;
    scanf("%d%d", &n, &a);
    for (int i = 0; i < n; i++) {
        scanf("%hd%" PRId64, &data[i].x, &data[i].y);
    }
    FILE *f = fopen("kek", "w");
    fwrite(data, sizeof(_Data), n, f);
    fclose(f);
    snprintf(exec_str, 1234, "./5 kek %d", a);
    int code = 0;
    if (code = system(exec_str)) {
        printf("Run finished with code %d\n", code);
    }
    f = fopen("kek", "r");
    fread(data, sizeof(_Data), n, f);
    for (int i = 0; i < n; i++) {
        printf("%hd %" PRId64 "\n", data[i].x, data[i].y);
    }
    fclose(f);

    return 0;
}
