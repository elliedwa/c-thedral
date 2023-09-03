#ifndef CATHEDRAL_PIECES_H_
#define CATHEDRAL_PIECES_H_

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

#define WHICH_PIECE(x) ((x) & (0x10 - 1))
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

#endif
