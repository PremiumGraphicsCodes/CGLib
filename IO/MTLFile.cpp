#define _CRT_SECURE_NO_DEPRECATE
#include "stdafx.h"
#include "MTLFile.h"

#include "Helper.h"

#include <vector>

#include <cassert>

#include <string>

#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Material.h"


using namespace Crystal::Graphics;
using namespace Crystal::IO;

OBJMaterial::OBJMaterial()
{
	ambient = Graphics::ColorRGBA<float>(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = Graphics::ColorRGBA<float>(0.0f, 0.0f, 0.0f, 0.0f);
	specular = Graphics::ColorRGBA<float>(0.0f, 0.0f, 0.0f, 0.0f);
	float specularExponent = 0.0f;
	float transparent = 0.0f;
	float opticalDensity = 0.0f;

	illumination = Illumination::COLOR_ON_AND_AMBIENT_OFF;
}

bool OBJMaterial::read(std::istream& stream)
{
	std::string header;
	this->name = Helper::read< std::string >(stream);
	stream >> header;

	while (!stream.eof()) {
		if (header.front() == '#') {
			std::getline(stream, header);
			//comment += header;
		}
		else if (header == "newmtl") {
			return true;
		}
		else if (header == "Ka") {
			this->ambient = Helper::readColorRGB(stream);
		}
		else if (header == "Kd") {
			this->diffuse = Helper::readColorRGB(stream);
		}
		else if (header == "Ks") {
			this->specular = Helper::readColorRGB(stream);
		}
		else if (header == "Ns") {
			this->specularExponent = Helper::read< float >(stream);
		}
		else if (header == "d" || header == "Tr") {
			this->transparent = Helper::read<float>(stream);
		}
		else if (header == "map_Ka") {
			this->ambientTexture = Helper::read< std::string >(stream);
		}
		else if (header == "map_Kd") {
			std::string str = Helper::read< std::string >(stream);
			/*
			if (str == "-o") {
				Helper::readVector(stream);
				str = Helper::read< std::string >(stream);
			}
			if (str == "-s") {
				Helper::readVector(stream);
				str = Helper::read< std::string >(stream);
			}
			*/
			this->diffuseTexture = str;
		}
		else if (header == "map_Ks") {
			this->shininessTexture = Helper::read< std::string >(stream);
		}
		else if (header == "map_Ns") {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if (header == "map_d") {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if (header == "map_bump" || header == "bump") {
			this->bumpTexture = Helper::read< std::string >(stream);
		}
		else if (header == "illum") {
			this->illumination = OBJMaterial::Illumination( Helper::read< int >(stream) );
		}
		else if (header == "Ni") {
			this->opticalDensity = Helper::read<float>(stream);
		}

		stream >> header;
	}
	return true;
}


bool OBJMaterial::write(std::ostream& stream) const
{
	stream << "newmtl " << name << std::endl;

	const ColorRGBA<float>& ambient = this->ambient;
	char s[256];
	sprintf(s, "Ka %.4lf %.4lf %.4lf", ambient.getRed(), ambient.getGreen(), ambient.getBlue());
	stream << s << std::endl;

	const ColorRGBA<float>& diffuse = this->getDiffuse();
	sprintf(s, "Kd %.4lf %.4lf %.4lf", diffuse.getRed(), diffuse.getGreen(), diffuse.getBlue());
	stream << s << std::endl;

	const ColorRGBA<float>& specular = this->getSpecular();
	sprintf(s, "Ks %.4lf %.4lf %.4lf", specular.getRed(), specular.getGreen(), specular.getBlue());
	stream << s << std::endl;

	const float shininess = this->getSpecularExponent();
	sprintf(s, "Ns %.4lf", shininess);
	stream << s << std::endl;

	const float tr = this->getTransparent();
	sprintf(s, "Tr %.4lf", tr);
	stream << s << std::endl;

	return true;
}

bool MTLFile::read(const std::string& filename)
{
	std::ifstream stream;
	stream.open(filename.c_str());

	if (!stream.is_open()) {
		return false;
	}

	return read(stream);
}

bool MTLFile::read(std::istream& stream)
{
	std::string str;
	
	std::string comment;

	std::string header= Helper::read< std::string >(stream);

	while( !stream.eof() ) {
		if( header.front() == '#' ) {
			std::getline( stream, header );
		}
		else if( header == "newmtl" ) {
			OBJMaterial mtl;
			mtl.read(stream);
			materials.push_back( mtl );
		}
		else {
			stream >> header;
		}
	}

	return true;
}

#include "File.h"

Material OBJMaterial::toMaterial(const std::string& directory) const
{
	Material m;
	m.setAmbient(this->ambient);
	m.setDiffuse(this->diffuse);
	m.setSpecular(this->specular);
	m.setShininess(this->specularExponent);

	Texture texture;
	if (!this->diffuseTexture.empty()) {
		File file(directory + this->diffuseTexture);
		Imagef* texImage = new Imagef();
		texImage->read(file.getFullPath());
		texture.setDiffuse(texImage);
	}
	m.setTexture(texture);
	//t.setDirectory(directory);

	return m;
}

bool MTLFile::write(const std::string& filename)
{
	std::ofstream stream(filename.c_str());

	if (!stream.is_open()) {
		return false;
	}

	return write(stream);
}

bool MTLFile::write(std::ostream& stream)
{
	for (const auto& m : materials) {
		m.write(stream);
	}
	return true;
}
