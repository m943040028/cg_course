#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "object3d.h"
#include "matrix.h"

class Transform : public Object3D {
public:
	Transform(Matrix &matrix, Object3D *object)
	{
		this->matrix = matrix;
		this->object = object;
	};
	~Transform() {};
	virtual bool intersect(const Ray &r, Hit &h, float tmin);

private:
	Matrix matrix;
	Object3D *object;
};

#endif
