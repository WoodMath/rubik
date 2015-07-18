#ifndef __BEZIER_by_WOODMATH
#define __BEZIER_by_WOODMATH
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#define GRAY_SCALE (0.125f)
#define GRAY_TESTt



float wmBezierCurveSum(float[4][2], float, int);
float wmBezierTriSum(float[4][4][3], float, float, int);
void wmBezier2f(float[4][2], unsigned int, unsigned int, unsigned int);
void wmBezierSweep2f(float[4][2], float, float, unsigned int, unsigned int, unsigned int);
void wmBezierTriangle3f(float[4][4][3], unsigned int, unsigned int, unsigned int);
void wmBezierFan2f(float[4][2], unsigned int, unsigned int, unsigned int);
void wmTexturedBezierFan2f(float[4][2], unsigned int, unsigned int, unsigned int);
void wmTexturedUnitSquare();
void wmUnitSquare();

#endif
