void initBoard(enum pieceType* board, int dim) {
    board->dimension = dim;

    for (int x = 0; x < dim; x++) {
        for (int y = 0; y < dim; y++) {
            board->cases[x][y] = empty;
        }
    }

    for (int x = dim; x < 12; x++) {
        for (int y = dim; y < 12; y++) {
            board->cases[x][y] = out;
        }
    }
};