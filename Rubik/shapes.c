#include "shapes.h"
#define DEBUGd
#define DISPLAY_EDGES
#define DISPLAY_CORNERS
#define DISPLAY_FACE_CORNERS
#define DISPLAY_CENTER

float  glOuterPathSweep2f[4][2] = {{0.00,1.00},
			{0.50,1.00},
			{1.00,0.50},
			{1.00,0.00}};


float  glInnerPathSweep2f[4][2] = {{0.00,1.00},
			{0.00,0.50},
			{0.50,0.00},
			{1.00,0.00}};



//	uses following format
//
//	a^0*b^0*c^3	a^1*b^0*c^2	a^2*b^0*c^1	a^3*b^0*c^0
//	a^0*b^1*c^2	a^1*b^1*c^1	a^2*b^1*c^0	a^0*b^0*c^0
//	a^0*b^2*c^1	a^1*b^2*c^0	a^0*b^0*c^0	a^0*b^0*c^0
//	a^0*b^3*c^0	a^0*b^0*c^0	a^0*b^0*c^0	a^0*b^0*c^0
//
//	where a+b+c = 1



// first 2 array subscripts represent i and j, third array scupscript are for the vector component
float  glOuterPathTri3f[4][4][3] = {	//		0		1		2		3
				{{0.00,0.00,1.00},{0.50,0.00,1.00},{1.00,0.00,0.50},{1.00,0.00,0.00}},		// 0
				{{0.00,0.50,1.00},{0.70,0.70,0.70},{1.00,0.50,0.00},{0.00,0.00,0.00}},		// 1
				{{0.00,1.00,0.50},{0.50,1.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}},		// 2
				{{0.00,1.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}}		// 3
			};

/*
float  glInnerPathTri3f[4][4][3] = {	//		0		1		2		3
				{{0.00,0.00,1.00},{0.00,0.00,0.50},{0.50,0.00,0.00},{1.00,0.00,0.00}},		// 0
				{{0.00,0.00,0.50},{0.10,0.10,0.10},{0.50,0.00,0.00},{0.00,0.00,0.00}},		// 1
				{{0.00,0.50,0.00},{0.00,0.50,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}},		// 2
				{{0.00,1.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}}		// 3
			};
*/

float  glInnerPathTri3f[4][4][3] = {	//		0		1		2		3
				{{1.00,0.00,1.00},{1.00,0.00,0.50},{1.00,0.50,0.00},{1.00,1.00,0.00}},		// 0
				{{0.50,0.00,1.00},{0.70,0.70,0.70},{0.50,1.00,0.00},{0.00,0.00,0.00}},		// 1
				{{0.00,0.50,1.00},{0.00,1.00,0.50},{0.00,0.00,0.00},{0.00,0.00,0.00}},		// 2
				{{0.00,1.00,1.00},{0.00,0.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}}		// 3
			};

void displayFaceCorners(float bzInnerPathSweep2f[4][2], float fBoxSize, float fCornerRadius){

	float fFarCorner = fBoxSize - fCornerRadius;
	float fEdgeLength = fBoxSize - 2.0f*fCornerRadius;

	// (0,0) corner
	glPushMatrix();
	glTranslatef(fCornerRadius,fCornerRadius,0.0f);
	glScalef(1.0f,1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,1.0f);
	wmBezierFan2f(bzInnerPathSweep2f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (0,1) corner
	glPushMatrix();
	glTranslatef(fCornerRadius,fFarCorner,0.0f);
	glScalef(1.0f,-1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,1.0f);
	wmBezierFan2f(bzInnerPathSweep2f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (1,0) corner
	glPushMatrix();
	glTranslatef(fFarCorner,fCornerRadius,0.0f);
	glScalef(-1.0f,1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,1.0f);
	wmBezierFan2f(bzInnerPathSweep2f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (1,1) corner
	glPushMatrix();
	glTranslatef(fFarCorner,fFarCorner,0.0f);
	glScalef(-1.0f,-1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,1.0f);
	wmBezierFan2f(bzInnerPathSweep2f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

}

void displayAdjacentEdges(float bzOuterPathSweep2f[4][2], float fBoxSize, float fCornerRadius){

	float fFarCorner = fBoxSize - fCornerRadius;
	float fEdgeLength = fBoxSize - 2.0f*fCornerRadius;

	// (0,0,0),(0,0,1) edge
	glPushMatrix();
	glTranslatef(fCornerRadius,fCornerRadius,fCornerRadius);
	glScalef(-1.0f,-1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,fEdgeLength);
	wmBezierSweep2f(bzOuterPathSweep2f, 0.0f, 1.0f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (0,0,0),(0,1,0) edge
	glPushMatrix();
	glRotatef(-90.0f,0.0f,1.0f,0.0f);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	glTranslatef(fCornerRadius,fCornerRadius,fCornerRadius);
	glScalef(-1.0f,-1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,fEdgeLength);
	wmBezierSweep2f(bzOuterPathSweep2f, 0.0f, 1.0f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (0,0,0),(1,0,0) edge
	glPushMatrix();
	glRotatef(90.0f,0.0f,0.0f,1.0f);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glTranslatef(fCornerRadius,fCornerRadius,fCornerRadius);
	glScalef(-1.0f,-1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,fEdgeLength);
	wmBezierSweep2f(bzOuterPathSweep2f, 0.0f, 1.0f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

}

void displayEmptyFace(float fBoxSize, float fCornerRadius){

	float fFarCorner = fBoxSize - fCornerRadius;
	float fEdgeLength = fBoxSize - 2.0f*fCornerRadius;

	glPushMatrix();
	glTranslatef(fCornerRadius, fCornerRadius, 0.0);
	glScalef(fEdgeLength, fEdgeLength, 1.0);
	wmUnitSquare();
	glPopMatrix();


}

void drawCubie(float fBoxSize, float fCornerRadius, int iXShift, int iYShift, int iZShift, char bDrawBlankFaces){
//void drawCubie(float fBoxSize, float fCornerRadius, int iXShift, int iYShift, int iZShift, char bDrawBlankFaces){


/*
float  bzOuterPathSweep2f[][2] = {{0.00,1.00},
			{0.50,1.00},
			{1.00,0.50},
			{1.00,0.00}};


float  bzInnerPathSweep2f[][2] = {{0.00,1.00},
			{0.00,0.50},
			{0.50,0.00},
			{1.00,0.00}};

*/

//	uses following format
//
//	a^0*b^0*c^3	a^1*b^0*c^2	a^2*b^0*c^1	a^3*b^0*c^0
//	a^0*b^1*c^2	a^1*b^1*c^1	a^2*b^1*c^0	a^0*b^0*c^0
//	a^0*b^2*c^1	a^1*b^2*c^0	a^0*b^0*c^0	a^0*b^0*c^0
//	a^0*b^3*c^0	a^0*b^0*c^0	a^0*b^0*c^0	a^0*b^0*c^0
//
//	where a+b+c = 1


/*
// first 2 array subscripts represent i and j, third array scupscript are for the vector component
float  bzOuterPathTri3f[4][4][3] = {	//		0		1		2		3
				{{0.00,0.00,1.00},{0.50,0.00,1.00},{1.00,0.00,0.50},{1.00,0.00,0.00}},		// 0
				{{0.00,0.50,1.00},{0.70,0.70,0.70},{1.00,0.50,0.00},{0.00,0.00,0.00}},		// 1
				{{0.00,1.00,0.50},{0.50,1.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}},		// 2
				{{0.00,1.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}}		// 3
			};
*/
/*
float  bzInnerPathTri3f[4][4][3] = {	//		0		1		2		3
				{{0.00,0.00,1.00},{0.00,0.00,0.50},{0.50,0.00,0.00},{1.00,0.00,0.00}},		// 0
				{{0.00,0.00,0.50},{0.10,0.10,0.10},{0.50,0.00,0.00},{0.00,0.00,0.00}},		// 1
				{{0.00,0.50,0.00},{0.00,0.50,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}},		// 2
				{{0.00,1.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}}		// 3
			};
*/
/*
float  bzInnerPathTri3f[4][4][3] = {	//		0		1		2		3
				{{1.00,0.00,1.00},{1.00,0.00,0.50},{1.00,0.50,0.00},{1.00,1.00,0.00}},		// 0
				{{0.50,0.00,1.00},{0.70,0.70,0.70},{0.50,1.00,0.00},{0.00,0.00,0.00}},		// 1
				{{0.00,0.50,1.00},{0.00,1.00,0.50},{0.00,0.00,0.00},{0.00,0.00,0.00}},		// 2
				{{0.00,1.00,1.00},{0.00,0.00,0.00},{0.00,0.00,0.00},{0.00,0.00,0.00}}		// 3
			};
*/
/*
	float kkOuterPathSweep2f[4][2] = glOuterPathSweep2f;
	float kkInnerPathSweep2f[4][2] = glInnerPathSweep2f;
	float kkOuterPathTri3f[4][4][3] = glOuterPathTri3f;
	float kkInnerPathTri3f[4][4][3] = glInnerPathTri3f; 
*/
///*
	float (*kkOuterPathSweep2f)[2];
	float (*kkInnerPathSweep2f)[2];
	float (*kkOuterPathTri3f)[4][3];
	float (*kkInnerPathTri3f)[4][3]; 
//*/

/*
	float kkOuterPathSweep2f[4][2];
	float kkInnerPathSweep2f[4][2];
	float kkOuterPathTri3f[4][4][3];
	float kkInnerPathTri3f[4][4][3]; 

	float* kkOuterPathSweep2f[2];
	float* kkInnerPathSweep2f[2];
	float* kkOuterPathTri3f[4][3];
	float* kkInnerPathTri3f[4][3];

	float* (kkOuterPathSweep2f[2]);
	float* (kkInnerPathSweep2f[2]);
	float* (kkOuterPathTri3f[4][3]);
	float* (kkInnerPathTri3f[4][3]); 
*/
	kkOuterPathSweep2f = glOuterPathSweep2f;
	kkInnerPathSweep2f = glInnerPathSweep2f;
	kkOuterPathTri3f = glOuterPathTri3f;
	kkInnerPathTri3f = glInnerPathTri3f; 

	if(iXShift == 1 && iYShift == 1 && iZShift == 1)	// Center Cube
		return;

	float fFarCorner = fBoxSize - fCornerRadius;
	float fEdgeLength = fBoxSize - 2.0f*fCornerRadius;
/*
	int iXShift = iCubie % 3;
	int iYShift = (iCubie / 3) % 3;
	int iZShift = iCubie / 9;
*/
#ifdef DISPLAY_CORNERS

	// (0,0,0)
	glPushMatrix();
	glTranslatef(fCornerRadius,fCornerRadius,fCornerRadius);
	glScalef(-1.0f,-1.0f,-1.0f);
	glScalef(fCornerRadius,fCornerRadius,fCornerRadius);
//	glScalef(5.0f,5.0f,5.0f);
	wmBezierTriangle3f(glOuterPathTri3f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (0,0,1)displayFaceCorners(float bzInnerPathSweep2f[4][2], float fBoxSize, float fCornerRadius)
	glPushMatrix();
	glTranslatef(fCornerRadius,fCornerRadius,fFarCorner);
	glScalef(-1.0f,-1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,fCornerRadius);
	wmBezierTriangle3f(glOuterPathTri3f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (0,1,0)
	glPushMatrix();
	glTranslatef(fCornerRadius,fFarCorner,fCornerRadius);
	glScalef(-1.0f,1.0f,-1.0f);
	glScalef(fCornerRadius,fCornerRadius,fCornerRadius);
	wmBezierTriangle3f(glOuterPathTri3f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (0,1,1)
	glPushMatrix();
	glTranslatef(fCornerRadius,fFarCorner,fFarCorner);
	glScalef(-1.0f,1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,fCornerRadius);
	wmBezierTriangle3f(glOuterPathTri3f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (1,0,0)
	glPushMatrix();
	glTranslatef(fFarCorner,fCornerRadius,fCornerRadius);
	glScalef(1.0f,-1.0f,-1.0f);
	glScalef(fCornerRadius,fCornerRadius,fCornerRadius);
	wmBezierTriangle3f(glOuterPathTri3f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (1,0,1)
	glPushMatrix();
	glTranslatef(fFarCorner,fCornerRadius,fFarCorner);
	glScalef(1.0f,-1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,fCornerRadius);
	wmBezierTriangle3f(glOuterPathTri3f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (1,1,0)
	glPushMatrix();
	glTranslatef(fFarCorner,fFarCorner,fCornerRadius);
	glScalef(1.0f,1.0f,-1.0f);
	glScalef(fCornerRadius,fCornerRadius,fCornerRadius);
	wmBezierTriangle3f(glOuterPathTri3f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	// (1,1,1)
	glPushMatrix();
	glTranslatef(fFarCorner,fFarCorner,fFarCorner);
	glScalef(1.0f,1.0f,1.0f);
	glScalef(fCornerRadius,fCornerRadius,fCornerRadius);
	wmBezierTriangle3f(glOuterPathTri3f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

#endif


#ifdef DISPLAY_EDGES


	displayAdjacentEdges(glOuterPathSweep2f, fBoxSize, fCornerRadius);

	glPushMatrix();
	glTranslatef(fBoxSize, fBoxSize, 0.0f);
	glScalef(-1.0f,-1.0f,1.0f);
	displayAdjacentEdges(glOuterPathSweep2f, fBoxSize, fCornerRadius);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, fBoxSize, fBoxSize);
	glScalef(1.0f,-1.0f,-1.0f);
	displayAdjacentEdges(glOuterPathSweep2f, fBoxSize, fCornerRadius);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(fBoxSize, 0.0f, fBoxSize);
	glScalef(-1.0f,1.0f,-1.0f);
	displayAdjacentEdges(glOuterPathSweep2f, fBoxSize, fCornerRadius);
	glPopMatrix();

#endif

#ifdef DISPLAY_FACE_CORNERS

	// (x,y) z=0
	if(iZShift == 0)
		displayFaceCorners(glInnerPathSweep2f, fBoxSize, fCornerRadius);
	else if(bDrawBlankFaces)
		displayEmptyFace(fBoxSize, fCornerRadius);

	// (x,z) y=0
	glPushMatrix();
	glTranslatef(0.0f,0.0f,fBoxSize);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	if(iYShift == 0)
		displayFaceCorners(glInnerPathSweep2f, fBoxSize, fCornerRadius);
	else if(bDrawBlankFaces)
		displayEmptyFace(fBoxSize, fCornerRadius);
	glPopMatrix();

	// (y,z) x=0
	glPushMatrix();
	glTranslatef(0.0f,0.0f,fBoxSize);
	glRotatef(90.0f,0.0f,1.0f,0.0f);
	if(iXShift == 0)
		displayFaceCorners(glInnerPathSweep2f, fBoxSize, fCornerRadius);
	else if(bDrawBlankFaces)
		displayEmptyFace(fBoxSize, fCornerRadius);
	glPopMatrix();

	// (x,y) z=1
	glPushMatrix();
	glTranslatef(0.0f,0.0f,fBoxSize);
	glScalef(1.0f,1.0f,-1.0f);
	if(iZShift == 2)
		displayFaceCorners(glInnerPathSweep2f, fBoxSize, fCornerRadius);
	else if(bDrawBlankFaces)
		displayEmptyFace(fBoxSize, fCornerRadius);
	glPopMatrix();


	// (x,z) y=1
	glPushMatrix();
	glTranslatef(0.0f,fBoxSize,0.0f);

	glScalef(1.0f,-1.0f,1.0f);
	glTranslatef(0.0f,0.0f,fBoxSize);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	if(iYShift == 2)
		displayFaceCorners(glInnerPathSweep2f, fBoxSize, fCornerRadius);
	else if(bDrawBlankFaces)
		displayEmptyFace(fBoxSize, fCornerRadius);
	glPopMatrix();

	// (y,z) x=1
	glPushMatrix();
	glTranslatef(fBoxSize,0.0f,0.0f);
	glScalef(-1.0f,1.0f,1.0f);
	glTranslatef(0.0f,0.0f,fBoxSize);
	glRotatef(90.0f,0.0f,1.0f,0.0f);
	if(iXShift == 2)
		displayFaceCorners(glInnerPathSweep2f, fBoxSize, fCornerRadius);
	else if(bDrawBlankFaces)
		displayEmptyFace(fBoxSize, fCornerRadius);
	glPopMatrix();

#endif

}

void drawTexturedFace(float fBoxSize, float fCornerRadius, GLint gluTex, int iSubFace){

	fBoxSize = fBoxSize - 2.0f*fCornerRadius;

	float fFarCorner = fBoxSize - fCornerRadius;
	float fEdgeLength = fBoxSize - 2.0f*fCornerRadius;

	float fUVCornerRadius = fCornerRadius / fBoxSize;
	float fUVFarCorner = fFarCorner / fBoxSize;
	float fUVEdgeLength = fEdgeLength / fBoxSize;
	int iSubHorz = (iSubFace % 3);
	int iSubVert = (iSubFace / 3);
	float fSubHorz = 2.0f-(float)iSubHorz;
	float fSubVert = 2.0f-(float)iSubVert;
	float fUVSub = 1.0f/3.0f;

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(fCornerRadius, fCornerRadius, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, gluTex );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); 
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(-1.0f*fSubHorz*fUVSub,-1.0f*fSubVert*fUVSub,0.0f);
	glScalef(fUVSub,fUVSub,fUVSub);

#ifdef DISPLAY_FACE_CORNERS

/*	(0,0) corner		*/
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(0.0f*fUVFarCorner, 0.0f*fUVFarCorner, 0.0f);
	glScalef(fUVCornerRadius, fUVCornerRadius, 1.0f);
	glTranslatef(-1.0f, -1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(1.0f*fCornerRadius, 1.0f*fCornerRadius, 0.0f);
	glScalef(-1.0f*fCornerRadius, -1.0f*fCornerRadius, 1.0f);
	wmTexturedBezierFan2f(glOuterPathSweep2f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

/*	(1,0) corner		*/
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(-1.0f*fUVFarCorner, 0.0f*fUVFarCorner, 0.0f);
	glScalef(-1.0f*fUVCornerRadius, 1.0f*fUVCornerRadius, 1.0f);
	glTranslatef(0.0f, -1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(fFarCorner, fCornerRadius, 0.0f);
	glScalef(1.0f*fCornerRadius, -1.0f*fCornerRadius, 1.0f);
	wmTexturedBezierFan2f(glOuterPathSweep2f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

/*	(0,1) corner		*/
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(0.0f*fUVFarCorner, -1.0f*fUVFarCorner, 0.0f);
	glScalef(1.0f*fUVCornerRadius, -1.0f*fUVCornerRadius, 1.0f);
	glTranslatef(-1.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(fCornerRadius, fFarCorner, 0.0f);
	glScalef(-1.0f*fCornerRadius, 1.0f*fCornerRadius, 1.0f);
	wmTexturedBezierFan2f(glOuterPathSweep2f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

/*	(1,1) corner		*/
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(-1.0f*fUVFarCorner, -1.0f*fUVFarCorner, 0.0f);
	glScalef(-1.0f*fUVCornerRadius, -1.0f*fUVCornerRadius, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(fFarCorner, fFarCorner, 0.0f);
	glScalef(1.0f*fCornerRadius, 1.0f*fCornerRadius, 1.0f);
	wmTexturedBezierFan2f(glOuterPathSweep2f, 4, 4, NUM_BEZIER_DIV);
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

#endif

#ifdef DISPLAY_CENTER

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(-1.0f*fUVCornerRadius, -1.0f*fUVCornerRadius, 0.0f);
	glScalef(-1.0f*fUVEdgeLength, -1.0f*fUVEdgeLength, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(fCornerRadius, fCornerRadius, 0.0f);
	glScalef(1.0f*fEdgeLength, 1.0f*fEdgeLength, 1.0f);
	wmTexturedUnitSquare();
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

#endif

#ifdef DISPLAY_EDGES

/*	face edge from (0,0) to (1,0)		*/
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(-1.0f*fUVCornerRadius, -0.0f*fUVFarCorner, 0.0f);
	glScalef(-1.0f*fUVEdgeLength, -1.0f*fUVCornerRadius, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(1.0f*fCornerRadius, 0.0f*fFarCorner, 0.0f);
	glScalef(1.0f*fEdgeLength, 1.0f*fCornerRadius, 1.0f);
	wmTexturedUnitSquare();
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

/*	face edge from (0,1) to (1,1)		*/
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(-1.0f*fUVCornerRadius, -1.0f*fUVFarCorner, 0.0f);
	glScalef(-1.0f*fUVEdgeLength, -1.0f*fUVCornerRadius, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(1.0f*fCornerRadius, 1.0f*fFarCorner, 0.0f);
	glScalef(1.0f*fEdgeLength, 1.0f*fCornerRadius, 1.0f);
	wmTexturedUnitSquare();
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

/*	face edge from (0,0) to (0,1)		*/
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(-0.0f*fUVFarCorner, -1.0f*fUVCornerRadius, 0.0f);
	glScalef(-1.0f*fUVCornerRadius, -1.0f*fUVEdgeLength, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0.0f*fFarCorner, 1.0f*fCornerRadius, 0.0f);
	glScalef(1.0f*fCornerRadius, 1.0f*fEdgeLength, 1.0f);
	wmTexturedUnitSquare();
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

/*	face edge from (1,0) to (1,1)		*/
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glTranslatef(-1.0f*fUVFarCorner, -1.0f*fUVCornerRadius, 0.0f);
	glScalef(-1.0f*fUVCornerRadius, -1.0f*fUVEdgeLength, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(1.0f*fFarCorner, 1.0f*fCornerRadius, 0.0f);
	glScalef(1.0f*fCornerRadius, 1.0f*fEdgeLength, 1.0f);
	wmTexturedUnitSquare();
	glPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
#endif
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

	glDisable( GL_TEXTURE_2D );

	glMatrixMode(GL_MODELVIEW);


}
