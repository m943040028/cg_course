#include "ray.h"
#include "hit.h"
#include "vectors.h"
#include "sphere.h"
#include "group.h"
#include "light.h"
#include "scene_parser.h"
#include "image.h"
#include "camera.h"
#include "floatpoint.h"
#include "raytracer.h"
#include "shader.h"

#include <float.h>

// RayTracer implementation
//
// @ shader:		shader object
// @ scene_file:	scene_file path
// @ input image file:	Image object
void raytracer(Shader *shader, const char *scene_file, Image &img)
{

	int width, height;
	float coord_x, coord_y;

	SceneParser scene(scene_file);
	Camera *c = scene.getCamera();
	Group *g = scene.getGroup();

	img.SetAllPixels(scene.getBackgroundColor());
	width = img.Width();
	height = img.Height();

	// loops over the pixels in the image plane, 
	// generates a ray using OrthographicCamera class,
	// intersects it with the high-level Group that
	// stores the objects of the scene,
	// and writes the color of the closest intersected object. 
	float step_x = 1.0f / width;
	float step_y = 1.0f / height;

	for (coord_x = 0.0f; f_unequal(coord_x, 1.0f); coord_x += step_x) {
		for (coord_y = 0.0f; f_unequal(coord_y, 1.0f); coord_y += step_y)
		{
			Vec2f p(coord_x, coord_y);
			Vec3f n(0.0f, 0.0f, 0.0f);
			Hit hit_point(FLT_MAX, NULL, n);

			// generate a Ray from camera
			Ray ray = c->generateRay(p);

			// intersect it with group object
			if (g->intersect(ray, hit_point, c->getTMin())) {
				assert(hit_point.getMaterial());
				Vec3f pixel_color;

				// shading the pixel
				shader->shading(pixel_color, &hit_point, &scene);

				img.SetPixel((int)nearbyint(coord_x*width),
					(int)nearbyint(coord_y*height), pixel_color);
			}
		}
	}
}
