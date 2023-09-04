#ifndef CATHEDRAL_BITBOARD_H_
#define CATHEDRAL_BITBOARD_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define NUM_ROWS 10
#define NUM_COLS 10
#define NUM_SQUARES (NUM_ROWS * NUM_COLS)
#define PADDED_ROW_LENGTH (NUM_COLS + 1)

typedef struct {
        uint64_t bb[2];
} BITBOARD;

typedef BITBOARD PADDED_BITBOARD;
typedef uint64_t BITBOARD_HALF;
typedef BITBOARD_HALF PADDED_BITBOARD_HALF;

static const PADDED_BITBOARD_HALF PADDING_BITS        = 0x40080100200400;
static const PADDED_BITBOARD_HALF OVERFLOW_BIT        = (1ULL << 55);
static const PADDED_BITBOARD_HALF PADDED_ILLEGAL_MASK = PADDING_BITS | OVERFLOW_BIT;
static const PADDED_BITBOARD_HALF PADDED_PIECES_BITS  = 0xff00000000000000;
static const PADDED_BITBOARD_HALF PADDED_OFFBOARD_MASK =
    PADDED_ILLEGAL_MASK | PADDED_PIECES_BITS;

static const BITBOARD_HALF PIECES_BITS = 0xfffc000000000000;

static const uint64_t ROW_MASK = (1ULL << NUM_COLS) - 1;

BITBOARD bb_shl(BITBOARD board);
BITBOARD bb_not(BITBOARD board);
BITBOARD bb_and(BITBOARD lhs, BITBOARD rhs);
BITBOARD bb_or(BITBOARD lhs, BITBOARD rhs);
BITBOARD bb_xor(BITBOARD lhs, BITBOARD rhs);
bool bb_empty(BITBOARD board);
bool validate_padded_bitboard(PADDED_BITBOARD board);
bool check_stop_bit(PADDED_BITBOARD board);
BITBOARD_HALF bb_half_remove_padding(PADDED_BITBOARD_HALF half);
BITBOARD bb_remove_padding(PADDED_BITBOARD board);

void DEBUG_print_bitboard_hex(BITBOARD b);

#endif
