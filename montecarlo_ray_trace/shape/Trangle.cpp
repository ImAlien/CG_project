#include "Shape.h"

using namespace glm;
IntersectResult Triangle::intersect(Ray& ray) {
	IntersectResult res;

	vec3 S = ray.startPoint;        // �������
	vec3 d = ray.direction;         // ���߷���
	vec3 N = normalize(cross(p2 - p1, p3 - p1));    // ������
	if (dot(N, d) > 0.0f) N = -N;   // ��ȡ��ȷ�ķ�����

	// ������ߺ�������ƽ��
	if (fabs(dot(N, d)) < 0.00001f) return res;

	// ����
	float t = (dot(N, p1) - dot(S, N)) / dot(d, N);
	if (t < 0.0005f) return res;    // ����������ڹ��߱���

	// �������
	vec3 P = S + d * t;

	// �жϽ����Ƿ�����������
	vec3 c1 = cross(p2 - p1, P - p1);
	vec3 c2 = cross(p3 - p2, P - p2);
	vec3 c3 = cross(p1 - p3, P - p3);
	if (dot(c1, N) > 0 && dot(c2, N) > 0 && dot(c3, N) > 0) {
		res.distance = t;
		res.isIntersect = true;
		res.triangle = this;
		return res;
	}
	if (dot(c1, N) < 0 && dot(c2, N) < 0 && dot(c3, N) < 0) {
		res.distance = t;
		res.isIntersect = true;
		res.triangle = this;
		return res;
	}

	return res;
}