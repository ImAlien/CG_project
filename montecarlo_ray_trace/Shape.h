#pragma once

#include<glm/vec3.hpp>
#include<glm/glm.hpp>
#include "IntersectResult.h"
#include"Ray.h"
class Shape {
public:
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
	Material material;  // ����
	Triangle() {}
	Triangle(glm::vec3 P1, glm::vec3 P2, glm::vec3 P3, glm::vec3 color)
	{
		p1 = P1, p2 = P2, p3 = P3;
		material.normalVector = glm::normalize(glm::cross(p2 - p1, p3 - p1));
		material.color = color;
	}
	// �������
	IntersectResult intersect(Ray ray);
};