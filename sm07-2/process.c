#define _GNU_SOURCE

#include <stdlib.h>

int compare(const void *p1, const void *p2, void *user)
{
    int k1 = *((int*)p1);
    int k2 = *((int*)p2);
    int *data = (int*) user;
    return data[k1]-data[k2];
}

void process(size_t count, int *data, int *order)
{
  size_t k;
  for(k = 0; k < count; k++)
    order[k] = k;
  qsort_r(order, count, sizeof(int), compare, (void*)data);
  return;
}
