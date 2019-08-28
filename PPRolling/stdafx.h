#pragma once

#define WIN32_LEAN_AND_MEAN //window
#define _USE_MATH_DEFINES
#define M_PI

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <float.h>

#include "AntTweakBar.h"

#include "CPoint3d.h"
#include "CMatrix.h"
#include "TimeTool.h"
#include "Color3D.h"

// OpenGL
#include "gl2ps.h"
#include "gl_screenshot.h"
#include "OpenGL.h"
#include "OpenGLWindow.h"
#include "OpenGLprimitive.h"

//glut library
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <gl\freeglut.h>

//main program
#include "OctVoxel.h"
#include "TetraCheckerBoard.h"
