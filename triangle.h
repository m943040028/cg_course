#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object3d.h"
#include "vectors.h"

class Triangle : public Object3D {
public:
	Triangle(const Vec3f &v0, const Vec3f &v1,
		const Vec3f &v2, Material *material)
	{
		this->v0 = v0;
		this->v1 = v1;
		this->v2 = v2;
		this->material = material;
	};
	~Triangle() {};
	virtual bool intersect(const Ray &r, Hit &h, float tmin);

private:
	Vec3f v0;
	Vec3f v1;
	Vec3f v2;
};

#endif
