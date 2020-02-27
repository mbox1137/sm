//__m128i mul_64x64(__m128i ab, __m128i cd);
__m128i mul64x64(u_int64_t a, u_int64_t b);
__m128i mul64p(u_int64_t a, u_int64_t b);
__m128i mul64r(u_int64_t a, u_int64_t b);

typedef union {
    __m128i v;    // SSE 4 x float vector
    float a[4];  // scalar array of 4 floats
    unsigned char c[16];
} U;

