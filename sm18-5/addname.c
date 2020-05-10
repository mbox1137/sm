void addname(CTRLN *z, char *name) {
    int n;
    if(!name) {
        if(z->names)
            free(z->names);
        if(z->pnames)
            free(z->pnames);
        z->kn=0;
        z->nn=0;
        z->kpn=0;
        z->npn=0;
        return;
    }
    n=strlen(name);
    if(n==0) {
        z->kn=0;
        z->kpn=0;
        return;
    }
    if((z->kn+n+1) >= (z->nn)) {
        if(!z->names) {
            z->nn = 1<<13;
            z->names = malloc(z->nn);
            if(z->names == NULL)
                z->names = NULL;
        } else {
            z->nn *= 2;
            z->names = realloc(z->names, z->nn);
            if(z->names == NULL)
                z->names = NULL;
        }
    }
    if((z->kpn) >= (z->npn)) {
        if(!z->pnames) {
            z->npn = 1<<10;
            z->pnames = malloc((z->npn) * sizeof(int));
            if(z->pnames == NULL)
                z->pnames = NULL;
        } else {
            z->npn *= 2;
            z->pnames = realloc(z->pnames, z->npn*sizeof(int));
            if(z->pnames == NULL)
                z->pnames = NULL;
        }
    }
    (z->pnames)[z->kpn]=z->kn;
    strcpy(&((z->names)[z->kn]),name);
    z->kn += n+1;
    z->kpn++;
}
