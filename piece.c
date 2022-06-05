//Enum pour le type de piece
enum pieceType {
    out = 0,
    empty = 1,
    pawn = 2,
    bishop = 3,
    knight = 4,
    rook = 5,
    queen = 6,
    king = 7
};

//Structure d'une piece (type + couleur)
typedef struct {
    int type;
    int color;
} piece;

