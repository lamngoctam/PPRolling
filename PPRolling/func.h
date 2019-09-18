#pragma once

#include "stdafx.h"

//global variables
OctVoxel cube;
//OctVoxel* label;

OctVoxel *newCube;
int cubeNum(0);

//all main function
int CubePathPlanning(int argc, char* argv[]);

int TetrahedronPathPlanning(int argc, char* argv[]);

//openGl function references
void RunOpenGL(int argc, char *argv[]);
void RunOpenGL1(int argc, char *argv[]);