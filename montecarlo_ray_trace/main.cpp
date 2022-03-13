#include<glm/glm.hpp>
#include<glm/glm.hpp>
#include"svpng.inc"
#include <omp.h>    // openmp���̼߳���
#include<glm/vec3.hpp>
#include<iostream>
#include"Shape.h"
#include<vector>
#include<iostream>

using namespace std;
using namespace glm;
const glm::vec3 RED(1, 0.5, 0.5);


void test_rgb(void) {
	unsigned char rgb[256 * 256 * 3], *p = rgb;
	unsigned x, y;
	FILE *fp = fopen("rgb.png", "wb");
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			*p++ = (unsigned char)x;    /* R */
			*p++ = (unsigned char)y;    /* G */
			*p++ = 128;                 /* B */
		}
	svpng(fp, 256, 256, rgb, 0);
	fclose(fp);
}

void test_rgba(void) {
	unsigned char rgba[256 * 256 * 4], *p = rgba;
	unsigned x, y;
	FILE* fp = fopen("rgba.png", "wb");
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			*p++ = (unsigned char)x;                /* R */
			*p++ = (unsigned char)y;                /* G */
			*p++ = 128;                             /* B */
			*p++ = (unsigned char)((x + y) / 2);    /* A */
		}
	svpng(fp, 256, 256, rgba, 1);
	fclose(fp);
}

// ��� SRC �����е����ݵ�ͼ��
void imshow(double* SRC, int WIDTH, int HEIGHT)
{

	unsigned char* image = new unsigned char[WIDTH * HEIGHT * 3];// ͼ��buffer
	unsigned char* p = image;
	double* S = SRC;    // Դ����

	FILE* fp;
	fopen_s(&fp, "image.png", "wb");

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			*p++ = (unsigned char)clamp((*S++) * 255, 0.0, 255.0);  // R ͨ��
			*p++ = (unsigned char)clamp((*S++) * 255, 0.0, 255.0);  // G ͨ��
			*p++ = (unsigned char)clamp((*S++) * 255, 0.0, 255.0);  // B ͨ��
		}
	}

	svpng(fp, WIDTH, HEIGHT, image, 0);
}

// ���ؾ������ hit �Ľ��
IntersectResult shoot(vector<Shape*>& shapes, Ray ray)
{
	IntersectResult res, r;
	res.distance = 1145141919.810f; // inf

	// ��������ͼ�Σ����������
	for (auto& shape : shapes)
	{
		r = shape->intersect(ray);
		if (r.isIntersect && r.distance < res.distance) res = r;  // ��¼����������󽻽��
	}

	return res;
}
int main(void) {
	int WIDTH = 400, HEIGHT = 200, SCREEN_Z = 0;
	//double* image = new double[WIDTH * HEIGHT * 3];
	//memset(image, 0.0, sizeof(double) * WIDTH * HEIGHT * 3);
	//double* p = image;
	//for (int i = 0; i < HEIGHT; i++)
	//{
	//	for (int j = 0; j < WIDTH; j++)
	//	{
	//		// ��������תͶӰƽ������
	//		double x = 2.0 * double(j) / double(WIDTH) - 1.0;
	//		double y = 2.0 * double(HEIGHT - i) / double(HEIGHT) - 1.0;
	//		glm::vec3 EYE = glm::vec3(0, 0, 1);
	//		glm::vec3 coord = glm::vec3(x, y, SCREEN_Z);          // ����ͶӰƽ������
	//		glm::vec3 direction = glm::normalize(coord - EYE);    // �������Ͷ�䷽��

	//		glm::vec3 color = direction;

	//		*p = color.x; p++;  // R ͨ��
	//		*p = color.y; p++;  // G ͨ��
	//		*p = color.z; p++;  // B ͨ��
	//	}
	//}
	//imshow(image,WIDTH, HEIGHT);
	vector<Shape*> shapes;  // ��������ļ���
	shapes.push_back(new Triangle(glm::vec3(-0.5, -0.5, 0), glm::vec3(0.0, 0.5, 0), glm::vec3(0.5, -0.5, 0), RED));
	double* image = new double[WIDTH * HEIGHT * 3];
	memset(image, 0.0, sizeof(double) * WIDTH * HEIGHT * 3);
	double* p = image;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			// ��������תͶӰƽ������
			double x = 2.0 * double(j) / double(WIDTH) - 1.0;
			double y = 2.0 * double(HEIGHT - i) / double(HEIGHT) - 1.0;
			glm::vec3 EYE = glm::vec3(0, 0, 1);
			vec3 coord = vec3(x, y, SCREEN_Z);          // ����ͶӰƽ������
			vec3 direction = normalize(coord - EYE);    // �������Ͷ�䷽��

			// ���ɹ���
			Ray ray;
			ray.startPoint = coord;
			ray.direction = direction;

			// �ҽ��㲢����������ɫ
			IntersectResult res = shoot(shapes, ray);
			if (res.isIntersect) cout << i << j << endl;
			vec3 color = res.material.color;

			*p = color.x; p++;  // R ͨ��
			*p = color.y; p++;  // G ͨ��
			*p = color.z; p++;  // B ͨ��
		}

	}
	imshow(image, WIDTH, HEIGHT);
	system("pause");
	return 0;
}