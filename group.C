#include <float.h>
#include "group.h"
#include "hit.h"

bool Group::intersect(const Ray &r, Hit &h, float tmin)
{
	int i, n = 0;
	float t = FLT_MAX;
	Hit tmph = h;

	for (i = 0;i < nobjs; i++)
		if (objs[i]->intersect(r, tmph, tmin)) {
			cout << __FILE__ << " n: " << n <<" t: "<< tmph.getT() << endl;
			n++;
			if (tmph.getT() < t) {
				t = tmph.getT();
				cout << __FILE__ << " update => t: "<< t << endl;
				h.set(t, tmph.getMaterial(), tmph.getNormal(), r);
			}
		}

	if (!n)
		return false;
	return true;
}

void Group::addObject(int index, Object3D *obj)
{
	objs[index] = obj;
}
