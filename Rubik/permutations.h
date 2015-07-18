#ifndef __PERMUTATIONS_by_WOODMATH
#define __PERMUTATIONS_by_WOODMATH
#include <stdio.h>
#define PERMUTATION_COLS 54
#define SUB_MOVES 21

#define MOVE_FACE_UP		((unsigned char)(0b10000000))
#define MOVE_FACE_LEFT		((unsigned char)(0b01000000))
#define MOVE_FACE_FRONT		((unsigned char)(0b00100000))
#define MOVE_FACE_RIGHT		((unsigned char)(0b00010000))
#define MOVE_FACE_BACK		((unsigned char)(0b00001000))
#define MOVE_FACE_DOWN		((unsigned char)(0b00000100))
#define MOVE_DIR_CCW		((unsigned char)(0b00000010))
#define MOVE_DIR_CW		((unsigned char)(0b00000001))
#define MOVE_FACES		((unsigned char)(0b11111100))
#define MOVE_DIRS		((unsigned char)(0b00000011))

#define MOVE_STATE_NONE		((unsigned char)(0b00000000))
#define MOVE_STATE_FORWARD	((unsigned char)(0b00000001))
#define MOVE_STATE_BACKWARD	((unsigned char)(0b00000010))

#define MAX_NUMBER_MOVES	(100)

/*

                          +-----+
                          |     |
                          |  U  |
                          |     |
                    +-----+-----+-----+-----+
                    |     |     |     |     |
                    |  L  |  F  |  R  |  B  |
                    |     |     |     |     |
                    +-----+-----+-----+-----+
                          |     |
                          |  D  |
                          |     |
                          +-----+



                             +------+------+------+
                             |      |      |      |
                             |  00  |  01  |  02  |
                             |      |      |      |
                             +------+------+------+      
                             |      |      |      |
                             |  03  |  04  |  05  |
                             |      |      |      |
                             +------+------+------+      
                             |      |      |      |
                             |  06  |  07  |  08  |
                             |      |      |      |
        +------+------+------+------+------+------+------+------+------+------+------+------+
        |      |      |      |      |      |      |      |      |      |      |      |      |
        |  09  |  10  |  11  |  18  |  19  |  20  |  27  |  28  |  29  |  36  |  37  |  38  |
        |      |      |      |      |      |      |      |      |      |      |      |      |
        +------+------+------+------+------+------+------+------+------+------+------+------+      
        |      |      |      |      |      |      |      |      |      |      |      |      |
        |  12  |  13  |  14  |  21  |  22  |  23  |  30  |  31  |  32  |  39  |  40  |  41  |
        |      |      |      |      |      |      |      |      |      |      |      |      |
        +------+------+------+------+------+------+------+------+------+------+------+------+      
        |      |      |      |      |      |      |      |      |      |      |      |      |
        |  15  |  16  |  17  |  24  |  25  |  26  |  33  |  34  |  35  |  42  |  43  |  44  |
        |      |      |      |      |      |      |      |      |      |      |      |      |
        +------+------+------+------+------+------+------+------+------+------+------+------+      
                             |      |      |      |
                             |  45  |  46  |  47  |
                             |      |      |      |
                             +------+------+------+      
                             |      |      |      |
                             |  48  |  49  |  50  |
                             |      |      |      |
                             +------+------+------+      
                             |      |      |      |
                             |  51  |  52  |  53  |
                             |      |      |      |         
                             +------+------+------+
          
*/

//      Cubies are the physical pieces
//      Cubicles are physical spaces

//      Location refers to cubbicle space that the cubie occupies, regardless of orientation
//      Orientation refers to "rotation" for center pieces, "flip" for edge pieces, and "spin" for corner pieces
//      Position refers to the combination of location + orientation

//      Index represents cubicle location
//      Number in array represents the cubicle face
//	ex: rubik_set_use[0][x] = y means cubicle x has cubie y


//void cCopyBuffer(unsigned char[][PERMUTATION_COLS], unsigned char[][PERMUTATION_COLS], int, int){

void cCopyBuffer(unsigned char(*)[PERMUTATION_COLS], unsigned char(*)[PERMUTATION_COLS], int, int);
void cApplyMove(unsigned char(*)[PERMUTATION_COLS], unsigned char(*)[PERMUTATION_COLS], unsigned char(*)[PERMUTATION_COLS], unsigned char(*), int, int);
void applyPermutationString(unsigned char*);
void cApplySingleMove(unsigned char*);
void resetBuffers();
void generateRandomMoves(unsigned char);
void printArray(unsigned char(*)[PERMUTATION_COLS], int, int);

#endif
