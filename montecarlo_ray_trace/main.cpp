#include<glm/glm.hpp>
#include<glm/glm.hpp>
#include <omp.h>    // openmp多线程加速
#include<glm/vec3.hpp>
#include<iostream>
#include"shape/Shape.h"
#include"camera/DataFrame.h"
#include"camera/Camera.h"
#include"obj/Obj.h"
#include"scene/scene.h"
#include"test/Log.h"
#include "main.h"
#include<vector>
#include<iostream>
#include<stdio.h>
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace glm;
const glm::vec3 RED(1, 0.5, 0.5);


DataFrame* DF;
Obj* GOBJ;
Camera* GCamera;
Scene* GScene;
int main(void) {
	//GOBJ = new Obj();
	//GOBJ->loadFile("./scenes/bunny/bunny.obj");
	LOG("---------------------new main----------------------");
	GScene = new Scene(SCENE_NAME);
	system("pause");                        
	return 0;
}