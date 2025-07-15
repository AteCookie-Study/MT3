#pragma once
#include"Vector3.h"
#include"Novice.h"
#include"Matrix4x4.h"

struct Plane {
	Vector3 normal;
	float distance;
};

struct Line {
	Vector3 origin;
	Vector3 diff;
};

struct  Ray {
	Vector3 origin; 
	Vector3 diff; 
};

struct  Segment {
	Vector3 origin; 
	Vector3 diff; 
};

struct Sphere {
	Vector3 center;
	float radius;
};

struct Triangle {
	Vector3 vertices[3];
};