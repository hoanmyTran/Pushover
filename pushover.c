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
 * \param b : address of board
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

void showBoard(board* b)
{
    for(int i=0; i<b->size*b->size; i++)
    {
        printf("%d ",b->array[i]);
        if((i+1)%b->size==0)
        {
            printf("\n");
        }
    }    
}

// int getCase(board* b, int i, int j) {

// }

int main()
{
    board* b = createBoard(3);
    fillBoard(b);
    showBoard(b);
    destroyBoard(b);

    return EXIT_SUCCESS;
}