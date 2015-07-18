#include "drawing.h"
#define DEBUGd

#define PERMUTATION_COLS 54
extern char cRubikStateBuffer[][PERMUTATION_COLS];
extern char cRubikCopyBuffer[][PERMUTATION_COLS];

GLuint texUp, texLeft, texFront, texRight, texBack, texDown;

void loadTextureInfo(){

	unsigned int iFlags = 0;
	iFlags |= SOIL_FLAG_POWER_OF_TWO;

//	glBindTexture( GL_TEXTURE_2D, texFront );
/*
	texUp = SOIL_load_OGL_texture("./up.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texLeft = SOIL_load_OGL_texture("./left.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texFront = SOIL_load_OGL_texture("./front.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texRight = SOIL_load_OGL_texture("./right.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texBack = SOIL_load_OGL_texture("./back.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texDown = SOIL_load_OGL_texture("./down.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
*/
	texUp = SOIL_load_OGL_texture("./opengllogo.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texLeft = SOIL_load_OGL_texture("./Android.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texFront = SOIL_load_OGL_texture("./Tux.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texRight = SOIL_load_OGL_texture("./UTArlington.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texBack = SOIL_load_OGL_texture("./Apple-logo.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	texDown = SOIL_load_OGL_texture("./UbuntuHUGE.PNG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, iFlags);
	
}


void drawFullCube(float fBoxSize, float fCornerRadius){

	int iXInc, iYInc, iZInc;
	int iCubeNumber;
	
	for(iXInc = 0; iXInc < 3; iXInc++)
		for(iYInc = 0; iYInc < 3; iYInc++)
			for(iZInc = 0; iZInc < 3; iZInc++){
				iCubeNumber = iXInc + 3*iYInc + 9*iZInc;
				float fTrans = fBoxSize + 0.01f;

				glPushMatrix();
//				glTranslatef(fTrans*iXInc, fTrans*iYInc, fTrans*iZInc); 
				glTranslatef(fBoxSize*iXInc, fBoxSize*iYInc, fBoxSize*iZInc); 
				drawCubie(fBoxSize, fCornerRadius, iXInc, iYInc, iZInc, 0);
//				drawCubie(fBoxSize, fCornerRadius, iXInc, iYInc, iZInc, 0);
				glPopMatrix();
			}


	return;
}

void drawPartialCube(float fBoxSize, float fCornerRadius, char cSegment, char cDimension){

	int iXInc, iYInc, iZInc;
	int iCubeNumber;

	for(iXInc = 0; iXInc < 3; iXInc++){
		for(iYInc = 0; iYInc < 3; iYInc++){
			for(iZInc = 0; iZInc < 3; iZInc++){
				iCubeNumber = iXInc + 3*iYInc + 9*iZInc;
				float fTrans = fBoxSize + 0.01f;

				char bDraw = 1;				

				if(cDimension & PARTIAL_DIMENSION_X)
					bDraw *= ((cSegment >> iXInc) & 1);

				if(cDimension & PARTIAL_DIMENSION_Y)
					bDraw *= ((cSegment >> iYInc) & 1);

				if(cDimension & PARTIAL_DIMENSION_Z)
					bDraw *= ((cSegment >> iZInc) & 1);

				if(bDraw){
					glPushMatrix();
	//				glTranslatef(fTrans*iXInc, fTrans*iYInc, fTrans*iZInc); 
					glTranslatef(fBoxSize*iXInc, fBoxSize*iYInc, fBoxSize*iZInc); 
					drawCubie(fBoxSize, fCornerRadius, iXInc, iYInc, iZInc, 1);
	//				drawCubie(fBoxSize, fCornerRadius, iXInc, iYInc, iZInc, 0);
					glPopMatrix();
				}
			}
		}
	}

	return;
}

void drawNumberedFace(float fBoxSize, float fCornerRadius, int iNum){

	int iPosFace = iNum / 9;
	int iPosNum = iNum % 9;
	int iTexFace = cRubikStateBuffer[0][iNum] / 9;
	int iTexNum = cRubikStateBuffer[0][iNum] % 9;
	int iTexRotat = cRubikStateBuffer[1][iNum];

	int iTexShiftX = 2 - iPosNum % 3;
	int iTexShiftY = 2 - (iPosNum / 3);
	GLint texUse;

#ifdef DEBUG 
	printf(" iPosFace = %d; iPosNum = %d; iTexShiftX = %d; iTexShiftY = %d;\n", iPosFace, iPosNum, iTexShiftX, iTexShiftY);

#endif
	switch(iTexFace){
		case 0: texUse = texUp; break;
		case 1: texUse = texLeft; break;
		case 2: texUse = texFront; break;
		case 3: texUse = texRight; break;
		case 4: texUse = texBack; break;
		case 5: texUse = texDown; break;
		default:;
	}

	glPushMatrix();

	switch(iPosFace){
		case 0: glTranslatef(fBoxSize*0.0f, fBoxSize*3.0f, fBoxSize*0.0f); glRotatef( 90.0f, 1.0f, 0.0f, 0.0f); break;
		case 1: glTranslatef(fBoxSize*3.0f, fBoxSize*0.0f, fBoxSize*0.0f); glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); break;
		case 2: glTranslatef(fBoxSize*0.0f, fBoxSize*0.0f, fBoxSize*0.0f); glRotatef(  0.0f, 0.0f, 1.0f, 0.0f); break;
		case 3: glTranslatef(fBoxSize*0.0f, fBoxSize*0.0f, fBoxSize*3.0f); glRotatef( 90.0f, 0.0f, 1.0f, 0.0f); break;
		case 4: glTranslatef(fBoxSize*3.0f, fBoxSize*0.0f, fBoxSize*3.0f); glRotatef(180.0f, 0.0f, 1.0f, 0.0f); break;
		case 5: glTranslatef(fBoxSize*0.0f, fBoxSize*0.0f, fBoxSize*3.0f); glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); break;
		default:;
	}

	glPushMatrix();
	glTranslatef(fBoxSize*((float)iTexShiftX), fBoxSize*((float)iTexShiftY), 0.0f);

	glPushMatrix();

	if(iTexRotat == 2 || iTexRotat == 3)
		glTranslatef(0.0f*fBoxSize, 1.0f*fBoxSize, 0.0f);
	if(iTexRotat == 1 || iTexRotat == 2)
		glTranslatef(1.0f*fBoxSize, 0.0f*fBoxSize, 0.0f);
	glRotatef(iTexRotat*90.0f, 0.0f, 0.0f, 1.0f);
	drawTexturedFace(fBoxSize, fCornerRadius, texUse, iTexNum);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	return;
}
