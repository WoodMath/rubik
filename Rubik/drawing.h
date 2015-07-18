#ifndef __DRAWING_by_WOODMATH
#define __DRAWING_by_WOODMATH
#include <GLUT/glut.h>
#include "shapes.h"
#include "SOIL.h"

#define PARTIAL_SEGMENT_0 	((char)(0b00000001))
#define PARTIAL_SEGMENT_1 	((char)(0b00000010))
#define PARTIAL_SEGMENT_2 	((char)(0b00000100))

#define PARTIAL_DIMENSION_X 	((char)(0b00010000))
#define PARTIAL_DIMENSION_Y 	((char)(0b00100000))
#define PARTIAL_DIMENSION_Z 	((char)(0b01000000))



void loadTextureInfo();
void drawFullCube(float, float);
void drawPartialCube(float, float, char, char);
void drawNumberedFace(float, float, int);

#endif
