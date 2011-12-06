#ifndef _OBJECT_3D_H_
#define _OBJECT_3D_H_

#include "material.h"

class Ray;
class Hit;

class Object3D {

public:
	Object3D() {};
	~Object3D() {};
	virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;

protected:
	Material *material;
};

#endif
