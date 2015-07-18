/*

	Assignment:	Homework Program 01
	Date:           01/24/2014
	Class:          CSE-3320
	Student:        Jeff Wood
	Purpose:	Create a Shell 

*/
/*          ***** CHANGE LOG ****               */

/*
06/05/2013 - 	Put changes here
06/24/2013 -	Replaced DOS format of 'template.c' with Unix Format
06/26/2013 -	Corrected indentation on 'return 0;' in 'main'
06/28/2013 -	Replaced 'void' parameter set of 'main' function with 'int argc, char* argv[]' 
07/13/2013 -	Added <stdlib.h> and <string.h> include files
07/16/2013 -	Added '#define' statements for '#define FALSE (0)' and '#define TRUE (1)'
02/08/2014 -	Added '#include <time.h>' and '#define DEBUG' statements
02/08/2014 -	Added 'FILE* fileOut = fopen("./debug.txt","w");'
06/01/2014 -	Created 'rubik.c', 'bezier.c' and 'bezier.h' code files
06/06/2014 -	Added 'wmBezier2f', 'wmBezierSweep2f', and 'wmBezierTriangle3f' functions to 'bezier.c' and 'bezier.h'
06/12/2014 -	Added 'wmBezierCurveSum', 'wmBezierTriSum', and 'wmBezierFan2f' functions to 'bezier.c' and 'bezier.h'
06/14/2014 -	Created 'shapes.c' and 'shapes.h'
06/14/2014 -	Added 'drawCubieAdjacentEdges', 'drawCubieFaceCorners', and 'drawCubie' functions to 'shapes.c' and 'shapes.h'
06/20/2014 -	Corrected lighting issues
07/18/2014 -	Added 'wmTexturedBezierFan2f', and 'wmTexturedUnitSquare' functions to 'bezier.c' and 'bezier.h'
07/19/2014 -	Added 'drawFace' function to 'shapes.c' and 'shapes.h'
07/19/2014 -	Added '#include "SOIL.h"' to 'rubik.c' 
07/23/2014 -	Added backlog of changes
07/23/2014 -	Created 'permutations.c' and 'permutations.h'
07/26/2014 -	Added 'wmUnitSquare' function to 'bezier.c' and 'bezier.h'
07/26/2014 -	Replaced 'PERMUTATION_ROWS' with 'PERMUTATION_COLS'
07/26/2014 -	Added 'displayEmptyFace' functions to 'shapes.c' and 'shapes.h'
07/26/2014 -	Created 'drawing.c' and 'drawing.h'
07/26/2014 -	Moved 'loadTextureInfo' function to 'drawing.c' and 'drawing.h'
07/26/2014 -	Added 'drawFullCube' function to 'drawing.c' and 'drawing.h'
08/09/2014 -	Renamed function from 'drawFace' to 'drawTextureFace'
08/09/2014 -	Added 'drawNumberedFace' function to 'drawing.c' and 'drawing.h'
08/12/2014 -	Added 'applyPermutationString' function to 'permutations.c' and 'permutations.h'
08/13/2014 -	Added 'cApplySingleMove' function to 'permutations.c' and 'permutations.h'
08/13/2014 -	Added 'printArray' function to 'permutations.c' and 'permutations.h'
08/14/2014 -	Updated 'cApplyMove' function in 'permutations.c' and 'permutations.h'
08/14/2014 -	Added 'generateRandomMoves' function to 'permutations.c' and 'permutations.h'
08/15/2014 -	Modified function signature of 'drawCubie' in 'shapes.c' and 'shapes.h'
08/15/2014 -	Added 'drawPartialCube' function to 'drawing.c' and 'drawing.h'
08/15/2014 -	Modified function signature and body of 'generateRandomMoves' function in 'permutations.c' and 'permutations.h'
08/15/2014 -	Added 'resetBuffers' function to 'permuations.c' and 'permutations.h'
08/27/2014 -	Corrected error in 'generateRandomMoves' function in 'permuations.c' causing funny redraw
08/27/2014 -	Corrected error in 'generateRandomMoves' providing incorrect 'iPrevFace' and 'iPrevDir' for 'Up' faces
08/27/2014 -	Replaced references to 'char' with 'unsigned char' for use in 'move' data and info variables and arrays.
*/


#define FALSE (0)
#define TRUE (1)

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "drawing.h"
#include "permutations.h"

#define DEBUGd
#define USE_PERSPECTIVE
#define USE_ORTHOGRAPHICd
#define CUBE_SIZE (1.0f)
#define CORNER_RADIUS (0.075f)

#define SPEED_SLICE (15.0f)
#define SPEED_VIEW_PHI (10.0f)
#define SPEED_VIEW_SIGMA (10.0f)

#define DELAY (unsigned int)(50)

#define ANIMATION_SHOW
char cPicDir[512];
char cUserName[512];
char cCurrWorkingDir[512];
DIR* dirPics;
GLfloat m[16]; 
const int startwinsize = 400; // Starting window width & height, in pixels
int winw, winh;               // Window width & height, in pixels, saved by reshape

// Mouse
int mouseleftdown = 1;   // True if mouse LEFT button is down.
                              // Saved by mouse.
int mousex=0, mousey=0;           // Mouse x,y coords, in GLUT format (pixels from upper-left corner).
                              // Only guaranteed to be valid if a mouse button is down.
                              // Saved by mouse, motion.
// mouse
// The GLUT mouse function

extern GLuint texUp, texLeft, texFront, texRight, texBack, texDown;
extern unsigned char cRubikStateBuffer[][PERMUTATION_COLS];
extern unsigned char cRubikCopyBuffer[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CW_Up[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CW_Left[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CW_Front[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CW_Right[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CW_Back[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CW_Down[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CCW_Up[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CCW_Left[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CCW_Front[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CCW_Right[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CCW_Back[][PERMUTATION_COLS];
extern unsigned char cRubikMove_CCW_Down[][PERMUTATION_COLS];

extern unsigned char* cMoves;
extern unsigned char* cMarker;
extern int iMoveState;
//extern int iTokenCount;		// Count of parsed groupings of letters , "F", "UU", "RRR", "BBBB" and "H" each count as 1
extern int iArrayCount;		// Count of valid moves "F" and "RRR" count as 1, "UU" count as two and "BBBB" and "H" count as 0

//float fSpeed = 15.0f;
float fRotateSlice = 0.0f;
float fRotateViewPhi = 0.0f;
float fRotateViewSigma = 0.0f;

#ifdef ANIMATION_SHOW
void mouse(int button, int state, int x, int y){

//	glMatrixMode(GL_MODELVIEW);

	// Save the left button state
	if (button == GLUT_LEFT_BUTTON){
		mouseleftdown = (state == GLUT_DOWN);
		glutPostRedisplay();  // Left button has changed; redisplay!
//		glutSwapBuffers();
	}
	// Save the mouse position
	mousex = x;
	mousey = y;
}


// motion
// The GLUT motion function
void motion(int x, int y){
	// We only do anything if the left button is down
//	glMatrixMode(GL_MODELVIEW);


	if (mouseleftdown)
		glutSwapBuffers();
	glutPostRedisplay();

	// Save the mouse position
	mousex = x;
	mousey = y;
}
#endif
void drawAxis(float fScale){

//	float fScale = 0.1f;
	glLineWidth(0.2);

	glNormal3f(0.0f, 0.0f, 1.0f);

	/* x */
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(fScale,0.0,0.0);
	glEnd();

	/* y */
	glBegin(GL_LINES);
	glColor3f(0.0,1.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,fScale,0.0);
	glEnd();

	/* z */
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,1.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,0.0,fScale);
	glEnd();

}

void drawCube(float fDegrees){

	int iInc = 0;

	unsigned char (*cMoveArr)[PERMUTATION_COLS];

	float fDirMultiplier = 1.0f;
	float fXBasis = 0.0f, fYBasis = 0.0f, fZBasis = 0.0f; 
	unsigned char cSegment = 0, cDimension = 0;

	if((*cMarker) & (MOVE_FACE_RIGHT | MOVE_FACE_LEFT)){
		fXBasis = 1.0f;
		fYBasis = 0.0f;
		fZBasis = 0.0f;
		cDimension |= PARTIAL_DIMENSION_X;
	}
	if((*cMarker) & (MOVE_FACE_DOWN | MOVE_FACE_UP)){
		fXBasis = 0.0f;
		fYBasis = 1.0f;
		fZBasis = 0.0f;
		cDimension |= PARTIAL_DIMENSION_Y;
	}
	if((*cMarker) & (MOVE_FACE_BACK | MOVE_FACE_FRONT)){
		fXBasis = 0.0f;
		fYBasis = 0.0f;
		fZBasis = 1.0f;	
		cDimension |= PARTIAL_DIMENSION_Z;
	}

	if((*cMarker) & (MOVE_FACE_RIGHT | MOVE_FACE_DOWN | MOVE_FACE_FRONT)){
		fDirMultiplier = 1.0f;
		cSegment |= PARTIAL_SEGMENT_0;
	}

	if((*cMarker) & (MOVE_FACE_LEFT | MOVE_FACE_UP | MOVE_FACE_BACK)){
		fDirMultiplier = -1.0f;
		cSegment |= PARTIAL_SEGMENT_2;
	}

	fDirMultiplier *= (((*cMarker) & MOVE_DIR_CCW) ? -1.0f : 1.0f); 
	fDirMultiplier *= ((iMoveState == MOVE_STATE_BACKWARD) ? -1.0f : 1.0f); 

	if((*cMarker) & MOVE_FACE_UP)
		cMoveArr = cRubikMove_CW_Up;
	if((*cMarker) & MOVE_FACE_LEFT)
		cMoveArr = cRubikMove_CW_Left;
	if((*cMarker) & MOVE_FACE_FRONT)
		cMoveArr = cRubikMove_CW_Front;
	if((*cMarker) & MOVE_FACE_RIGHT)
		cMoveArr = cRubikMove_CW_Right;
	if((*cMarker) & MOVE_FACE_BACK)
		cMoveArr = cRubikMove_CW_Back;
	if((*cMarker) & MOVE_FACE_DOWN)
		cMoveArr = cRubikMove_CW_Down;

#ifdef DEBUG
	printf(" (*cMarker) = %d;\n", (*cMarker) &  252);
#endif
	//	Face Not Being Rotated
	for(iInc = 0; iInc < 54; iInc++){
		if(cMoveArr[2][iInc] == 0)
			drawNumberedFace(CUBE_SIZE, CORNER_RADIUS, iInc);
	}
	
	//	Cubes Not Being Rotated
	drawPartialCube(CUBE_SIZE, CORNER_RADIUS, (~cSegment), cDimension);
	
	glPushMatrix();

	glTranslatef(1.5f*CUBE_SIZE, 1.5f*CUBE_SIZE, 1.5f*CUBE_SIZE);
	glRotatef(fDirMultiplier*fDegrees, fXBasis, fYBasis, fZBasis);
	glTranslatef(-1.5f*CUBE_SIZE, -1.5f*CUBE_SIZE, -1.5f*CUBE_SIZE);

	//	Face Being Rotated
	for(iInc = 0; iInc < 54; iInc++){
		if(cMoveArr[2][iInc] == 1)
			drawNumberedFace(CUBE_SIZE, CORNER_RADIUS, iInc);
	}

	//	Cubes Being Rotated
	drawPartialCube(CUBE_SIZE, CORNER_RADIUS, cSegment, cDimension);

	glPopMatrix();

}

void draw(){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	


	glLoadIdentity();             // Reset
	glPushMatrix();

#ifdef ANIMATION_SHOW 
	glRotatef(fRotateViewPhi, 1.0f, 0.0f, 0.0f);
	glRotatef(fRotateViewSigma, 0.0f, 1.0f, 0.0f);

#else
	glRotatef((float)mousex,0.0f,1.0f,0.0f);
	glRotatef((float)mousey,1.0f,0.0f,0.0f);

//	glRotatef(45.0f,1.0f,0.0f,0.0f);
//	glRotatef(45.0f,0.0f,1.0f,0.0f);
#endif

#ifdef ANIMATION_SHOW
	glScalef(0.5f, 0.5f, 0.5f);
#else
	glScalef(0.4f, 0.4f, 0.4f);
#endif
	glTranslatef(-1.5f,-1.5f,-1.5f);


#ifdef ANIMATION_SHOW
	drawCube(fRotateSlice);
#else
	resetBuffers();

	int iInc;
	for(iInc = 0; iInc < 54; iInc++){
//		if(cMoveArr[2][iInc] == 1)
			drawNumberedFace(CUBE_SIZE, CORNER_RADIUS, iInc);
	}

	//	Cubes Being Rotated
	drawFullCube(CUBE_SIZE, CORNER_RADIUS);
#endif
	glPopMatrix();

#ifdef ANIMATION_SHOW
	//	code to update permutations when move has completed
	if(fRotateSlice >= 90.0f){
		fRotateSlice = 0.0f;
		unsigned char cFace = 0;
		unsigned char cDir = 0;
		unsigned char cMove = 0;

		if(iMoveState == MOVE_STATE_BACKWARD){	// Working the way back on permutations
			cFace = (*cMarker) & MOVE_FACES;					// filter out Direction (Face remains)
			cDir = (~((*cMarker) & MOVE_DIRS)) & MOVE_DIRS;				// filter out Face (Direciton remains) then Reverse Direction
			cMove = cFace | cDir;							// combine to apply effective going in reverse
			cApplySingleMove(&cMove);

			if(cMarker == cMoves){
				generateRandomMoves((unsigned char)(0));
				cMarker = cMoves;
				iMoveState = MOVE_STATE_FORWARD;
			}else
				cMarker--;

		}else if(iMoveState == MOVE_STATE_FORWARD){
			cApplySingleMove(cMarker);

			if((cMarker - cMoves) >= (iArrayCount - 1))
				iMoveState = MOVE_STATE_BACKWARD;				//	reverse direction
			else
				cMarker++;

		}

	}else
		fRotateSlice += SPEED_SLICE;


	fRotateViewPhi += SPEED_VIEW_PHI;
	fRotateViewSigma += SPEED_VIEW_SIGMA;

#endif

//	glutPostRedisplay();

	glutSwapBuffers();


}



//Main program
void init(){

//	srand((unsigned int)time(void));


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowPosition(0,0);
	glutInitWindowSize( 512, 512 );
//	glutInitContextVersion( 2, 1 );

	glutCreateWindow("Window");

	GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };



	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_RESCALE_NORMAL);

	glClearColor(0,0,0,1.0);
	glClearDepth(20.0f);       // Set background depth to farthest
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test


#ifdef USE_PERSPECTIVE
	glViewport(0,0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective	(60.0f, 1.0f, 0.1f, 10.0f);
	glTranslatef(0.0f,0.0f,-1.5f);
	glScalef(0.60f,0.60f,0.60f);

#endif	

#ifdef USE_ORTHOGRAPHIC
	glViewport(0,0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	glTranslatef(0.0f,0.0f,-0.0f);
	glScalef(0.50f,0.50f,0.50f);
#endif

	glMatrixMode(GL_MODELVIEW);


	loadTextureInfo();


}


void parseCommandArguments(int argc, char* (argv[])){

	int iInc;

	memset(cUserName, 0, sizeof(cUserName));
	memset(cCurrWorkingDir, 0, sizeof(cCurrWorkingDir));
	memset(cPicDir, 0, sizeof(cPicDir));

	getlogin_r(cUserName, sizeof(cUserName));
	getcwd(cCurrWorkingDir, sizeof(cCurrWorkingDir));

	memset(cPicDir, 0, sizeof(cPicDir));
	strcpy(cPicDir,"~");
	strcat(cPicDir,"Pictures");	 
#ifdef DEBUG	
	printf(" cUserName = %s; cCurrWorkingDir = %s; \n", cUserName, cCurrWorkingDir);
#endif
	for(iInc = 0; iInc < argc; iInc++){
		if(*(argv[iInc]+0) == '-' && *(argv[iInc]+1) == 'm' && strlen(argv[iInc]) > 2)
			applyPermutationString(argv[iInc]+2);

		if(*(argv[iInc]+0) == '-' && *(argv[iInc]+1) == 'd' && strlen(argv[iInc]) > 2){
			memset(cPicDir, 0, sizeof(cPicDir));
			strcpy(cPicDir, argv[iInc]+2);
			dirPics = opendir("~");
			dirPics = opendir(cPicDir);
			
		};

	}

	if(iMoveState == MOVE_STATE_NONE){	//no '-m' found or no valid '-m' string found
		generateRandomMoves((unsigned char)(1));
	}

}

void update(int n){

	glutPostRedisplay();
	glutTimerFunc(DELAY,update,0);
}

int main(int argc, char* argv[]){



#ifdef DEBUG
	FILE* fileOut = fopen("./debug.txt","w");
	fprintf(fileOut," *** Debug File Created *** \n");
#endif

	parseCommandArguments(argc, argv);
	

	glutInit(&argc, argv);
	//Simple buffer
	init();
//	glGetFloatv (GL_MODELVIEW_MATRIX, m);

	//Call to the drawing function
	glutDisplayFunc(draw);
#ifdef ANIMATION_SHOW
	glutTimerFunc(DELAY,update,0);
#else
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
#endif
	glutMainLoop();


#ifdef DEBUG
	fclose(fileOut);
#endif
	return 0;
}
