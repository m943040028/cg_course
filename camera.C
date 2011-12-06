
#include "vectors.h"
#include "camera.h"
#include "ray.h"
#include "floatpoint.h"

#include <assert.h>

Ray OrthographicCamera::generateRay(Vec2f point) {
	assert(point.x() < 1.0 && point.x() >= 0.0);
	assert(point.y() < 1.0 && point.y() >= 0.0);
	assert(f_unequal(point.x(), 1.0));
	assert(f_unequal(point.y(), 1.0));

	float scaler_x = point.x() - 0.5;
	float scaler_y = point.y() - 0.5;

	Vec3f origin = center + (up*size) * scaler_y +
		(horizontal*size) * scaler_x;

	Ray r(origin, direction);
	return r;
}

Ray PerspectiveCamera::generateRay(Vec2f point) {
	assert(point.x() < 1.0 && point.x() >= 0.0);
	assert(point.y() < 1.0 && point.y() >= 0.0);
	assert(f_unequal(point.x(), 1.0));
	assert(f_unequal(point.y(), 1.0));
	assert(angle != 0);

	Vec3f org(0.0, 0.0, 0.0);
	Vec3f dir;
	Vec3f target;

	// assume distance between origin and image plane is 1
	float hypotenuse = 1 / cos(angle/2);
	float image_plane_size = (hypotenuse * sin(angle/2)) * 2;
	float x_off, y_off;


	x_off = image_plane_size * (point.x() - 0.5);
	y_off = image_plane_size * (point.y() - 0.5);
	cout << x_off << "," << y_off << endl;

	// get the image plane origin
	target = center + direction;
	// add x offset
	target.Set(target.x()+x_off, target.y(), target.z());
	// add y offset
	target.Set(target.x(), target.y()+y_off, target.z());

	org = center;

	cout << target << endl;
	// get direction vector
	dir = target - center;
	dir.Normalize();
	Ray r(org, dir);
	cout << "ray: dir correspond to (" << point.x() << "," << point.y() << "), " << dir << endl;
	return r;
}
