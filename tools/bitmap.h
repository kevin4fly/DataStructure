#ifndef  BITMAP_H
#define  BITMAP_H

#include  <stdlib.h>
#include  <assert.h>
#include  <string.h>

#define   BITS_PER_INT     32
#define   SHIFT_INT       5
#define   MASK_INT        0x1f
#define   BITS            10000000

/**< a simple bitmap implementation
 * .bits: total bits of a bitmap
 *
 * */
struct bitmap
{
    int bits[BITS/BITS_PER_INT+1];
};

void bitmap_init(struct bitmap **bm);
void set_bit(struct bitmap *bm, int bit_i);
void clr_bit(struct bitmap *bm, int bit_i);
int test_bit(const struct bitmap *bm, int bit_i);
void bitmap_destroy(struct bitmap *bm);

#endif  /*BITMAP_H*/
