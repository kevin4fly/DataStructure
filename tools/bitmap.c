#include  "bitmap.h"

void init_bitmap(struct bitmap **bm)
{
    *bm = malloc(sizeof(struct bitmap));
    assert(*bm);
    memset(*bm,0,sizeof(struct bitmap));
}

void set_bit(struct bitmap *bm, int bit_i)
{
    bm->bits[bit_i>>SHIFT_INT] |= 1 << (bit_i & MASK_INT);
}

void clr_bit(struct bitmap *bm, int bit_i)
{
    bm->bits[bit_i>>SHIFT_INT] &= ~(1 << (bit_i & MASK_INT));
}

int test_bit(const struct bitmap *bm, int bit_i)
{
    return bm->bits[bit_i>>SHIFT_INT] & (1 << (bit_i & MASK_INT));
}
