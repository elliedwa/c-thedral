#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define VAR_TO_STR_BIN(x)                                                      \
        obj_to_bin((char[sizeof(x) *CHAR_BIT + 1]){""}, &(x), sizeof(x))

char *
obj_to_bin(char *dest, const void *object, size_t osize)
{
        const unsigned char *p = (const unsigned char *)object;
        p += osize;
        char *s = dest;
        while (osize-- > 0) {
                p--;
                unsigned i = CHAR_BIT;
                while (i-- > 0) {
                        *s++ = ((*p >> i) & 1) + '0';
                }
        }
        *s = '\0';
        return dest;
}

#define NUM_ROWS 10
#define NUM_COLS 10
#define NUM_SQUARES (NUM_ROWS * NUM_COLS)


typedef struct {
        uint64_t bb[2];
} BITBOARD;

/* const BITBOARD OFFBOARD_MASK = {{0xffc0080100200400, 0xffc0080100200400}}; */
const uint64_t PADDING_BITS  = 0x40080100200400;
const uint64_t OVERFLOW_BIT  = (1ULL << 55);
const uint64_t ILLEGAL_MASK  = PADDING_BITS | OVERFLOW_BIT;
const uint64_t PIECES_BITS   = 0xff00000000000000;
const uint64_t OFFBOARD_MASK = ILLEGAL_MASK | PIECES_BITS;

/* this really only works one shift at a time, but that's all we need */
BITBOARD
bb_shl(BITBOARD board)
{

        BITBOARD res = {{board.bb[0] << 1, board.bb[1] << 1}};
        if (res.bb[0] & OVERFLOW_BIT) {
                res.bb[0] ^=
                    OVERFLOW_BIT; /* remove the bit from first half... */
                res.bb[1] |= 1;   /*  ... and add it to second half */
        }
        return res;
}

BITBOARD
bb_not(BITBOARD board)
{
        BITBOARD res = {{~board.bb[0], ~board.bb[1]}};
        return res;
}

BITBOARD
bb_and(BITBOARD lhs, BITBOARD rhs)
{
        BITBOARD res = {{lhs.bb[0] & rhs.bb[0], lhs.bb[1] & rhs.bb[1]}};
        return res;
}

BITBOARD
bb_or(BITBOARD lhs, BITBOARD rhs)
{
        BITBOARD res = {{lhs.bb[0] | rhs.bb[0], lhs.bb[1] | rhs.bb[1]}};
        return res;
}

BITBOARD
bb_xor(BITBOARD lhs, BITBOARD rhs)
{
        BITBOARD res = {{lhs.bb[0] ^ rhs.bb[0], lhs.bb[1] ^ rhs.bb[1]}};
        return res;
}

bool
validate_bitboard(BITBOARD board)
{
        return !((board.bb[0] & PADDING_BITS) || (board.bb[1] & PADDING_BITS));
}

bool
check_stop_bit(BITBOARD board)
{
        return (board.bb[1] & OVERFLOW_BIT);
}

void
print_bitboard_half(uint64_t half)
{
        uint64_t printable = ~OFFBOARD_MASK;
        int i              = 0;
        while (printable) {
                if (++i % 11 == 0) {
                        printf("\n");
                }
                if (printable & 1) {
                        putchar('0' + (char)(half & 1));
                }
                half >>= 1;
                printable >>= 1;
        }
        putchar('\n');
}

void
print_bitboard(BITBOARD *board)
{
        print_bitboard_half(board->bb[0]);
        print_bitboard_half(board->bb[1]);
}

enum piece {
        LIGHT_TAVERN_1,
        LIGHT_TAVERN_2,
        LIGHT_STABLE_1,
        LIGHT_STABLE_2,
        LIGHT_INN_1,
        LIGHT_INN_2,
        LIGHT_BRIDGE,
        LIGHT_SQUARE,
        LIGHT_ABBEY,
        LIGHT_MANOR,
        LIGHT_TOWER,
        LIGHT_CASTLE,
        LIGHT_INFIRMARY,
        LIGHT_ACADEMY,
        NUM_PIECES_PER_SIDE,
        DARK_TAVERN_1 = 0x10,
        DARK_TAVERN_2,
        DARK_STABLE_1,
        DARK_STABLE_2,
        DARK_INN_1,
        DARK_INN_2,
        DARK_BRIDGE,
        DARK_SQUARE,
        DARK_ABBEY,
        DARK_MANOR,
        DARK_TOWER,
        DARK_CASTLE,
        DARK_INFIRMARY,
        DARK_ACADEMY,
};

enum piece_shape {
        SHAPE_TAVERN,
        SHAPE_STABLE,
        SHAPE_INN,
        SHAPE_BRIDGE,
        SHAPE_SQUARE,
        SHAPE_ABBEY_LIGHT,
        SHAPE_ABBEY_DARK,
        SHAPE_MANOR,
        SHAPE_TOWER,
        SHAPE_CASTLE,
        SHAPE_INFIRMARY,
        SHAPE_ACADEMY_LIGHT,
        SHAPE_ACADEMY_DARK,
        SHAPE_CATHEDRAL,
        NUM_PIECE_SHAPES
};

struct piece_data {
        enum piece_shape id;
        int symmetry;

        uint64_t masks[4];
};

#define CATHEDRAL_HEIGHT 0 /* why waste a bit for only one piece? */
#define REAL_CATHEDRAL_HEIGHT 4

const struct piece_data PIECE_DATA_ARRAY[NUM_PIECE_SHAPES] = {
    {SHAPE_TAVERN, 0, {0x1}},
    {SHAPE_STABLE, 1, {0x801, 0x3}},
    {SHAPE_INN, 3, {0x1801, 0x803, 0x1003, 0x1802}},
    {SHAPE_BRIDGE, 1, {0x400801, 0x7}},
    {SHAPE_SQUARE, 0, {0x1803}},
    {SHAPE_ABBEY_LIGHT, 1, {0x801801, 0x1806}},
    {SHAPE_ABBEY_DARK, 1, {0x401802, 0x3003}},
    {SHAPE_MANOR, 3, {0x3802, 0x401801, 0x1007, 0x801802}},
    {SHAPE_TOWER, 3, {0xc03004, 0x1801801, 0x401806, 0x1003003}},
    {SHAPE_INFIRMARY, 0, {0x803802}},
    {SHAPE_CASTLE, 3, {0xc01003, 0x3805, 0xc00803, 0x2807}},
    {SHAPE_ACADEMY_LIGHT, 3, {0x1801802, 0x403802, 0x803003, 0x803804}},
    {SHAPE_ACADEMY_DARK, 3, {0xc03002, 0x803801, 0x801806, 0x1003802}},
    {SHAPE_CATHEDRAL, 0, {0x400803802}}};

BITBOARD
get_placement(enum piece_shape shape, int sym, int shift)
{
        struct piece_data piece = PIECE_DATA_ARRAY[shape];
        assert(sym >= 0 && sym < 4);
        BITBOARD board = {{piece.masks[sym % (piece.symmetry + 1)]}};
        while (shift--) {
                bb_shl(board);
        }
        return board;
}

typedef struct pl_node_s {
        enum piece_shape shape;
        BITBOARD board;
        struct pl_node_s *next_board;
        struct pl_node_s *next_shape;
} pl_node;

typedef struct {
        pl_node *head;
        pl_node *tail;
} placement_list;

pl_node *
pl_new_node(enum piece_shape shape, BITBOARD board)
{
        pl_node *node    = malloc(sizeof(pl_node));
        node->shape      = shape;
        node->board      = board;
        node->next_board = NULL;
        node->next_shape = NULL;
        return node;
}

pl_node *
pl_add_node(placement_list *pl, enum piece_shape shape, BITBOARD board)
{
        pl_node *old_tail = pl->tail;
        if (!old_tail) {
                return NULL;
        }
        pl_node *new_node    = pl_new_node(shape, board);
        new_node->next_shape = old_tail->next_shape;
        old_tail->next_board = new_node;
        pl->tail             = new_node;

        return new_node;
}

pl_node *
pl_add_shape(placement_list *pl)
{
        pl_node *last_shape         = pl->tail;
        enum piece_shape next_shape = last_shape->shape + 1;
        pl_node *new_shape;
        if (next_shape < NUM_PIECE_SHAPES) {
                BITBOARD board = {{PIECE_DATA_ARRAY[next_shape].masks[0]}};
                new_shape      = pl_new_node(next_shape, board);
        }
        else {
                new_shape = NULL;
        }
        last_shape->next_shape = new_shape;
        pl->tail               = new_shape;
        return new_shape;
}

placement_list
generate_placements(void)
{
        placement_list pl = {NULL, NULL};

        pl_node *HEAD     = pl_new_node(0, get_placement(0, 0, 0));
        pl.head           = HEAD;
        pl.tail           = HEAD;
        pl_node *shape;
        while ((shape = pl_add_shape(&pl))) {
                printf("Added shape %d\n", shape->shape);
        }
        pl.tail        = pl.head;
        int num_boards = 0;
        while (pl.tail) {
                enum piece_shape cur_shape = pl.tail->shape;
                struct piece_data piece    = PIECE_DATA_ARRAY[cur_shape];
                for (int sym = 0; sym <= piece.symmetry; sym++) {
                        BITBOARD board = {{piece.masks[sym], 0}};
                        while (!check_stop_bit(board)) {
                                if (validate_bitboard(board)) {
                                        pl_add_node(&pl, cur_shape, board);
                                        num_boards++;
                                        print_bitboard(&board);
                                        printf("\n");
                                }
                                board = bb_shl(board);
                        }
                        /* print_bitboard(&board); */
                        /* printf("\n"); */
                }
                pl.tail = pl.tail->next_shape;
        }
        printf("found %d placements\n", num_boards);

        return pl;
}

int
main(void)
{
        int num_boards = 0;
        generate_placements();
        /* for (size_t i = 0; i < NUM_PIECE_SHAPES; i++) { */
        /*         struct piece_data piece = PIECE_DATA_ARRAY[i]; */
        /*         for (int sym = 0; sym <= piece.symmetry; sym++) { */
        /*                 BITBOARD board = {{piece.masks[sym], 0}}; */
        /*                 while (!check_stop_bit(board)) { */
        /*                         if (validate_bitboard(board)) { */
        /*                                 num_boards++; */
        /*                         } */
        /*                         board = bb_shl(board); */
        /*                 } */
        /*                 /\* print_bitboard(&board); *\/ */
        /*                 /\* printf("\n"); *\/ */
        /*         } */
        /* } */
        /* printf("%d placements found\n", num_boards); */
        return 0;
}
