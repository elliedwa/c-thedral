#include "placement_gen.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct piece_data {
        enum piece_shape id;
        int symmetry;
        PADDED_BITBOARD_HALF masks[4];
};

static BITBOARD get_placement(enum piece_shape shape, int sym, int shift);


static pl_node *pl_new_node(enum piece_shape shape, BITBOARD board);
static pl_node *pl_add_node(placement_list *pl, enum piece_shape shape,
                     BITBOARD board);
static pl_node *pl_add_shape(placement_list *pl);

static const struct piece_data PIECE_DATA_ARRAY[NUM_PIECE_SHAPES] = {
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
        PADDED_BITBOARD board = {{piece.masks[sym % (piece.symmetry + 1)]}};
        while (shift--) {
                bb_shl(board);
        }
        return board;
}
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
                PADDED_BITBOARD pboard = {
                    {PIECE_DATA_ARRAY[next_shape].masks[0]}};
                BITBOARD board = bb_remove_padding(pboard);
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
                        BITBOARD pb = {{piece.masks[sym], 0}};
                        while (!check_stop_bit(pb)) {
                                if (validate_padded_bitboard(pb)) {
                                        BITBOARD board = bb_remove_padding(pb);
                                        pl_add_node(&pl, cur_shape, board);
                                        num_boards++;
                                }
                                pb = bb_shl(pb);
                        }
                }
                pl.tail = pl.tail->next_shape;
        }
        printf("found %d placements\n", num_boards);

        return pl;
}


