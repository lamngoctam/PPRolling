#pragma once


#ifndef __OPENGLWINDOW0_H_
#define __OPENGLWINDOW0_H_


#include "stdafx.h"


void DisplayInit();
void DisplayPostprocessor();

void writefile(int format, int sort, int options, int nbcol, 
	char *filename, char *extension, int winid, OpenGL GLSettings);
void writebmpfile(char *filename, char *extension, int winid);
void OpenGLReshape(int width, int height);

void OpenGLIdle();
void OpenGLInitialize(int WindowID, OpenGL GLSettings, int InitPosiX, 
	int InitPosiY, int WindowWidth, int WindowHeight, const char* WindowName);

void OpenGLPostprocessor(OpenGL GLSettings);
void PickUpInit(int x, int y);
void PickUpPostprocessor(void);
int SelectHits(GLuint hits, GLuint* buf, int hit_name[2]);
double ReturnDepth(int x, int y);

void DrawBoundingbox(CVector3d MaxPt, CVector3d MinPt, int colorID);
void ConclusiveAxis(void);



#endif