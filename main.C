#include <stdio.h>
#include <string.h>

#include "image.h"
#include "raytracer.h"
#include "diffuse.h"
#include "normal.h"

int
main(int argc, char **argv)
{
	char *input_file = NULL;
	int width = 100;
	int height = 100;
	char *output_file = NULL;
	float depth_min = 0;
	float depth_max = 1;
	char *depth_file = NULL;
	char *normal_file = NULL;

	// sample command line:
	// raytracer -input scene1_1.txt -size 200 200 -output output1_1.tga -depth 9 10 depth1_1.tga

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i],"-input")) {
			i++; assert (i < argc); 
			input_file = argv[i];
		} else if (!strcmp(argv[i],"-size")) {
			i++; assert (i < argc); 
			width = atoi(argv[i]);
			i++; assert (i < argc); 
			height = atoi(argv[i]);
		} else if (!strcmp(argv[i],"-output")) {
			i++; assert (i < argc); 
			output_file = argv[i];
		} else if (!strcmp(argv[i],"-depth")) {
			i++; assert (i < argc); 
			depth_min = atof(argv[i]);
			i++; assert (i < argc); 
			depth_max = atof(argv[i]);
			i++; assert (i < argc); 
			depth_file = argv[i];
		} else if (!strcmp(argv[i],"-normals")) {
			i++; assert (i < argc); 
			normal_file = argv[i];
		} else {
			printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
			assert(0);
		}
	}

	Image image(width, height);
	if (output_file) {
		DiffuseShader diffuse;
		raytracer(&diffuse, input_file, image);
		image.SaveTGA(output_file);
	}
	if (normal_file) {
		NormalShader normal;
		raytracer(&normal, input_file, image);
		image.SaveTGA(normal_file);
	}
}
