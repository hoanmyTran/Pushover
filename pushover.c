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
 * Function showing board
 * \param b : board
 */ 
void show(board* b)
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

int main()
{
    board* b = createBoard(3);
    fillBoard(b);
    showBoard(b);
    // printf("%d\n",getPiece(b,0,2));
    setPiece(b, 2, 0, -2);
    printf("\n");
    showBoard(b);
    destroyBoard(b);

    return EXIT_SUCCESS;
}