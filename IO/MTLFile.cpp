#define _CRT_SECURE_NO_DEPRECATE

#include "MTLFile.h"

#include "Helper.h"

#include <vector>

#include <cassert>

#include <string>

#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Material.h"


using namespace Crystal::Graphics;
using namespace Crystal::IO;

void MTLTextureOption::setDefault()
{
	blendu = true;
	blendv = true;
	boost = 1.0f; // TODO.
	baseValue = 0.0f;
	gainValue = 1.0f;
	origin = Math::Vector3d<float>::Zero();
	scale = Math::Vector3d<float>(1.0f, 1.0f, 1.0f);
	turblence = Math::Vector3d<float>::Zero();
	imfchan = "l";
}

MTLFile MTLFileReader::read(const std::string& filename)
{
	std::ifstream stream;

	stream.open(filename.c_str());

	assert(stream.is_open());

	return read(stream);
}

MTLFile MTLFileReader::read(std::istream& stream)
{
	std::vector<MTL> mtls;
	std::string str;
	
	std::string comment;

	//Material* material = nullptr;

	std::string header= Helper::read< std::string >(stream);

	while( !stream.eof() ) {
		if( header.front() == '#' ) {
			std::getline( stream, header );
			//comment += header;
		}
		else if( header == "newmtl" ) {
			const std::string& materialName = Helper::read< std::string >(stream);
			
			MTL mtl;
			mtl.setName( materialName );
			mtls.push_back( mtl );
		}
		else if( header == "Ka" ) {
			mtls.back().setAmbient( Helper::readColorRGB(stream) );

		}
		else if( header == "Kd" ) {
			mtls.back().setDiffuse( Helper::readColorRGB(stream) );
		}
		else if( header == "Ks" ) {
			mtls.back().setSpecular( Helper::readColorRGB(stream) );
		}
		else if( header == "Ns") {
			const float ns = Helper::read< float >( stream );
			mtls.back().setSpecularExponent(ns);
		}
		else if (header == "d" || header == "Tr") {
			const float d = Helper::read<float>(stream);
			mtls.back().setTransparent(d);
		}
		else if( header == "map_Ka" ) {
			mtls.back().setAmbientTextureName( Helper::read< std::string >(stream) );
		}
		else if( header == "map_Kd" ) {
			str = Helper::read< std::string >(stream);
			if( str == "-o" ) {
				Helper::readVector(stream);
				str = Helper::read< std::string >(stream);
			}
			if( str == "-s" ) {
				Helper::readVector(stream);
				str = Helper::read< std::string >(stream);
			}
			mtls.back().setDiffuseTextureName( str );
		}
		else if( header == "map_Ks" ) {
			const std::string& filename = Helper::read< std::string >(stream);
			mtls.back().setShininessTextureName( filename );
		}
		else if( header == "map_Ns" ) {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if( header == "map_d" ) {
			const std::string& filename = Helper::read< std::string >(stream);
		}
		else if ( header == "map_bump" || header == "bump" ) {
			mtls.back().setBumpTextureName( Helper::read< std::string >(stream) );
		}
		else if (header == "illum") {
			const int i = Helper::read< int >(stream);
			mtls.back().setIllumination( MTL::Illumination(i));
		}
		else if (header == "Ni") {
			const float d = Helper::read<float>(stream);
			mtls.back().setOpticalDensity( d );
		}

		stream >> header;
	}

	MTLFile file;
	file.mtls = mtls;
	return file;
}



MTLTextureOption MTLFile::getTextureOptions(const std::string& str)
{
	std::stringstream stream(str);
	MTLTextureOption options;
	std::string nextStr = Helper::readNextString(stream);
	while (!nextStr.empty() && nextStr.front() == '-') {
		std::string str = Helper::read<std::string>(stream);
		if (str == "-blendu") {
			str = Helper::read<std::string>(stream);
			options.setBlendU( MTLFile::readOnOff(str) );
		}
		else if (str == "-blendv") {
			str = Helper::read<std::string>(stream);
			options.setBlendV( MTLFile::readOnOff(str) );
		}
		else if (str == "-boost") {
			options.setBoost( Helper::read<float>(stream) );
		}
		else if (str == "-mm") {
			options.setBaseValue( Helper::read<float>(stream) );
			options.setGainValue( Helper::read<float>(stream) );
		}
		else if (str == "-o") {
			options.setOrigin( Helper::readVector(stream) );
		}
		else if (str == "-s") {
			options.setScale( Helper::readVector(stream) );
		}
		else if (str == "-t") {
			options.setTurblence( Helper::readVector(stream) );
		}
		else if (str == "-texres") {
			options.setResolution( Helper::read<int>(stream) );
		}
		else if (str == "-clamp") {
			str = Helper::read<std::string>(stream);
			options.setClamp( MTLFile::readOnOff(str) );
		}
		else if (str == "-bm") {
			options.setBumpMultiplier( Helper::read<float>(stream) );
		}
		else if (str == "-imfchan") {
			const std::string& c = Helper::read<std::string>(stream);
			//r | g | b | m | l | z
			//assert(c == 'r' || c == 'g' || c == 'b' || c == 'm' || c == 'l' || c == 'z');
			options.setImfChan( c );
		}
		else if (str == "-type") {
			options.setType( Helper::read<std::string>(stream) );
		}
		nextStr = Helper::readNextString(stream);
	}
	return options;
}

std::vector< std::string > MTLFile::writeTextureOptions(std::ostream& stream, MTLTextureOption& option)
{
	std::vector< std::string > strs;
	{
		std::string str;
		str += "-blendu ";
		str += (option.getBlendU() ? "on" : "off");
		strs.push_back(str);
	}

	{
		std::string str;
		str += "-blendv ";
		str += (option.getBlendV() ? "on" : "off");
		strs.push_back(str);
	}

	for (const std::string& str : strs) {
		stream << str << std::endl;
	}

	return strs;
}


bool MTLFileWriter::save(const std::string& filename, const Material& m)
{
	std::ofstream stream(filename.c_str());

	if (!stream.is_open()) {
		return false;
	}

	return save(stream, m);
}

bool MTLFileWriter::save(std::ostream& stream, const Material& m)
{

	//stream << "# Exported from CGStudio" << std::endl;

	//strs.push_back( "newmtl " + m->getName());

	const ColorRGBA<float>& ambient = m.getAmbient();
	char s[256];
	sprintf(s, "Ka %.4lf %.4lf %.4lf", ambient.getRed(), ambient.getGreen(), ambient.getBlue());
	strs.push_back(s);

	const ColorRGBA<float>& diffuse = m.getDiffuse();
	sprintf(s, "Kd %.4lf %.4lf %.4lf", diffuse.getRed(), diffuse.getGreen(), diffuse.getBlue());
	strs.push_back(s);

	const ColorRGBA<float>& specular = m.getSpecular();
	sprintf(s, "Ks %.4lf %.4lf %.4lf", specular.getRed(), specular.getGreen(), specular.getBlue());
	strs.push_back(s);

	const float shininess = m.getShininess();
	sprintf(s, "Ns %.4lf", shininess);
	strs.push_back(s);

	const float tr = m.getTransparent();
	sprintf(s, "Tr %.4lf", tr);
	strs.push_back(s);

	//for (const Material* m : file.getMaterials()) {
		//	stream << std::endl;

		//	stream << "newmtl " << m->name << std::endl;

		//	const ColorRGBA<float>& ambient = m->getAmbient();
		//	stream << "Ka " << ambient.getRed() << " " << ambient.getGreen() << " " << ambient.getBlue() << std::endl;

		//	const ColorRGBA<float>& diffuse = m->getDiffuse();
		//	stream << "Kd " << diffuse.getRed() << " " << diffuse.getGreen() << " " << diffuse.getBlue() << std::endl;

		//	const ColorRGBA<float>& specular = m->getSpecular();
		//	stream << "Ks " << specular.getRed() << " " << specular.getGreen() << " " << specular.getBlue() << std::endl;

		//	//stream << "Ns " << m->shininess << std::endl;

		//	/*
		//	const Texture& texture = m->texture;
		//	if( !texture.getAmbientFileName().empty() ) {
		//		stream << "map_Ka " << texture.getAmbientFileName() << std::endl;
		//	}
		//	if( !texture.getDiffuseFileName().empty() ) {
		//		stream << "map_Kd " << texture.getDiffuseFileName() << std::endl;
		//	}
		//	if( !texture.getSpecularFileName().empty() ) {
		//		stream << "map_Ks " << texture.getSpecularFileName() << std::endl;
		//	}
		//	*/
		//}


	for (const std::string& str : strs) {
		stream << str << std::endl;
	}
	return true;
}