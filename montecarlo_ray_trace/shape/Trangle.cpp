#include "Shape.h"

using namespace glm;
//IntersectResult Triangle::intersect(Ray ray) {
//	IntersectResult res;
//
//	vec3 S = ray.startPoint;        // �������
//	vec3 d = ray.direction;         // ���߷���
//	vec3 N = material.normalVector;       // ������
//	if (dot(N, d) > 0.0f) N = -N;   // ��ȡ��ȷ�ķ�����
//
//	// ������ߺ�������ƽ��
//	if (fabs(dot(N, d)) < 0.00001f) return res;
//
//	// ����
//	float t = (dot(N, p1) - dot(S, N)) / dot(d, N);
//	if (t < 0.0005f) return res;    // ������������������
//
//	// �������
//	vec3 P = S + d * t;
//
//	//// �жϽ����Ƿ�����������
//	//vec3 c1 = cross(p2 - p1, P - p1);
//	//vec3 c2 = cross(p3 - p2, P - p2);
//	//vec3 c3 = cross(p1 - p3, P - p3);
//	//vec3 n = material.normalVector;   // ��Ҫ "ԭ��������" ���ж�
//	//if (dot(c1, n) < 0 || dot(c2, n) < 0 || dot(c3, n) < 0) return res;
//
//	// װ��ؽ��
//	res.isIntersect = true;
//	res.distance = t;
//	res.intersectPoint = P;
//	res.material = material;
//	res.material.normalVector = N;    // Ҫ������ȷ�ķ���
//	return res;
//}