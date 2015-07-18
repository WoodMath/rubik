#include "bezier.h"
#define DEBUGD
#define DEBUG_COLORS
#define USE_NORMAL
#define NORMAL_DIR 1.0f
float wmBezierCurveSum(float fBezierArr[4][2], float fInc, int iCol){
	
	float fReturn = 
		1.0f*(fBezierArr[0][iCol])*pow(1.0f-fInc,3.0) + 
		3.0f*(fBezierArr[1][iCol])*pow(1.0f-fInc,2.0)*pow(fInc,1.0) + 
		3.0f*(fBezierArr[2][iCol])*pow(1.0f-fInc,1.0)*pow(fInc,2.0) + 
		1.0f*(fBezierArr[3][iCol])*pow(fInc,3.0) ;

	return fReturn;
}

float wmBezierTriSum(float fBezierArr[4][4][3], float fIncU, float fIncV, int iCol){
	
	float fReturn = 
		1.0f*(fBezierArr[0][0][iCol])*pow(1.0f-fIncU-fIncV,3.0) + 
		3.0f*(fBezierArr[0][1][iCol])*pow(fIncV,1.0)*pow(1.0f-fIncU-fIncV,2.0) + 
		3.0f*(fBezierArr[0][2][iCol])*pow(fIncV,2.0)*pow(1.0f-fIncU-fIncV,1.0) + 
		1.0f*(fBezierArr[0][3][iCol])*pow(fIncV,3.0) + 
		3.0f*(fBezierArr[1][0][iCol])*pow(fIncU,1.0)*pow(1.0f-fIncU-fIncV,2.0) + 
		6.0f*(fBezierArr[1][1][iCol])*pow(fIncU,1.0)*pow(fIncV,1.0)*pow(1.0f-fIncU-fIncV,1.0) + 
		3.0f*(fBezierArr[1][2][iCol])*pow(fIncU,1.0)*pow(fIncV,2.0) + 
		3.0f*(fBezierArr[2][0][iCol])*pow(fIncU,2.0)*pow(1.0f-fIncU-fIncV,1.0) + 
		3.0f*(fBezierArr[2][1][iCol])*pow(fIncU,2.0)*pow(fIncV,1.0) + 
		1.0f*(fBezierArr[3][0][iCol])*pow(fIncU,3.0);

	return fReturn;
}

void wmBezier2f(float fBezierArr[4][2], unsigned int iRows, unsigned int iCols, unsigned int iNDivs){

#ifdef DEBUG
	printf(" wmBezier2f : iNDivs = %u ;\n", iNDivs);

#endif

	unsigned int iInc = 0;


	glBegin(GL_LINE_STRIP);
#ifdef GRAY_TEST
	glColor3f(0.0f,GRAY_SCALE,0.0f);
#else
	glColor3f(GRAY_SCALE,GRAY_SCALE,GRAY_SCALE);
#endif
	for(iInc = 0; iInc <= iNDivs; iInc++){
		float fInc = ((float)iInc)/((float)iNDivs);

		float bezierXf = wmBezierCurveSum(fBezierArr, fInc, 0);
		float bezierYf = wmBezierCurveSum(fBezierArr, fInc, 1);

		glVertex2f(bezierXf, bezierYf);

	}

	glEnd();


#ifdef DEBUG
	glPointSize(5.0f);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(fBezierArr[0][0], fBezierArr[0][1]);
	glVertex2f(fBezierArr[1][0], fBezierArr[1][1]);
	glVertex2f(fBezierArr[2][0], fBezierArr[2][1]);
	glVertex2f(fBezierArr[3][0], fBezierArr[3][1]);
//	glVertex2f(0.0f, 0.0f);
	glEnd();

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
//	glVertex2f(0.0f, 0.0f);
	glVertex2f(fBezierArr[0][0], fBezierArr[0][1]);
	glVertex2f(fBezierArr[1][0], fBezierArr[1][1]);
	glVertex2f(fBezierArr[2][0], fBezierArr[2][1]);
	glVertex2f(fBezierArr[3][0], fBezierArr[3][1]);
//	glVertex2f(0.0f, 0.0f);
	glEnd();
#endif
	return;
}

void wmBezierSweep2f(float fBezierArr[4][2], float fZNear, float fZFar, unsigned int iRows, unsigned int iCols, unsigned int iNDivs){

#ifdef DEBUG
	printf(" wmBezierSweep2f : fZNear = %5.3f ;\n", fZNear);
	printf(" wmBezierSweep2f : fZFar = %5.3f ;\n", fZFar);
	printf(" wmBezierSweep2f : iNDivs = %u ;\n", iNDivs);

#endif
	unsigned int iInc = 0;


	glBegin(GL_TRIANGLE_STRIP);
#ifdef GRAY_TEST
	glColor3f(0.0f,GRAY_SCALE,0.0f);
#else
	glColor3f(GRAY_SCALE,GRAY_SCALE,GRAY_SCALE);
#endif


	for(iInc = 0; iInc <= iNDivs; iInc++){
		float fInc = ((float)iInc)/((float)iNDivs);

		float bezierXf = wmBezierCurveSum(fBezierArr, fInc, 0);
		float bezierYf = wmBezierCurveSum(fBezierArr, fInc, 1);
		
#ifdef USE_NORMAL
		glNormal3f(1.0f*NORMAL_DIR*bezierXf, 1.0f*NORMAL_DIR*bezierYf, 0.0f);
#endif
		glVertex3f(bezierXf, bezierYf, fZNear);

#ifdef USE_NORMAL
//		glNormal3f(1.0f*NORMAL_DIR*bezierXf, 1.0f*NORMAL_DIR*bezierYf, 0.0f);
#endif
		glVertex3f(bezierXf, bezierYf, fZFar);

	}

	glEnd();

#ifdef DEBUG
	glPointSize(5.0f);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex3f(fBezierArr[0][0], fBezierArr[0][1], fZNear);
	glVertex3f(fBezierArr[1][0], fBezierArr[1][1], fZNear);
	glVertex3f(fBezierArr[2][0], fBezierArr[2][1], fZNear);
	glVertex3f(fBezierArr[3][0], fBezierArr[3][1], fZNear);
//	glVertex3f(0.0f, 0.0f, fZNear);
	glEnd();

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
//	glVertex3f(0.0f, 0.0f, fZNear);
	glVertex3f(fBezierArr[0][0], fBezierArr[0][1], fZNear);
	glVertex3f(fBezierArr[1][0], fBezierArr[1][1], fZNear);
	glVertex3f(fBezierArr[2][0], fBezierArr[2][1], fZNear);
	glVertex3f(fBezierArr[3][0], fBezierArr[3][1], fZNear);
//	glVertex3f(0.0f, 0.0f, fZNear);
	glEnd();

	glPointSize(5.0f);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex3f(fBezierArr[0][0], fBezierArr[0][1], fZFar);
	glVertex3f(fBezierArr[1][0], fBezierArr[1][1], fZFar);
	glVertex3f(fBezierArr[2][0], fBezierArr[2][1], fZFar);
	glVertex3f(fBezierArr[3][0], fBezierArr[3][1], fZFar);
//	glVertex3f(0.0f, 0.0f, fZFar);
	glEnd();


	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
//	glVertex3f(0.0f, 0.0f, fZFar);
	glVertex3f(fBezierArr[0][0], fBezierArr[0][1], fZFar);
	glVertex3f(fBezierArr[1][0], fBezierArr[1][1], fZFar);
	glVertex3f(fBezierArr[2][0], fBezierArr[2][1], fZFar);
	glVertex3f(fBezierArr[3][0], fBezierArr[3][1], fZFar);
//	glVertex3f(0.0f, 0.0f, fZFar);
	glEnd();

/*
	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(fBezierArr[0][0], fBezierArr[0][1], fZNear);
	glVertex3f(0.0f, 0.0f, fZNear);
	glVertex3f(fBezierArr[3][0], fBezierArr[3][1], fZNear);
	glEnd();

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(fBezierArr[0][0], fBezierArr[0][1], fZFar);
	glVertex3f(0.0f, 0.0f, fZFar);
	glVertex3f(fBezierArr[3][0], fBezierArr[3][1], fZFar);
	glEnd();
*/

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
/*
	glVertex3f(0.0f, 0.0f, fZNear);
	glVertex3f(0.0f, 0.0f, fZFar);
*/
	glVertex3f(fBezierArr[0][0], fBezierArr[0][1], fZNear);
	glVertex3f(fBezierArr[0][0], fBezierArr[0][1], fZFar);

	glVertex3f(fBezierArr[1][0], fBezierArr[1][1], fZNear);
	glVertex3f(fBezierArr[1][0], fBezierArr[1][1], fZFar);

	glVertex3f(fBezierArr[2][0], fBezierArr[2][1], fZNear);
	glVertex3f(fBezierArr[2][0], fBezierArr[2][1], fZFar);

	glVertex3f(fBezierArr[3][0], fBezierArr[3][1], fZNear);
	glVertex3f(fBezierArr[3][0], fBezierArr[3][1], fZFar);

	glEnd();

#endif

	return;
}

void wmBezierTriangle3f(float fBezierArr[4][4][3], unsigned int iRows, unsigned int iCols, unsigned int iNDivs){

#ifdef DEBUG
	printf(" wmBezierTriangle3f : iNDivs = %u ;\n", iNDivs);

#endif
	int iIncU = 0, iIncV = 0;



	for(iIncU = 0; iIncU < iNDivs; iIncU++){

		float fIncU=0, fIncV=0, fIncNextU=0;
		float bezierXf, bezierYf, bezierZf;
		float bezierNextXf, bezierNextYf, bezierNextZf;

		glBegin(GL_TRIANGLE_STRIP);

#ifdef GRAY_TEST
		glColor3f(0.0f,GRAY_SCALE,0.0f);
#else
		glColor3f(GRAY_SCALE,GRAY_SCALE,GRAY_SCALE);
#endif

		
		for(iIncV = 0; iIncV < (iNDivs - iIncU)*1; iIncV++){
			fIncU = ((float)iIncU)/((float)iNDivs);
			fIncV = ((float)iIncV)/((float)iNDivs);

			fIncNextU = ((float)(iIncU+1))/((float)iNDivs);
			
			bezierXf = wmBezierTriSum(fBezierArr,fIncU, fIncV, 0);
			bezierYf = wmBezierTriSum(fBezierArr,fIncU, fIncV, 1);
			bezierZf = wmBezierTriSum(fBezierArr,fIncU, fIncV, 2);

			bezierNextXf = wmBezierTriSum(fBezierArr,fIncNextU, fIncV, 0);
			bezierNextYf = wmBezierTriSum(fBezierArr,fIncNextU, fIncV, 1);
			bezierNextZf = wmBezierTriSum(fBezierArr,fIncNextU, fIncV, 2);

#ifdef USE_NORMAL
			glNormal3f(NORMAL_DIR*bezierXf, NORMAL_DIR*bezierYf, NORMAL_DIR*bezierZf);		
#endif
			glVertex3f(bezierXf, bezierYf, bezierZf);

#ifdef USE_NORMAL
			glNormal3f(NORMAL_DIR*bezierNextXf, NORMAL_DIR*bezierNextYf, NORMAL_DIR*bezierNextZf);
#endif
			glVertex3f(bezierNextXf, bezierNextYf, bezierNextZf);

		}

		fIncU = ((float)iIncU)/((float)iNDivs);
		fIncV = ((float)iIncV)/((float)iNDivs);


		bezierXf = wmBezierTriSum(fBezierArr,fIncU, fIncV, 0);
		bezierYf = wmBezierTriSum(fBezierArr,fIncU, fIncV, 1);
		bezierZf = wmBezierTriSum(fBezierArr,fIncU, fIncV, 2);

#ifdef USE_NORMAL
		glNormal3f(NORMAL_DIR*bezierXf, NORMAL_DIR*bezierYf, NORMAL_DIR*bezierZf);
#endif
		glVertex3f(bezierXf, bezierYf, bezierZf);
		glEnd();

	}
	
#ifdef DEBUG
	glPointSize(15.0f);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);

#ifdef DEBUG_COLORS
	glColor3f(0.0f/3.0f, 0.0f/3.0f, 3.0f/3.0f);
#endif
	glVertex3f(fBezierArr[0][0][0], fBezierArr[0][0][1], fBezierArr[0][0][2]);

#ifdef DEBUG_COLORS
	glColor3f(0.0f/3.0f, 1.0f/3.0f, 2.0f/3.0f);
#endif
	glVertex3f(fBezierArr[0][1][0], fBezierArr[0][1][1], fBezierArr[0][1][2]);

#ifdef DEBUG_COLORS
	glColor3f(0.0f/3.0f, 2.0f/3.0f, 1.0f/3.0f);
#endif
	glVertex3f(fBezierArr[0][2][0], fBezierArr[0][2][1], fBezierArr[0][2][2]);

#ifdef DEBUG_COLORS
	glColor3f(0.0f/3.0f, 3.0f/3.0f, 0.0f/3.0f);
#endif
	glVertex3f(fBezierArr[0][3][0], fBezierArr[0][3][1], fBezierArr[0][3][2]);

#ifdef DEBUG_COLORS
	glColor3f(1.0f/3.0f, 0.0f/3.0f, 2.0f/3.0f);
#endif
	glVertex3f(fBezierArr[1][0][0], fBezierArr[1][0][1], fBezierArr[1][0][2]);

#ifdef DEBUG_COLORS
	glColor3f(1.0f/3.0f, 1.0f/3.0f, 1.0f/3.0f);
#endif
	glVertex3f(fBezierArr[1][1][0], fBezierArr[1][1][1], fBezierArr[1][1][2]);

#ifdef DEBUG_COLORS
	glColor3f(1.0f/3.0f, 2.0f/3.0f, 0.0f/3.0f);
#endif
	glVertex3f(fBezierArr[1][2][0], fBezierArr[1][2][1], fBezierArr[1][2][2]);

#ifdef DEBUG_COLORS
	glColor3f(2.0f/3.0f, 1.0f/3.0f, 0.0f/3.0f);
#endif
	glVertex3f(fBezierArr[2][0][0], fBezierArr[2][0][1], fBezierArr[2][0][2]);

#ifdef DEBUG_COLORS
	glColor3f(2.0f/3.0f, 1.0f/3.0f, 0.0f/3.0f);
#endif
	glVertex3f(fBezierArr[2][1][0], fBezierArr[2][1][1], fBezierArr[2][1][2]);

#ifdef DEBUG_COLORS
	glColor3f(3.0f/3.0f, 0.0f/3.0f, 0.0f/3.0f);
#endif
	glVertex3f(fBezierArr[3][0][0], fBezierArr[3][0][1], fBezierArr[3][0][2]);

//	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);

	// row 1
	glVertex3f(fBezierArr[0][1][0], fBezierArr[0][1][1], fBezierArr[0][1][2]); 
	glVertex3f(fBezierArr[0][0][0], fBezierArr[0][0][1], fBezierArr[0][0][2]);

	glVertex3f(fBezierArr[0][0][0], fBezierArr[0][0][1], fBezierArr[0][0][2]);
	glVertex3f(fBezierArr[1][0][0], fBezierArr[1][0][1], fBezierArr[1][0][2]);

	glVertex3f(fBezierArr[1][0][0], fBezierArr[1][0][1], fBezierArr[1][0][2]);
	glVertex3f(fBezierArr[0][1][0], fBezierArr[0][1][1], fBezierArr[0][1][2]); 

	// row 2
	glVertex3f(fBezierArr[1][0][0], fBezierArr[1][0][1], fBezierArr[1][0][2]);
	glVertex3f(fBezierArr[2][0][0], fBezierArr[2][0][1], fBezierArr[2][0][2]);

	glVertex3f(fBezierArr[2][0][0], fBezierArr[2][0][1], fBezierArr[2][0][2]);
	glVertex3f(fBezierArr[1][1][0], fBezierArr[1][1][1], fBezierArr[1][1][2]);

	glVertex3f(fBezierArr[1][1][0], fBezierArr[1][1][1], fBezierArr[1][1][2]);
	glVertex3f(fBezierArr[1][0][0], fBezierArr[1][0][1], fBezierArr[1][0][2]);

	glVertex3f(fBezierArr[0][1][0], fBezierArr[0][1][1], fBezierArr[0][1][2]); 
	glVertex3f(fBezierArr[0][2][0], fBezierArr[0][2][1], fBezierArr[0][2][2]); 

	glVertex3f(fBezierArr[0][2][0], fBezierArr[0][2][1], fBezierArr[0][2][2]); 
	glVertex3f(fBezierArr[1][1][0], fBezierArr[1][1][1], fBezierArr[1][1][2]);

	glVertex3f(fBezierArr[1][1][0], fBezierArr[1][1][1], fBezierArr[1][1][2]);
	glVertex3f(fBezierArr[0][1][0], fBezierArr[0][1][1], fBezierArr[0][1][2]); 

	// row 3
	glVertex3f(fBezierArr[0][2][0], fBezierArr[0][2][1], fBezierArr[0][2][2]); 
	glVertex3f(fBezierArr[0][3][0], fBezierArr[0][3][1], fBezierArr[0][3][2]); 

	glVertex3f(fBezierArr[0][3][0], fBezierArr[0][3][1], fBezierArr[0][3][2]); 
	glVertex3f(fBezierArr[1][2][0], fBezierArr[1][2][1], fBezierArr[1][2][2]); 

	glVertex3f(fBezierArr[1][2][0], fBezierArr[1][2][1], fBezierArr[1][2][2]); 
	glVertex3f(fBezierArr[1][1][0], fBezierArr[1][1][1], fBezierArr[1][1][2]); 

	glVertex3f(fBezierArr[1][1][0], fBezierArr[1][1][1], fBezierArr[1][1][2]); 
	glVertex3f(fBezierArr[2][1][0], fBezierArr[2][1][1], fBezierArr[2][1][2]); 

	glVertex3f(fBezierArr[2][1][0], fBezierArr[2][1][1], fBezierArr[2][1][2]); 
	glVertex3f(fBezierArr[1][2][0], fBezierArr[1][2][1], fBezierArr[1][2][2]);

	glVertex3f(fBezierArr[3][0][0], fBezierArr[3][0][1], fBezierArr[3][0][2]); 
	glVertex3f(fBezierArr[2][0][0], fBezierArr[2][0][1], fBezierArr[2][0][2]); 
 
	glVertex3f(fBezierArr[2][0][0], fBezierArr[2][0][1], fBezierArr[2][0][2]); 
	glVertex3f(fBezierArr[2][1][0], fBezierArr[2][1][1], fBezierArr[2][1][2]); 

	glVertex3f(fBezierArr[2][1][0], fBezierArr[2][1][1], fBezierArr[2][1][2]); 
	glVertex3f(fBezierArr[3][0][0], fBezierArr[3][0][1], fBezierArr[3][0][2]); 
/*
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(fBezierArr[3][0][0], fBezierArr[3][0][1], fBezierArr[3][0][2]); 

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(fBezierArr[0][3][0], fBezierArr[0][3][1], fBezierArr[0][3][2]); 

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(fBezierArr[0][0][0], fBezierArr[0][0][1], fBezierArr[0][0][2]); 
*/
	glEnd();

#endif

	return;
}

void wmBezierFan2f(float fBezierArr[4][2], unsigned int iRows, unsigned int iCols, unsigned int iNDivs){


#ifdef DEBUG
	printf(" wmBezierFan2f : iNDivs = %u ;\n", iNDivs);

#endif
	unsigned int iInc = 0;


	glBegin(GL_TRIANGLE_FAN);
#ifdef GRAY_TEST
	glColor3f(0.0f,GRAY_SCALE,0.0f);
#else
	glColor3f(GRAY_SCALE,GRAY_SCALE,GRAY_SCALE);
#endif

#ifdef USE_NORMAL
	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glVertex3f(0.0f, 0.0f, 0.0f);

	for(iInc = 0; iInc <= iNDivs; iInc++){
		float fInc = ((float)iInc)/((float)iNDivs);

		float bezierXf = wmBezierCurveSum(fBezierArr, fInc, 0);
		float bezierYf = wmBezierCurveSum(fBezierArr, fInc, 1);

#ifdef USE_NORMAL
//		glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
		glVertex3f(bezierXf, bezierYf, 0.0f);

	}

	glEnd();


#ifdef DEBUG
	glPointSize(5.0f);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(fBezierArr[0][0], fBezierArr[0][1]);
	glVertex2f(fBezierArr[1][0], fBezierArr[1][1]);
	glVertex2f(fBezierArr[2][0], fBezierArr[2][1]);
	glVertex2f(fBezierArr[3][0], fBezierArr[3][1]);
//	glVertex2f(0.0f, 0.0f);
	glEnd();

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
//	glVertex2f(0.0f, 0.0f);
	glVertex2f(fBezierArr[0][0], fBezierArr[0][1]);
	glVertex2f(fBezierArr[1][0], fBezierArr[1][1]);
	glVertex2f(fBezierArr[2][0], fBezierArr[2][1]);
	glVertex2f(fBezierArr[3][0], fBezierArr[3][1]);
//	glVertex2f(0.0f, 0.0f);
	glEnd();
#endif
	return;


}

void wmTexturedBezierFan2f(float fBezierArr[4][2], unsigned int iRows, unsigned int iCols, unsigned int iNDivs){


#ifdef DEBUG
	printf(" wmTexturedBezierFan2f : iNDivs = %u ;\n", iNDivs);

#endif
	unsigned int iInc = 0;


	glBegin(GL_TRIANGLE_FAN);
//	glColor3f(GRAY_SCALE,GRAY_SCALE,GRAY_SCALE);

#ifdef USE_NORMAL
	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f(0.0f, 0.0f, 0.0f);

	for(iInc = 0; iInc <= iNDivs; iInc++){
		float fInc = ((float)iInc)/((float)iNDivs);

		float bezierXf = wmBezierCurveSum(fBezierArr, fInc, 0);
		float bezierYf = wmBezierCurveSum(fBezierArr, fInc, 1);

#ifdef USE_NORMAL
//		glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
		glTexCoord2f( bezierXf, bezierYf );
		glVertex3f(bezierXf, bezierYf, 0.0f);

	}

	glEnd();


#ifdef DEBUG
	glPointSize(5.0f);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(fBezierArr[0][0], fBezierArr[0][1]);
	glVertex2f(fBezierArr[1][0], fBezierArr[1][1]);
	glVertex2f(fBezierArr[2][0], fBezierArr[2][1]);
	glVertex2f(fBezierArr[3][0], fBezierArr[3][1]);
//	glVertex2f(0.0f, 0.0f);
	glEnd();

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
//	glVertex2f(0.0f, 0.0f);
	glVertex2f(fBezierArr[0][0], fBezierArr[0][1]);
	glVertex2f(fBezierArr[1][0], fBezierArr[1][1]);
	glVertex2f(fBezierArr[2][0], fBezierArr[2][1]);
	glVertex2f(fBezierArr[3][0], fBezierArr[3][1]);
//	glVertex2f(0.0f, 0.0f);
	glEnd();
#endif
	return;


}

void wmTexturedUnitSquare(){


#ifdef DEBUG
	printf(" wmTexturedUnitSquare ;\n");
#endif

	glBegin(GL_TRIANGLE_STRIP);
//	glColor3f(GRAY_SCALE,GRAY_SCALE,GRAY_SCALE);

#ifdef USE_NORMAL
	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f(0.0f, 0.0f, 0.0f);

#ifdef USE_NORMAL
//	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f(1.0f, 0.0f, 0.0f);

#ifdef USE_NORMAL
//	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f(0.0f, 1.0f, 0.0f);

#ifdef USE_NORMAL
//	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f(1.0f, 1.0f, 0.0f);

	glEnd();


#ifdef DEBUG
	glPointSize(5.0f);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glEnd();

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();
#endif
	return;


}

void wmUnitSquare(){


#ifdef DEBUG
	printf(" wmUnitSquare ;\n");
#endif

	glBegin(GL_TRIANGLE_STRIP);
//	glColor3f(GRAY_SCALE,GRAY_SCALE,GRAY_SCALE);

#ifdef USE_NORMAL
	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glVertex3f(0.0f, 0.0f, 0.0f);

#ifdef USE_NORMAL
//	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glVertex3f(1.0f, 0.0f, 0.0f);

#ifdef USE_NORMAL
//	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glVertex3f(0.0f, 1.0f, 0.0f);

#ifdef USE_NORMAL
//	glNormal3f(0.0f, 0.0f, NORMAL_DIR*-1.0f);
#endif
	glVertex3f(1.0f, 1.0f, 0.0f);

	glEnd();


#ifdef DEBUG
	glPointSize(5.0f);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glEnd();

	glLineWidth(2.5f);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();
#endif
	return;


}

