#pragma once

#include <vector>
#include <string>
#include "../shape/Shape.h"
class Obj {
public:
	std::vector<Shape*> faces;
	int nface = 0, nvertex = 0;
	Obj() {}
	Obj(std::string filename) {
		loadFile(filename);
		createTable();
	}
	void loadFile(std::string filename);//���س�faces
	void loadFile(std::string filepath, std::string filename);
	void createTable();
};