#include "CGBFile.h"

#include "../Graphics/ImageRGBA.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace tinyxml2;

using GeomType = float;
using ValueType = float;

namespace {
	std::vector<ImageRGBA<unsigned char>> toImageRGBAs(const Volume3d<float, float>& volume) {
		const auto resx = volume.getGrid().getSizes()[0];
		const auto resy = volume.getGrid().getSizes()[1];
		const auto resz = volume.getGrid().getSizes()[2];

		std::vector<ImageRGBA<unsigned char>> images;
		for (int z = 0; z < resz; ++z) {
			ImageRGBA<unsigned char> image(resx, resy);
			for (int x = 0; x < resx; ++x) {
				for (int y = 0; y < resy; ++y) {
					const auto v = volume.getGrid().get(x, y, z);
					const auto r = static_cast<unsigned char>(v * 255);
					const ColorRGBA<unsigned char> color( r, 0, 0, 255);
					image.setColor(x, y, color);
				}
			}
			images.push_back(image);
		}
		return images;
	}

	Grid3d<ValueType> toGrid(const std::vector<ImageRGBA<unsigned char>>& images) {
		assert(!images.empty());

		const auto resx = images.front().getWidth();
		const auto resy = images.front().getHeight();
		const auto resz = images.size();

		Grid3d<ValueType> grid(resx, resy, resz);

		for (unsigned int z = 0; z < resz; ++z) {
			const auto image = images[z];
			for (int x = 0; x < resx; ++x) {
				for (int y = 0; y < resy; ++y) {
					const auto& v = image.getColor(x, y);
					const auto r = v.getRed() / 255.0f;
					grid.set(x, y, z, r);
				}
			}
		}

		return grid;
	}
}


const std::string resStr = "resolution";
const std::string originStr = "origin";

static tinyxml2::XMLElement* create(XMLDocument& xml, const std::string& str, const Vector3d<float>& v)
{
	XMLElement* e = xml.NewElement(str.c_str());

	e->SetAttribute("x", v.getX());
	e->SetAttribute("y", v.getY());
	e->SetAttribute("z", v.getZ());

	return e;
}

Vector3d<float> XMLHelper::parse(tinyxml2::XMLElement& elem)
{
	const auto x = elem.FloatAttribute("x");
	const auto y = elem.FloatAttribute("y");
	const auto z = elem.FloatAttribute("z");
	return Vector3d<float>(x, y, z);
}

template<typename GeomType, typename ValueType>
tinyxml2::XMLError CGBFile<GeomType, ValueType>::save(const std::string& directoryname, const std::string& fn, const Volume3d<GeomType, ValueType>& volume)
{	
	const std::string& filename = directoryname + "/" + fn;
	XMLDocument xml;
	auto decl = xml.NewDeclaration();
	xml.InsertEndChild(decl);
	auto root = xml.NewElement("volume");
	xml.InsertEndChild(root);

	root->SetAttribute("fileFormatVersion", "0.1");

	auto res = xml.NewElement(resStr.c_str());
	res->SetAttribute("x", static_cast<unsigned int>(volume.getGrid().getSizes()[0]));
	res->SetAttribute("y", static_cast<unsigned int>(volume.getGrid().getSizes()[1]));
	res->SetAttribute("z", static_cast<unsigned int>(volume.getGrid().getSizes()[2]));
	root->InsertEndChild(res);

	root->InsertEndChild( create(xml, originStr, volume.getStart()) );
	root->InsertEndChild( create(xml, "length", volume.getSpace().getLengths()));

	const auto& images = ::toImageRGBAs(volume);

	auto e = xml.NewElement("volume");
	e->SetAttribute("type", "unsigned char");
	e->SetAttribute("format", "png");
	
	for (auto i = 0; i < volume.getGrid().getSizeZ(); ++i) {
		auto elem = xml.NewElement("image");
		const auto str = directoryname + "/" + std::to_string(i) + ".png";
		elem->SetAttribute("path", str.c_str());
		images[i].save(str , ImageFileFormat::PNG);
		e->InsertEndChild(elem);
	}
	root->InsertEndChild(e);

	//for (size_t i = 0; i < )
	
	return xml.SaveFile(filename.c_str());
}


XMLError CGBFile<float, float>::load(const std::string& foldername, const std::string& fn)
{
	const auto& filename = foldername + "/" + fn;
	tinyxml2::XMLDocument xml;
	const auto error = xml.LoadFile(filename.c_str());
	if (error != XMLError::XML_NO_ERROR) {
		return error;
	}

	XMLElement* root = xml.FirstChildElement("volume");

	std::array<int, 3> index;

	{
		XMLElement* res = root->FirstChildElement(resStr.c_str());
		index[0] = res->IntAttribute("x");
		index[1] = res->IntAttribute("y");
		index[2] = res->IntAttribute("z");
	}

	auto res = root->FirstChildElement("origin");
	const auto& origin = XMLHelper::parse(*res);

	auto lengthElem = root->FirstChildElement("length");
	const auto& length = XMLHelper::parse(*lengthElem);

	//Space3d<float> space(origin, length);
	const auto space = Space3d<float>(origin, length);

	auto volumeElem = root->FirstChildElement("volume");
	auto imageElem = volumeElem->FirstChildElement("image");

	std::vector<ImageRGBA<unsigned char>> images;
	while (imageElem != nullptr) {
		const auto& filename = imageElem->Attribute("path");
		ImageRGBA<unsigned char> image;
		image.read(filename);
		images.push_back(image);
		imageElem = imageElem->NextSiblingElement("image");
	}
	const auto& grid = toGrid(images);

	this->volume = Volume3d<GeomType, ValueType>(space, grid);
	return error;
}

template XMLError CGBFile<float, float>::save(const std::string&, const std::string& filename, const Volume3d<float, float>& volume);

template XMLError CGBFile<float, float>::load(const std::string& foldername, const std::string& fn);
