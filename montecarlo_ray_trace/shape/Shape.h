#pragma once

#include<glm/vec3.hpp>
#include<glm/glm.hpp>
#include "../ray/IntersectResult.h"
#include"../ray/Ray.h"
#include"../material/Material.h"
#include <vector>
class Point {
public:
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 tex;
	Point() {};
};
class Shape {
public:
	std::vector<Point*> points;
	Material* material;
	Shape() {};
	virtual IntersectResult intersect(Ray ray) {
		return IntersectResult();
	}
};
// ������
class Triangle : public Shape
{
public:
	glm::vec3 p1, p2, p3;    // ������
	Triangle() {}
	Triangle(glm::vec3 P1, glm::vec3 P2, glm::vec3 P3)
	{
		p1 = P1, p2 = P2, p3 = P3;
	}
	// �������
	IntersectResult intersect(Ray ray);
};