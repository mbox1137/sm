int mysystem(const char *str);
typedef struct {
    char *names;
    int *pnames;
    int kn;
    int nn;
    int kpn;
    int npn;
    } CTRLN;
void addname(CTRLN *z, char *name);
