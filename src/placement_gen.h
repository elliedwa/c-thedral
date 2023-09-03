#ifndef CATHEDRAL_PLACEMENT_GEN_H_
#define CATHEDRAL_PLACEMENT_GEN_H_

#include "bitboard.h"
#include "pieces.h"

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
placement_list generate_placements(void);

#endif
