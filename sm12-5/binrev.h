//https://habr.com/ru/post/142662/
#pragma pack(push, 1)
struct Data
{
    int16_t x; // 2 байта,
    int64_t y; // 8 байт
};
#pragma pack(pop)

void marshall(unsigned char *out, const struct Data *in);
void unmarshall(struct Data *out, const unsigned char *in);
