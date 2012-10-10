#ifndef _OTHELLO_BOARD_H_
#define _OTHELLO_BOARD_H_
#include "common.h"
#include "transform.h"           // Flipper

/* One square on the board. */
typedef struct {
        enum { EMPTY, BLACK, WHITE } disk;
        struct { int dark; int light; } score;
        Bool flipping;
        Flipper *flipper;
} Square;

/**
 * Square size in OpenGL world units.
 *
 * Square size is a convenient unit when placing lights and camera around
 * the board.  A value of one is a no-op, so it could be optimized out
 * (likely, the compiler does that).  But, since we've gone through the
 * trouble of having all the calculations done in terms of square size,
 * let's just keep this around.
 */
#define SQUARESIZE 1

typedef struct {
        /* Array of Squares */
        Square *squares;
        /* Actual board size. User can define them using -r and -f
         * options. */
        int ranks;
        int files;
} Board;

/* Limits for board size. */
#define BOARD_SIZE_MIN  4
#define BOARD_SIZE_MAX 98
#define BOARD_SIZE_DEF  8

/* Indexes of the "best" moves */
int best_dark;
int best_light;

/* Macros to convert between index and (rank, file) information. */
#define rank(board, index)          ((index) / ((board)->files))
#define file(board, index)          ((index) % ((board)->files))
#define index(board, rank, file)    (((board)->files) * (rank) + (file))

/* Macro to access board as if it were two dimensional. */
#define board(board, rank, file)    (&((board)->squares[ index((board), (rank), (file)) ]))

Board*   oth_board_init         (int *argc, char **argv);
void     oth_board_free         (Board* board);
void     oth_board_reset        (Board* board);

void     oth_board_flip_disks   (Board* board,
                                 int rank,
                                 int file);

#endif                          /* _OTHELLO_BOARD_H_ */
