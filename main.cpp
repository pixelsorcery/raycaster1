#include <iostream>
#include <memory>
#define __STDC_LIB_EXT1__
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

static constexpr int WIDTH = 1024;
static constexpr int HEIGHT = 768;

struct Vector3 { float x, y, z; };
struct Vector3i { int x, y, z; };

Vector3 sub(Vector3 a, Vector3 b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector3 add(Vector3 a, Vector3 b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

float dot(Vector3 a, Vector3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(Vector3 a, Vector3 b) {
	return { a.y * b.z - a.z * b.y, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y };
}

Vector3 mul(float a, Vector3 v) {
	return { a * v.x, a * v.y, a * v.z };
}

struct Matrix3x4 {
	Vector3 x, y, z, w;
};

Vector3 mul0(Vector3 v, Matrix3x4 m) {
	return add(add(mul(v.x, m.x), mul(v.y, m.y)), mul(v.z, m.z));
}

Vector3 mul1(Vector3 v, Matrix3x4 m) {
	return add(add(add(mul(v.x, m.x), mul(v.y, m.y)), mul(v.z, m.z)), m.w);
}

Vector3 verts[] = { {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f} };
static constexpr int NUM_VERTS = sizeof(verts) / sizeof(Vector3);

int main() {
	Vector3 v0 = verts[0];
	Vector3 v1 = verts[1];
	Vector3 v2 = verts[2];

	unique_ptr<Vector3i[]> target = std::make_unique<Vector3i[]>(WIDTH * HEIGHT);
	Vector3 vertsx[NUM_VERTS];

	Matrix3x4 modelToWorld = {
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f},
		{ 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, -5.0f}
	};

	// transform 
	for (int v = 0; v < NUM_VERTS; v++) {
		vertsx[v] = mul1(verts[v], modelToWorld);
	}

	Matrix3x4 worldToProj = {

	}

	// project
	for (int v = 0; v < NUM_VERTS; v++) {
		vertsx[v] = mul(verts[v])
	}

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			// calculate z values of all cross products between camera point -> triangle point and camera point -> pixel being shaded

			// if all z values are > 0 or all z values are < 0, output white, else output black
			target[y * HEIGHT + x] = Vector3i{ 0, 0, 0 };

			// optionally, calculate barycentric weights

			// calculate uv coords

			// sample texture map

			// output texture color
		}
	}

	stbi_write_png("output.png", WIDTH, HEIGHT, 3, target.get(), 0);

	return 0;
}