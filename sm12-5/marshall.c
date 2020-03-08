#include <stdint.h>
#include <endian.h>
#include "binrev.h"

void unmarshall(struct Data *out, const unsigned char *in) {
union {
    struct Data d;
    unsigned char c[sizeof(struct Data)]
    } du;
le16toh();
le64toh();
}

void marshall(unsigned char *out, const struct Data *in) {
htole16();
htole64();
}
