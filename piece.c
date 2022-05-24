enum pieceType {
    out,
    empty,
    pawn,
    bishop,
    knight,
    rook,
    queen,
    king
};

struct piece
{
    int pos[2];
    enum pieceType type;
};

typedef struct piece piece;