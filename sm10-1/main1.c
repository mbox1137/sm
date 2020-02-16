#include <stdio.h>
#include <inttypes.h>

uint64_t A, B, res;

void process(void);

int main()
{
    if (scanf("%" SCNu64 "%" SCNu64, &A, &B) != 2)
    {
        fprintf(stderr, "not valid input!\n");
        return 1;
    }

    process();

    return 0;
}
