#include "triangle.h"
#include "vectors.h"
#include "matrix.h"
#include "ray.h"
#include "hit.h"
#include "floatpoint.h"

// Use barycentric coordinates
//
// barycentric definition of a triangle:
//
//   P(alpha, beta, gamma) = a*alpha + b*beta + c*gamma
//       where 
//   (alpha + beta + gamma) = 1, and 
//   0 < alpha < 1 & 0 < beta < 1 & 0 < gamma < 1
//
//   alpha = 1 - beta - gamma, thus we can rewrite the formula
//   P(beta, gamma) = (1 - beta - gamma)*a + beta*b + gamma*c
//                  = a + beta*(b-a) + gamma*(c-a)
//
// Set ray equation equation to barycentric equation
//   Ro + t*Rd = a + beta*(b-a) + gamma*(c-a)
//
// Rewrite to matrix form:
//
//  | (ax - bx)  (ax - cx)  Rdx | | beta  |   | ax - Rox |
//  | (ay - by)  (ay - cy)  Rdy | | gamma | = | ay - Roy |
//  | (az - bz)  (az - cz)  Rdz | | t     |   | az - Roz |
//
// Using Cramer’s Rule, we can solve beta, gamma, and t
//
// Intersection if beta + gamma < 1 and beta > 0 and gamma > 0
//
bool Triangle::intersect(const Ray &r, Hit &h, float tmin)
{
	Vec3f Rd = r.getDirection();
	Vec3f Ro = r.getOrigin();

	float t, beta, gamma;
	float matrix_A_array[] = {
		(v0.x() - v1.x()), (v0.x() - v2.x()), Rd.x(), 0,
		(v0.y() - v1.y()), (v0.y() - v2.y()), Rd.y(), 0,
		(v0.z() - v1.z()), (v0.z() - v2.z()), Rd.z(), 0,
	};
	float matrix_A1_array[] = {
		(v0.x() - Ro.x()), (v0.x() - v2.x()), Rd.x(), 0,
		(v0.y() - Ro.y()), (v0.y() - v2.y()), Rd.y(), 0,
		(v0.z() - Ro.z()), (v0.z() - v2.z()), Rd.z(), 0,
	};
	float matrix_A2_array[] = {
		(v0.x() - v1.x()), (v0.x() - Ro.x()), Rd.x(), 0,
		(v0.y() - v1.y()), (v0.y() - Ro.y()), Rd.y(), 0,
		(v0.z() - v1.z()), (v0.z() - Ro.z()), Rd.z(), 0,
	};
	float matrix_A3_array[] = {
		(v0.x() - v1.x()), (v0.x() - v2.x()), (v0.x() - Ro.x()), 0,
		(v0.y() - v1.y()), (v0.y() - v2.y()), (v0.y() - Ro.y()), 0,
		(v0.z() - v1.z()), (v0.z() - v2.z()), (v0.z() - Ro.z()), 0,
		0, 0, 0, 0
	};

	Matrix A(matrix_A_array);
	Matrix A1(matrix_A1_array);
	Matrix A2(matrix_A2_array);
	Matrix A3(matrix_A3_array);

	// By Cramer's Rule, t = |A3|/|A|
	t = A3.det3() / A.det3();
	if (t < tmin)
		return false;

	beta = A1.det3() / A.det3();
	gamma = A2.det3() / A.det3();

	if (beta + gamma < 1 && beta > 0 && gamma > 0) {
		// get Normal
		Vec3f N, E1, E2;
		E1 = v0 - v1;
		E2 = v1 - v2;
		N = E1.Cross3(E2);
#if 0
		if (N.Dot3(Rd) > 0)
			N.Negate();
#endif
		h.set(t, material, N, r);
		return true;
	} else
		return false;
}
