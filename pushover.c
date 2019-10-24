#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define BOARD_SIZE_MIN 3
#define BOARD_SIZE_MAX 8


typedef struct
{
    int* array;
    int size;
}board;

/*!
 * Function allocating dynamically a board whose address is returned.
 * \param size : size of board
 */ 
board* createBoard(int size)
{
    assert(size>=BOARD_SIZE_MIN && size<=BOARD_SIZE_MAX);
    board* b = (board*) malloc(sizeof(board));
    if(b == NULL)
    {
        printf("No memory to allocate\n");
        exit(0);
    }
    b->array = malloc(size * sizeof(int));
    return b;
}

/*!
 * Function deallocating a board's memory whose address is as parameter.
 * \param b : address of board
 */ 
void destroyBoard(board* b)
{
    assert(&b->size != NULL);
    assert(b != NULL);
    free(&b->size);
    free(b);
}

int main()
{
    board* b = createBoard(3);
    destroyBoard(b);

    return EXIT_SUCCESS;
}