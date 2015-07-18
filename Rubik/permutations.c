#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "permutations.h"
#define DEBUGd


unsigned char* cMoves = NULL;
unsigned char* cMarker = NULL;
int iMoveState = MOVE_STATE_NONE;	// 1 for forward, 2 for backward
int iTokenCount = 0;			// Count of parsed groupings of letters , "F", "UU", "RRR", "BBBB" and "H" each count as 1
int iArrayCount = 0;			// Count of valid moves "F" and "RRR" count as 1, "UU" count as two and "BBBB" and "H" count as 0

unsigned char cRubikStateBuffer[][PERMUTATION_COLS] = {
	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
};

unsigned char cRubikCopyBuffer[][PERMUTATION_COLS] = {
	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
};

/*******************************************************************************************************************************/

unsigned char cRubikMove_CW_Up[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  2,   5,   8,   1,   4,   7,   0,   3,   6,  36,  37,  38,  12,  13,  14,  15,  16,  17,   9,  10,  11,  21,  22,  23,  24,  25,  26,  18,  19,  20,  30,  31,  32,  33,  34,  35,  27,  28,  29,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53}, 
	{  1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, 
	{  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
};

/*
        #declare up_cw = array[3][54]{
            {  2,   5,   8,   1,   4,   7,   0,   3,   6,  36,  37,  38,  12,  13,  14,  15,  16,  17,   9,  10,  11,  21,  22,  23,  24,  25,  26,  18,  19,  20,  30,  31,  32,  33,  34,  35,  27,  28,  29,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53}, 
            {  1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, 
            {  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
        };
*/

unsigned char cRubikMove_CW_Left[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{ 18,   1,   2,  21,   4,   5,  24,   7,   8,  11,  14,  17,  10,  13,  16,   9,  12,  15,  45,  19,  20,  48,  22,  23,  51,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,   6,  39,  40,   3,  42,  43,   0,  44,  46,  47,  41,  49,  50,  38,  52,  53},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   2,   0,   0,   2,   2,   0,   0,   2,   0,   0,   2,   0,   0},
	{  1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0}
};

/*
        #declare left_cw = array[3][54]{
            { 18,   1,   2,  21,   4,   5,  24,   7,   8,  11,  14,  17,  10,  13,  16,   9,  12,  15,  45,  19,  20,  48,  22,  23,  51,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,   6,  39,  40,   3,  42,  43,   0,  44,  46,  47,  41,  49,  50,  38,  52,  53},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   2,   0,   0,   2,   2,   0,   0,   2,   0,   0,   2,   0,   0},
            {  1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0}
        };
*/

unsigned char cRubikMove_CW_Front[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  0,   1,   2,   3,   4,   5,  27,  30,  33,   9,  10,   8,  12,  13,   7,  15,  16,   6,  20,  23,  26,  19,  22,  25,  18,  21,  24,  47,  28,  29,  46,  31,  32,  45,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  11,  14,  17,  48,  49,  50,  51,  52,  53},
	{  0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0},
	{  0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0}
};

/*
        #declare front_cw = array[3][54]{
            {  0,   1,   2,   3,   4,   5,  27,  30,  33,   9,  10,   8,  12,  13,   7,  15,  16,   6,  20,  23,  26,  19,  22,  25,  18,  21,  24,  47,  28,  29,  46,  31,  32,  45,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  11,  14,  17,  48,  49,  50,  51,  52,  53},
            {  0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0},
            {  0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0}
        };
*/

unsigned char cRubikMove_CW_Right[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  0,   1,  42,   3,   4,  39,   6,   7,  36,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   2,  21,  22,   5,  24,  25,   8,  29,  32,  35,  28,  31,  34,  27,  30,  33,  53,  37,  38,  50,  40,  41,  47,  43,  44,  45,  46,  20,  48,  49,  23,  51,  52,  26},
	{  0,   0,   2,   0,   0,   2,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   0,   0,   2,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
	{  0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1}
};

/*
        #declare right_cw = array[3][54]{
            {  0,   1,  42,   3,   4,  39,   6,   7,  36,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   2,  21,  22,   5,  24,  25,   8,  29,  32,  35,  28,  31,  34,  27,  30,  33,  53,  37,  38,  50,  40,  41,  47,  43,  44,  45,  46,  20,  48,  49,  23,  51,  52,  26},
            {  0,   0,   2,   0,   0,   2,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   0,   0,   2,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {  0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1}
        };
*/

unsigned char cRubikMove_CW_Back[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{ 15,  12,   9,   3,   4,   5,   6,   7,   8,  51,  10,  11,  52,  13,  14,  53,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,   0,  30,  31,   1,  33,  34,   2,  38,  41,  44,  37,  40,  43,  36,  39,  42,  45,  46,  47,  48,  49,  50,  35,  32,  29},
	{  3,   3,   3,   0,   0,   0,   0,   0,   0,   3,   0,   0,   3,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   0,   0,   3,   0,   0,   3,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   3,   3,   3},
	{  1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1}
};

/*
        #declare back_cw = array[3][54]{
            { 15,  12,   9,   3,   4,   5,   6,   7,   8,  51,  10,  11,  52,  13,  14,  53,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,   0,  30,  31,   1,  33,  34,   2,  38,  41,  44,  37,  40,  43,  36,  39,  42,  45,  46,  47,  48,  49,  50,  35,  32,  29},
            {  3,   3,   3,   0,   0,   0,   0,   0,   0,   3,   0,   0,   3,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   0,   0,   3,   0,   0,   3,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   3,   3, 270},
            {  1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1}
        };
*/

unsigned char cRubikMove_CW_Down[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  24,  25,  26,  18,  19,  20,  21,  22,  23,  33,  34,  35,  27,  28,  29,  30,  31,  32,  42,  43,  44,  36,  37,  38,  39,  40,  41,  15,  16,  17,  47,  50,  53,  46,  49,  52,  45,  48,  51},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1}
};
/*
        #declare down_cw = array[3][54]{
            {  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  24,  25,  26,  18,  19,  20,  21,  22,  23,  33,  34,  35,  27,  28,  29,  30,  31,  32,  42,  43,  44,  36,  37,  38,  39,  40,  41,  15,  16,  17,  47,  50,  53,  46,  49,  52,  45,  48,  51},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,  90},
            {  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1}
        };

*/

unsigned char cRubikMove_CCW_Up[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  6,   3,   0,   7,   4,   1,   8,   5,   2,  18,  19,  20,  12,  13,  14,  15,  16,  17,  27,  28,  29,  21,  22,  23,  24,  25,  26,  36,  37,  38,  30,  31,  32,  33,  34,  35,   9,  10,  11,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  3,   3,   3,   3,   3,   3,   3,   3,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
	{  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
};

unsigned char cRubikMove_CCW_Left[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{ 44,   1,   2,  41,   4,   5,  38,   7,   8,  15,  12,   9,  16,  13,  10,  17,  14,  11,   0,  19,  20,   3,  22,  23,   6,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  51,  39,  40,  48,  42,  43,  45,  18,  46,  47,  21,  49,  50,  24,  52,  53},
	{  2,   0,   0,   2,   0,   0,   2,   0,   0,   3,   3,   3,   3,   3,   3,   3,   3,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   2,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0},
	{  1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0}
};

unsigned char cRubikMove_CCW_Front[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  0,   1,   2,   3,   4,   5,  17,  14,  11,   9,  10,  45,  12,  13,  46,  15,  16,  47,  24,  21,  18,  25,  22,  19,  26,  23,  20,   6,  28,  29,   7,  31,  32,   8,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  33,  30,  27,  48,  49,  50,  51,  52,  53},
	{  0,   0,   0,   0,   0,   0,   3,   3,   3,   0,   0,   3,   0,   0,   3,   0,   0,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,   0,   0,   3,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   3,   3,   0,   0,   0,   0,   0,   0},
	{  0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0}
};

unsigned char cRubikMove_CCW_Right[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  0,   1,  20,   3,   4,  23,   6,   7,  26,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  47,  21,  22,  50,  24,  25,  53,  33,  30,  27,  34,  31,  28,  35,  32,  29,   8,  37,  38,   5,  40,  41,   2,  43,  44,  45,  46,  42,  48,  49,  39,  51,  52,  36},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   3,   3,   3,   3,   3,   3,   3,   3,   2,   0,   0,   2,   0,   0,   2,   0,   0,   0,   0,   2,   0,   0,   2,   0,   0,   2},
	{  0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1}
};

unsigned char cRubikMove_CCW_Back[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{ 29,  32,  35,   3,   4,   5,   6,   7,   8,   2,  10,  11,   1,  13,  14,   0,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  53,  30,  31,  52,  33,  34,  51,  42,  39,  36,  43,  40,  37,  44,  41,  38,  45,  46,  47,  48,  49,  50,   9,  12,  15},
	{  1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   3,   3,   3,   3,   3,   3,   3,   3,   3,   0,   0,   0,   0,   0,   0,   1,   1,   1},
	{  1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   1,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1}
};

unsigned char cRubikMove_CCW_Down[][PERMUTATION_COLS] = {
//	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53},
	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  42,  43,  44,  18,  19,  20,  21,  22,  23,  15,  16,  17,  27,  28,  29,  30,  31,  32,  24,  25,  26,  36,  37,  38,  39,  40,  41,  33,  34,  35,  51,  48,  45,  52,  49,  46,  53,  50,  47},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   3,   3,   3,   3,   3,   3,   3,   3},
	{  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1}
};

/*******************************************************************************************************************************/

unsigned char cRubikMove_Faces_Up[] = 
	{  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  18,  19,  20,  27,  28,  29,  36,  37,  38};

unsigned char cRubikMove_Faces_Left[] = 
	{  0,   3,   6,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  21,  24,  38,  41,  44,  45,  48,  51};

unsigned char cRubikMove_Faces_Front[] =
	{  6,   7,   8,  11,  14,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  30,  33,  45,  46,  47};

unsigned char cRubikMove_Faces_Right[] =
	{  2,   5,   8,  20,  23,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  39,  42,  47,  50,  53};

unsigned char cRubikMove_Faces_Back[] =
	{  0,   1,   2,   9,  12,  15,  29,  32,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  51,  52,  53};

unsigned char cRubikMove_Faces_Down[] =
	{ 15,  16,  17,  24,  25,  26,  33,  34,  35,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53};

void cCopyBuffer(unsigned char (*cBufferSource)[PERMUTATION_COLS], unsigned char (*cBufferDestination)[PERMUTATION_COLS], int iSizeRows, int iSizeCols){

	int iIncRow, iIncCol;
	for(iIncRow = 0; iIncRow < iSizeRows; iIncRow++)
		for(iIncCol = 0; iIncCol < iSizeCols; iIncCol++)
			cBufferDestination[iIncRow][iIncCol] = cBufferSource[iIncRow][iIncCol];
	return; 
};

void cApplyMove(unsigned char (*cStateBuffer)[PERMUTATION_COLS], unsigned char (*cCopyBuffer)[PERMUTATION_COLS], unsigned char (*cMoveBuffer)[PERMUTATION_COLS], unsigned char (*cSub), int iSizeRows, int iSizeCols){
/*
	int iIncCol;
	for(iIncCol = 0; iIncCol < iSizeCols; iIncCol++)
		if(cMoveBuffer[2][iIncCol] == 1){
			int iNewBufferDest = cMoveBuffer[0][iIncCol];

#ifdef DEBUG
			printf(" %2d -> %2d\n", iIncCol, iNewBufferDest);
#endif
			cCopyBuffer[0][iNewBufferDest] = cStateBuffer[0][iIncCol];
			cCopyBuffer[1][iNewBufferDest] = cStateBuffer[1][iIncCol] + cMoveBuffer[1][iIncCol];
			cCopyBuffer[1][iNewBufferDest] = cCopyBuffer[1][iNewBufferDest] % 4;
			if(cMoveBuffer[2][iNewBufferDest] == 0)
				printf(" Warning: Moving to Cubie face that is not indicated for a move (iIncCol = %d) -> (iNewBufferDest = %d).\n", iIncCol, iNewBufferDest);
		}


	for(iIncCol = 0; iIncCol < iSizeCols; iIncCol++)
		if(cMoveBuffer[2][iIncCol] == 1){
			cStateBuffer[0][iIncCol] = cCopyBuffer[0][iIncCol];
			cStateBuffer[1][iIncCol] = cCopyBuffer[1][iIncCol];
		}
*/
///*

	int iIncSub;
	for(iIncSub = 0; iIncSub < SUB_MOVES; iIncSub++){
		int iIncCol = cSub[iIncSub];
		int iNewBufferDest = cMoveBuffer[0][iIncCol];

#ifdef DEBUG
		printf(" %2d -> %2d\n", iIncCol, iNewBufferDest);
#endif
		cCopyBuffer[0][iNewBufferDest] = cStateBuffer[0][iIncCol];
		cCopyBuffer[1][iNewBufferDest] = cStateBuffer[1][iIncCol] + cMoveBuffer[1][iIncCol];
		cCopyBuffer[1][iNewBufferDest] = cCopyBuffer[1][iNewBufferDest] % 4;
		if(cMoveBuffer[2][iNewBufferDest] == 0)
			printf(" Warning: Moving to Cubie face that is not indicated for a move (iIncCol = %d) -> (iNewBufferDest = %d).\n", iIncCol, iNewBufferDest);

	}

	for(iIncSub = 0; iIncSub < SUB_MOVES; iIncSub++){
		int iIncCol = cSub[iIncSub];
		cStateBuffer[0][iIncCol] = cCopyBuffer[0][iIncCol];
		cStateBuffer[1][iIncCol] = cCopyBuffer[1][iIncCol];
	}
//*/
	return;
};

void applyPermutationString(unsigned char* cMoveString){

//	srand(time(NULL));

#ifdef DEBUG
	printf(" cMoveString = %s ;\n", cMoveString);
#endif

	int iInc, iLen; 
	iLen = strlen(cMoveString);

	int iTokenStart = 0, iTokenStop = 0;
	unsigned char *cTokenStart = NULL, *cTokenStop = NULL;

	int* iMoves;

	while(iTokenStart < iLen){
		iTokenStop = iTokenStart;
		cTokenStart = cMoveString + iTokenStart;
		cTokenStop = cMoveString + iTokenStop;

#ifdef DEBUG
		printf(" iTokenStart = %d ;\n", iTokenStart);
#endif

		while(((*cTokenStart) == (*cTokenStop)) && (iTokenStop < iLen)){
			cTokenStop = cMoveString + iTokenStop;

#ifdef DEBUG
			printf("%c", (int)(cMoveString[iTokenStop]));
#endif
			iTokenStop++;
			cTokenStop = cMoveString + iTokenStop;

		}
#ifdef DEBUG
		printf("\n");
#endif

		iTokenStop--;
		cTokenStop = cMoveString + iTokenStop;

		iTokenCount++;

		int iMoveCount;
		iMoveCount = (iTokenStop - iTokenStart + 1) % 4;
		if(iMoveCount == 1 || iMoveCount == 3)
			iArrayCount += 1;
		else if(iMoveCount == 2)
			iArrayCount += 2;
		else
			iArrayCount += 0;

#ifdef DEBUG
		printf(" iTokenCount = %d;\n", iTokenCount);
#endif

		iTokenStart = iTokenStop + 1;

	};

	iMoves = (int*) malloc(iTokenCount*sizeof(int));

	int iToken = 0;

	iMoves[iToken] = 0;
	for(iInc = 0; iInc < iLen; iInc++){
		if(cMoveString[iMoves[iToken]] != cMoveString[iInc]){
			iToken++;
#ifdef DEBUG
			printf(" new Token \n");
#endif
			iMoves[iToken] = iInc;
#ifdef DEBUG
			printf(" iMoves[iInc] = %d \n", iMoves[iToken]);
#endif
		};
#ifdef DEBUG
		printf(" cMoveString[%d] = %c ; iMoves[%d] = %d ;\n", 
			iInc, (int)cMoveString[iInc], iToken, iMoves[iToken]);
#endif
	};
/*
	unsigned char *cPrevStart = NULL, *cPrevStop = NULL;
	unsigned char *cCurrStart = NULL, *cCurrStop = NULL;
	unsigned char *cNextStart = NULL, *cNextStop = NULL;
*/
	cMoves = malloc(iArrayCount*sizeof(unsigned char));

	memset(cMoves, 0, iArrayCount);
	
	int iArrayIndex = 0;
	unsigned char iDir = 0;

	for(iInc = 0; iInc < iTokenCount; iInc++){
		int iMoveCount;
		if(iInc == (iTokenCount - 1))
			iMoveCount = iLen - iMoves[iInc];
		else
			iMoveCount = iMoves[iInc+1] - iMoves[iInc];

		iMoveCount = iMoveCount % 4;
#ifdef DEBUG
		printf(" iInc = %d ; c = %c; iMoveCount = %d; \n", iInc, (int)cMoveString[iMoves[iInc]], iMoveCount);
#endif

		if(iMoveCount > 0){
			unsigned char cApply = 0;

			// if two move choose random direction
			if(iMoveCount == 2){

				int iRand = rand();
#ifdef DEBUG
				printf(" iRand = %d; \n", iRand);
#endif
				iDir = iRand % 2;
				if(iDir)
					cApply |= MOVE_DIR_CW;
				else
					cApply |= MOVE_DIR_CCW;
			}
			if(iMoveCount == 1)
				cApply |= MOVE_DIR_CW;
			if(iMoveCount == 3)
				cApply |= MOVE_DIR_CCW;
								

			switch(cMoveString[iMoves[iInc]]){
				case 'U': cApply |= MOVE_FACE_UP; break;
				case 'L': cApply |= MOVE_FACE_LEFT; break;
				case 'F': cApply |= MOVE_FACE_FRONT; break;
				case 'R': cApply |= MOVE_FACE_RIGHT; break;
				case 'B': cApply |= MOVE_FACE_BACK; break;
				case 'D': cApply |= MOVE_FACE_DOWN; break;
				default:;
			}
			// only apply if valid letter
			if(cApply & (MOVE_FACE_UP | MOVE_FACE_LEFT | MOVE_FACE_FRONT | MOVE_FACE_RIGHT | MOVE_FACE_BACK | MOVE_FACE_DOWN)){
				cMoves[iArrayIndex] = cApply;
				cMarker = &(cMoves[iArrayIndex]);
				iArrayIndex++;
				cApplySingleMove(&cApply);
				if(iMoveCount == 2){
					cMoves[iArrayIndex] = cApply;
					cMarker = &(cMoves[iArrayIndex]);
					iArrayIndex++;
					cApplySingleMove(&cApply);
				}
			}
		}
	}

	free(iMoves);

	if(iArrayIndex == 0)	// no valid moves found
		return;
	else
		iArrayCount = iArrayIndex;

	iMoveState = MOVE_STATE_BACKWARD;		// will now rewind
#ifdef DEBUG
	for(iInc = 0; iInc < iArrayCount; iInc++){

		printf(" cMoves[%*d] = %d ", 2, iInc, (cMoves[iInc])&3); 
		if(cMoves[iInc] & MOVE_FACE_UP)
			printf("%*s", -15, " MOVE_FACE_UP ");
		if(cMoves[iInc] & MOVE_FACE_LEFT)
			printf("%*s", -15, " MOVE_FACE_LEFT ");
		if(cMoves[iInc] & MOVE_FACE_FRONT)
			printf("%*s", -15, " MOVE_FACE_FRONT ");
		if(cMoves[iInc] & MOVE_FACE_RIGHT)
			printf("%*s", -15, " MOVE_FACE_RIGHT ");
		if(cMoves[iInc] & MOVE_FACE_BACK)
			printf("%*s", -15, " MOVE_FACE_BACK ");
		if(cMoves[iInc] & MOVE_FACE_DOWN)
			printf("%*s", -15, " MOVE_FACE_DOWN ");

		if(cMoves[iInc] & MOVE_DIR_CW)
			printf("%*s", -20, " MOVE_DIR_CW \n");
		if(cMoves[iInc] & MOVE_DIR_CCW)
			printf("%*s", -20, " MOVE_DIR_CCW \n");

	}

	printf(" sizeof(cMoves) = %d \n", sizeof(cMoves));
#endif

}

void cApplySingleMove(unsigned char* cMoveChar){

	unsigned char (*cState)[PERMUTATION_COLS] = cRubikStateBuffer;
	unsigned char (*cCopy)[PERMUTATION_COLS] = cRubikCopyBuffer;
	unsigned char (*cMove)[PERMUTATION_COLS];
	unsigned char (*cSub);


	if( (*cMoveChar) & MOVE_FACE_UP){
		cMove = cRubikMove_CW_Up;
		cSub = cRubikMove_Faces_Up;
	}
	if( (*cMoveChar) & MOVE_FACE_LEFT){
		cMove = cRubikMove_CW_Left;
		cSub = cRubikMove_Faces_Left;
	}
	if( (*cMoveChar) & MOVE_FACE_FRONT){
		cMove = cRubikMove_CW_Front;
		cSub = cRubikMove_Faces_Front;
	}
	if( (*cMoveChar) & MOVE_FACE_RIGHT){
		cMove = cRubikMove_CW_Right;
		cSub = cRubikMove_Faces_Right;
	}
	if( (*cMoveChar) & MOVE_FACE_BACK){
		cMove = cRubikMove_CW_Back;
		cSub = cRubikMove_Faces_Back;
	}
	if( (*cMoveChar) & MOVE_FACE_DOWN){
		cMove = cRubikMove_CW_Down;
		cSub = cRubikMove_Faces_Down;
	}
	if( (*cMoveChar) & MOVE_DIR_CW)
		cApplyMove(cState, cCopy, cMove, cSub, 2, PERMUTATION_COLS);

	if( (*cMoveChar) & MOVE_DIR_CCW){
		cApplyMove(cState, cCopy, cMove, cSub, 2, PERMUTATION_COLS);
		cApplyMove(cState, cCopy, cMove, cSub, 2, PERMUTATION_COLS);
		cApplyMove(cState, cCopy, cMove, cSub, 2, PERMUTATION_COLS);
	}

#ifdef DEBUG
	printArray(cState, 2, PERMUTATION_COLS);
#endif

};

void resetBuffers(){

	int iInc;
	for(iInc = 0; iInc < PERMUTATION_COLS; iInc++){
		cRubikStateBuffer[0][iInc] = (unsigned char)iInc;
		cRubikStateBuffer[1][iInc] = (unsigned char)0;
		cRubikCopyBuffer[0][iInc] = (unsigned char)iInc;
		cRubikCopyBuffer[1][iInc] = (unsigned char)0;

	}
}

void generateRandomMoves(unsigned char bApplyPermutation){

//	srand(time(NULL));

	iArrayCount = (rand() % (MAX_NUMBER_MOVES - 1)) + 1;
	unsigned int iMoveFace, iMoveDir;
	unsigned int iPrevFace, iPrevDir;
	
	int iInc;


	if(cMoves != NULL)
		free(cMoves);

	cMoves = malloc(iArrayCount*sizeof(unsigned char));
	memset(cMoves, 0, iArrayCount);

	unsigned char cApply, cPrev;
	unsigned int iPrevFaceShift, iPrevDirShift;
	for(iInc = 0; iInc < iArrayCount; iInc++){
		iMoveFace = rand() % 6;
		iMoveDir = rand() % 2;

		if(iInc > 0){
			cPrev = cMoves[iInc - 1];

			iPrevFace = (cPrev & MOVE_FACES) >> 2;
			for(iPrevFaceShift = 0; (iPrevFace >> iPrevFaceShift) > 1; iPrevFaceShift++);
			iPrevFace = iPrevFaceShift;

			iPrevDir = cPrev & MOVE_DIRS;
			for(iPrevDirShift = 0; (iPrevDir >> iPrevDirShift) > 1; iPrevDirShift++);
			iPrevDir = iPrevDirShift;

#ifdef DEBUG
			printf(" iPrevFace = %d; iPrevDir = %d;", iPrevFace, iPrevDir);
#endif

			if(iMoveFace == iPrevFace)
				iMoveDir = iPrevDir;
		}

		cApply = (((1 << iMoveFace) << 2) | (1 << iMoveDir));
		cMoves[iInc] = cApply;

#ifdef DEBUG
		printf(" iMoveFace = %d; iMoveDir = %d; ", iMoveFace, iMoveDir);
		printf(" cApply & 252 = %d, \n", cApply & 252);
#endif
		cMarker = &(cMoves[iInc]);

		if(bApplyPermutation)
			cApplySingleMove(cMarker);

	}

	iMoveState = MOVE_STATE_BACKWARD;		// will now rewind

};

#ifdef DEBUG
void printArray(unsigned char (*cArray)[PERMUTATION_COLS], int iRows, int iCols){

	int iIncRow, iIncCol;

	for(iIncCol = 0; iIncCol < iCols; iIncCol++){
		printf(" %0*d", 2, iIncCol);		
	}
	printf("\n");
	
	for(iIncRow = 0; iIncRow < iRows; iIncRow++){
		for(iIncCol = 0; iIncCol < iCols; iIncCol++){
			printf(" %*d", 2, (int)cArray[iIncRow][iIncCol]);		
			
		}
		printf("\n");
	} 

/*
	printf("\n{");
	for(iIncCol = 0; iIncCol < iCols; iIncCol++){
		printf("%*d,", 4, (int)cArray[0][iIncCol]);
	}
	printf("},\n{");
	for(iIncCol = 0; iIncCol < iCols; iIncCol++){
		int iIncPrint = (int)cArray[1][iIncCol];
		printf("%*d,", 4, (iIncPrint == 3) ? 1 : ((iIncPrint == 1) ? 3 : iIncPrint) );
	}
	printf("}\n");
*/
};
#endif
