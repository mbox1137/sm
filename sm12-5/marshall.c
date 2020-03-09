#include <stdint.h>
#include <endian.h>
#include "binrev.h"

void unmarshall(struct Data *out, const unsigned char *in) {
    out->x = le16toh(((struct Data*)in)->x);
    out->y = le64toh(((struct Data*)in)->y);
}

void marshall(unsigned char *out, const struct Data *in) {
((struct Data*)out)->x = htole16(in->x);
((struct Data*)out)->y = htole64(in->y);
}
