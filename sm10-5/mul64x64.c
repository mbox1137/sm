//https://stackoverflow.com/questions/17863411/sse-multiplication-of-2-64-bit-integers

#include <emmintrin.h>

/*
 * Grid/long multiply two 64-bit SSE lanes.
 * Works for both signed and unsigned.
 *   ----------------.--------------.----------------.
 *  |                |   b >> 32    | a & 0xFFFFFFFF |
 *  |----------------|--------------|----------------|  
 *  | d >> 32        |   b*d << 64  |    a*d << 32   |
 *  |----------------|--------------|----------------|
 *  | c & 0xFFFFFFFF |   b*c << 32  |       a*c      |
 *  '----------------'--------------'----------------'
 *  Add all of them together to get the product.
 *
 *  Because we truncate the value to 64 bits, b*d << 64 will be zero,
 *  so we can leave it out.
 *
 *  We also can add a*d and b*c first and then shift because of the
 *  distributive property: (a << 32) + (b << 32) == (a + b) << 32.
 */

__m128i mul_64x64(__m128i ab, __m128i cd)
{
    /* ac = (ab & 0xFFFFFFFF) * (cd & 0xFFFFFFFF); */
    __m128i ac = _mm_mul_epu32(ab, cd);

    /* b = ab >> 32; */
    __m128i b = _mm_srli_epi64(ab, 32);

    /* bc = b * (cd & 0xFFFFFFFF); */
    __m128i bc = _mm_mul_epu32(b, cd);

    /* d = cd >> 32; */
    __m128i d = _mm_srli_epi64(cd, 32);

    /* ad = (ab & 0xFFFFFFFF) * d; */
    __m128i ad = _mm_mul_epu32(ab, d);

    /* high = bc + ad; */
    __m128i high = _mm_add_epi64(bc, ad);

    /* high <<= 32; */
    high = _mm_slli_epi64(high, 32);

    /* return ac + high; */
    return _mm_add_epi64(high, ac);
}

__m128i mul64x64(int64_t x, int64_t y) {
    __m128i ab, cd;
/*
    ab=_mm_cvtsi64_si128(x);
    cd=_mm_cvtsi64_si128(y);
*/
    return(mul_64x64(ab, cd));
}
