#include "shader.h"

class DiffuseShader : public Shader {

public:
	DiffuseShader() {};
	~DiffuseShader() {};
	void shading(Vec3f &output_color,
		     Hit *hit_point, SceneParser *scene);
private:
};
