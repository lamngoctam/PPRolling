#pragma once

#include "stdafx.h"

//global variables
OctVoxel cube;
OctVoxel* label;

//all main function
int CubePathPlanning(int argc, char* argv[]);

int TetrahedronPathPlanning(int argc, char* argv[]);

//openGl function references
void RunOpenGL(int argc, char *argv[]);