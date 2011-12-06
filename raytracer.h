#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

class Image;
class Shader;

void raytracer(Shader *shader, const char *input_file, Image &image);

#endif
