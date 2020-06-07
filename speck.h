#define u64 uint64_t

#if defined (__AVX2__)

#define SPECK_ALIGNED_CTX	32
#include <immintrin.h>
#define u256 __m256i
typedef struct {
        u256 rk[34];
        u64 key[34];
} speck_context_t;

#elif defined (__SSE4_2__)

#define SPECK_ALIGNED_CTX	16
#define SPECK_CTX_BYVAL		 1
#include <immintrin.h>
#define u128 __m128i
typedef struct {
        u128 rk[34];
        u64 key[34];
} speck_context_t;

#elif defined (__ARM_NEON)

#include <arm_neon.h>
#define u128 uint64x2_t
typedef struct {
        u128 rk[34];
        u64 key[34];
} speck_context_t;

#else

typedef struct {
        u64 key[34];
} speck_context_t;

#endif


int speck_ctr (unsigned char *out, const unsigned char *in, unsigned long long inlen,
               const unsigned char *n,
#if defined (SPECK_CTX_BYVAL)
	       speck_context_t ctx);
#else
	       speck_context_t *ctx);
#endif


int speck_expand_key (const unsigned char *k, speck_context_t *ctx);