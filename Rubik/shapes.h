#ifndef __SHAPES_by_WOODMATH
#define __SHAPES_by_WOODMATH
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include "bezier.h"
#define NUM_BEZIER_DIV (10)


void displayFaceCorners(float[4][2], float, float);
void displayAdjacentEdges(float[4][2], float, float);
void displayEmptyFace(float, float);
void drawCubie(float, float, int, int, int, char);
//void drawCubie(float, float, int, int, int, char);
void drawTexturedFace(float, float, GLint, int);

#endif
