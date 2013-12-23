#include  <stdlib.h>
#include  <assert.h>
#include  <string.h>

#define   BITSPER_INT     32
#define   SHIFT_INT       5
#define   MASK_INT        0x1f
#define   BITS            10000000

struct bitmap
{
    int bits[BITS/BITSPER_INT];
};

void init_bitmap(struct bitmap **bm);
void set_bit(struct bitmap *bm, int bit_i);
void clr_bit(struct bitmap *bm, int bit_i);
int test_bit(const struct bitmap *bm, int bit_i);
