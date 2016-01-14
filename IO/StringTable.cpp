#include "StringTable.h"

#include <fstream>
#include "TinyXML.h"

using namespace Crystal::IO;


StringTable::StringTable() :
	currentLocale("English")
{
}

void StringTable::add(const std::string key, const std::string value)
{
	map[currentLocale].add(key, value);
}

bool StringTable::read(const Crystal::File& file)
{
	tinyxml2::XMLDocument xml;
	const auto result = xml.LoadFile(file.getFullPath().c_str());
	if (result != tinyxml2::XMLError::XML_NO_ERROR) {
		return false;
	}
	auto root = xml.FirstChildElement("locale");
	for (auto element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()) {
		const auto str = element->Name();
		const auto path = element->Attribute("path");
		changeLocale(str);
		map[str].read(Crystal::File(path));
	}
	return true;
}

bool StringTable::write(const std::string& folder,const std::string& file)
{
	tinyxml2::XMLDocument xml;
	auto decl = xml.NewDeclaration();
	xml.InsertEndChild(decl);
	auto root = xml.NewElement("locale");
	xml.InsertEndChild(root);

	const auto metafile = folder + "/" + file;
	//std::ofstream stream(metafile);
	for (const auto m : map) {
		const auto path = folder + "/" + m.first;
		auto elem = xml.NewElement(m.first.c_str());
		elem->SetAttribute("path", path.c_str());
		root->InsertEndChild(elem);
		//stream << str << std::endl;
		if (!m.second.write(Crystal::File(path))) {
			return false;
		}
	}
	return (xml.SaveFile(metafile.c_str()) == tinyxml2::XML_NO_ERROR);
}