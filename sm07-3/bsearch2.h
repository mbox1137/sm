//#include <stdlib.h>

struct BSearchResult {
    size_t low;
    size_t hight;
    int result;
};

struct BSearchResult bsearch2(
    const void *key,
    const void *base,
    size_t nmemb,
    size_t size,
    int (*compar)(const void *p1, const void *p2, void *user),
    void *user);
