struct Data
{
    int16_t x; // 2 байта,
    int64_t y; // 8 байт
};

void marshall(unsigned char *out, const struct Data *in);
void unmarshall(struct Data *out, const unsigned char *in);
