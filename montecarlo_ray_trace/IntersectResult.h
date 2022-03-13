#pragma once
#include<glm/vec3.hpp>
#include"Material.h"
class IntersectResult {
public:
	bool isIntersect = false;             // �ཻ
	double distance = 0.0f;         // �뽻��ľ���
	glm::vec3 intersectPoint = glm::vec3(0, 0, 0);  // ���߽���
	Material material;              // ����ı������
	IntersectResult() {};
};
