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
    b->size = size;
    b->array = (int*) malloc(size * size * sizeof(int));
    if(b->array == NULL)
    {
        printf("No memory to allocate\n");
        exit(0);
    }
    return b;
}

/*!
 * Function deallocating a board's memory whose address is as parameter.
 * \param b : board
 */ 
void destroyBoard(board* b)
{
    assert(b->array != NULL);
    assert(b != NULL);
    free(b->array);
    free(b);
}

void fillBoard(board* b)
{
    for(int i=0; i<b->size*b->size; i++)
    {
        b->array[i] = i;
    }
}

/*!
 * Function returning the value at position i j
 * \param b : board
 * \param i : row
 * \param j : column
 */
int getPiece(board* b, int i, int j)
{
    assert(i>=0 && i<b->size && j>=0 && j<b->size);
    return b->array[i*b->size+j];
}

/*!
 * Function modifying the value of piece at position i j
 * \param b : board
 * \param i : row
 * \param j : column
 * \param val : new value replacing the old one
 */ 
void setPiece(board* b, int i, int j, int val)
{
    assert(i>=0 && i<b->size && j>=0 && j<b->size && val>=-1 && val<=1);
    b->array[getPiece(b, i, j)] = val;
}

/*!
 * Function returning 1 if the index is valid
 * \param index : index of the board between [0,n-1]
 */ 
int validIndex(board* b, int index)
{
    if(index>=0 && index<=b->size-1)
    {
        return 1;
    }
    return 0;
}

/*!
 * Function returning 1 if the piece existing on the board
 * \param rowIndex : index of row
 * \param columnIndex : index of column
 */ 
int validPiece(board* b, int rowIndex, int columnIndex)
{
    if(validIndex(b, rowIndex), validIndex(b, columnIndex))
    {
        return 1;
    }
    return 0;
}

/*!
 * Function showing board
 * \param b : board
 */ 
void showV1(board* b)
{
    for(int i=0; i<b->size*b->size; i++)
    {
        printf("%d\t",b->array[i]);
        if((i+1)%b->size==0)
        {
            printf("\n");
        }
    }    
}

void showV2(board* b)
{
    // TODO
}

void showV3(board* b)
{
    // TODO
}

int main()
{
    board* b = createBoard(3);
    fillBoard(b);
    showV1(b);
    destroyBoard(b);

    return EXIT_SUCCESS;
}