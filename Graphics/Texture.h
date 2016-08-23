#ifndef __CRYSTAL_GRAPHICS_TEXTURE_H__
#define __CRYSTAL_GRAPHICS_TEXTURE_H__

namespace Crystal {
	namespace Graphics {
		class Imagef;

class Texture
{
public:
	Texture();

	void setAmbient(Imagef* ambient) { this->ambient = ambient; }

	void setSpecular(Imagef* specular) { this->specular = specular; }

	void setDiffuse(Imagef* diffuse) { this->diffuse = diffuse; }

	void setBump(Imagef* bump) { this->bump = bump; }

	Imagef* getAmbient() { return ambient; }

	Imagef* getSpecular() { return specular; }

	Imagef* getDiffuse() { return diffuse; }

	Imagef* getBump() { return bump; }

private:
	Imagef* ambient;
	Imagef* specular;
	Imagef* diffuse;
	Imagef* bump;
};

	}
}

#endif