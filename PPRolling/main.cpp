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

