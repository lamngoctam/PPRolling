#include "func.h"

namespace apple {
	void print(const std::string& text) {
		std::cout << text << std::endl;
	}
}

namespace orange {
	void print(const char* text) {
		std::string temp = text;
		std::reverse(temp.begin(), temp.end());
		std::cout << temp << std::endl;
	}
}

using namespace apple;
using namespace orange;


int main(int argc, char *argv[]) {

	//apple::print("hello_world");
	//orange::print("hello_world");



	//for cube
	CubePathPlanning(argc, argv);
	//std::cout << "end of cube path planning" << std::endl;


	//for triangle
	//TetrahedronPathPlanning(argc, argv);
	//std::cout << "end of Tetrahedron Path Planning" << std::endl;




	return 0;
	//std::cin.get();
}


//
//void DrawCubeRolling() {
//
//	OctVoxel cb = newCube[numberCube];
//
//	//only for cube rolling right-up or left-up
//
//	for (int a = 0; a < cubeNum; a++)
//	{
//		if (newCube[a].getSelected())
//		{
//			glPushMatrix();
//			glLineWidth(1.9f);
//			std::cout << "+++++++++++    right   ++++++++++++ " << std::endl;
//			if (newCube[a].getRightRolling()) {
//
//				//for Right
//				glTranslatef(cb.getCoordX() - 0.5, cb.getCoordY() - 0.5, 0.0);
//				glRotatef(angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
//				glTranslatef(-0.5, 0.5, 0.5);//const	
//				glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
//				Draw3DcoordArrowGL(angleRotation, cb.getCoordX() - 0.5, cb.getCoordY() - 0.5, 0.0,
//					cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ(), 0.02);
//			}
//			else {
//				//rolling up
//				std::cout << "------------     up     -----------" << std::endl;
//
//				glPushMatrix();
//				glTranslatef(cb.getCoordX() - 1.5, cb.getCoordY() - 0.5, 0.0);
//				glRotatef(-angleRotation, cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ());
//				glTranslatef(1.5, -0.5, 0.5); //const
//
//				//draw cube
//				glColor3f(0.5, 0.5, 1.0); glutSolidCube(1);
//				Draw3DcoordArrowGL(angleRotation, cb.getCoordX() - 0.5, cb.getCoordY() - 0.5, 0.0,
//					cb.getDirectionX(), cb.getDirectionY(), cb.getDirectionZ(), 0.02);
//			}
//
//			glPopMatrix();
//		}
//
//	}
//	if (angleRotation >= 90)
//	{
//		newCube[numberCube].setSelected(false); //cb will stop
//		numberCube += 1;						//move to next cb
//
//		numberCube %= cubeNum;
//		newCube[numberCube].setSelected(true);
//		angleRotation = 0;
//
//	}
//
//}
