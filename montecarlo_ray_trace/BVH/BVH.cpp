
#include"BVH.h"
#include<glm/glm.hpp>
#include<limits.h>
#include<iostream>
#include"../test/Log.h"
using namespace std;
using namespace glm;

BVH::BVH(vector<BoundingBox>& BBs) {
	LOG("��ʼ����BVH");
	root = build(BBs, 0, BBs.size() - 1);
	cout << root->BB.aa.x << root->BB.bb.x; 
	LOG("BVH�������");
}

int CNT = 0;
BVHnode* BVH::build(vector<BoundingBox>& BBs, int l, int r) {
	if (l > r) return nullptr;

	BVHnode* node = new BVHnode();
	if (l == r) {
		node->isLeaf = true;
		node->BB = BBs[l];
		return node;
	}
	node->BB.aa = vec3(100, 100, 100);
	node->BB.bb = vec3(-100, -100, -100);
	// ���� AABB
	for (int i = l; i <= r; i++) {
		
		node->BB.aa.x = glm::min(node->BB.aa.x, BBs[i].aa.x);
		node->BB.aa.y = glm::min(node->BB.aa.y, BBs[i].aa.y);
		node->BB.aa.z = glm::min(node->BB.aa.z, BBs[i].aa.z);

		node->BB.bb.x = glm::max(node->BB.bb.x, BBs[i].bb.x);
		node->BB.bb.y = glm::max(node->BB.bb.y, BBs[i].bb.y);
		node->BB.bb.z = glm::max(node->BB.bb.z, BBs[i].bb.z);
		
	}

	// �ݹ齨��
	float lenx = node->BB.bb.x - node->BB.aa.x;
	float leny = node->BB.bb.y - node->BB.aa.y;
	float lenz = node->BB.bb.z - node->BB.aa.z;
	// �� x ����
	if (lenx >= leny && lenx >= lenz)
		std::sort(BBs.begin() + l, BBs.begin() + r + 1, cmpBBx);
	// �� y ����
	if (leny >= lenx && leny >= lenz)
		std::sort(BBs.begin() + l, BBs.begin() + r + 1, cmpBBy);
	// �� z ����
	if (lenz >= lenx && lenz >= leny)
		std::sort(BBs.begin() + l, BBs.begin() + r + 1, cmpBBz);

	// �ݹ�
	int mid = (l + r) / 2;
	node->left = build(BBs, l, mid);
	node->right = build(BBs, mid + 1, r);

	return node;
}

IntersectResult BVH::intersectBVH(Ray& ray) {
	return intersectBVHnode(root, ray, INF);
}
IntersectResult BVH::intersectBVHnode(BVHnode* u, Ray& ray,float tmin) {
	IntersectResult res;
	if (u == nullptr) return res;
	if (u->isLeaf) return u->BB.source->intersect(ray);
	float tcur = u->BB.intersectBB(ray);
	if (tcur == -1 || tcur > tmin) return res;
	IntersectResult res_left = intersectBVHnode(u->left, ray, tmin);
	tmin = std::min(tmin, res_left.distance);
	IntersectResult res_right = intersectBVHnode(u->right, ray,tmin);
	tmin = std::min(tmin, res_right.distance);
	if (res_left.isIntersect) {
		res.isIntersect = true;
		res.distance = std::min(res.distance, res_left.distance);
		res.triangle = res_left.triangle;
	}
	if (res_right.isIntersect) {
		res.isIntersect = true;
		if (res.distance > res_right.distance) {
			res.distance = res_right.distance;
			res.triangle = res_right.triangle;
		}
	}
	if (res.isIntersect && res.triangle == nullptr) {
		LOG("ERROR : intersect but no intersectionshape");
		exit(1);
	}
	return res;
}