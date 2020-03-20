struct S
{
    struct S *next;
    int z[2];
    int y[2];
};

uint32_t process(struct S *p) __attribute__((regparm(1)));
