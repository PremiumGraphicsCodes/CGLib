#ifndef __CRYSTAL_IO_OBJ_FILE_H__
#define __CRYSTAL_IO_OBJ_FILE_H__

#include "../Math/Vector3d.h"

#include "../Graphics/Buffer3d.h"
#include "../Polygon/PolygonObject.h"

#include "../IO/MTLFile.h"
#include "../IO/File.h"

#include "OBJVertex.h"
#include "OBJFace.h"

#include <fstream>
#include <string>
#include <vector>

namespace Crystal {
	namespace IO {

class OBJMTLLib
{
public:
	OBJMTLLib()
	{};

	OBJMTLLib(const std::string& name) :
		name(name)
	{}

	OBJMTLLib(const std::string& name, const std::vector< std::string >& materials) :
		name(name),
		materials(materials)
	{}

	std::string getName() const { return name; }

	std::vector< std::string > getMaterials() const { return materials; }

	bool operator==(const OBJMTLLib& rhs) const {
		return
			name == rhs.name &&
			materials == rhs.materials;
	}

private:
	std::string name;
	std::vector< std::string > materials;
};


struct OBJGroup {
	OBJGroup(){}

	OBJGroup(const std::string& name) :
				name(name)
			{}

	OBJGroup(const std::string& name, const std::vector<OBJFace>& faces) :
		name(name),
		faces(faces)
	{}

	void add(const Polygon::PolygonObject& polygon);

	bool operator==(const OBJGroup& rhs) const {
		return
			name == rhs.name &&
			faces == rhs.faces &&
			materials == rhs.materials;
	}

	std::string getName() const { return name; }

	void setFaces(const std::vector< OBJFace>& faces) { this->faces = faces; }

	std::vector< OBJFace > getFaces() const { return faces; }

	void setPositions(const std::vector< Math::Vector3d<float> >& positions) { this->positions = positions; }

	std::vector< Math::Vector3d<float> > getPositions() const { return positions; }

	void setNormals(const std::vector< Math::Vector3d<float> >& normals) { this->normals = normals; }

	std::vector< Math::Vector3d<float> > getNormals() const { return this->normals; }

	void setMtlLib(const OBJMTLLib& lib) { this->mtlLib = lib; }

			void setTexCoords(const std::vector< Math::Vector3d<float> >& texCoords) { this->texCoords = texCoords; }

			std::vector< Math::Vector3d<float> > getTexCoords() const { return this->texCoords; }

			void setMaterials(const std::vector<std::string>& m) { this->materials = m; }

			Math::Vector3d<float> readVertices(const std::string& str);

			Math::Vector3d<float> readVector3d(const std::string& str);

			//Math::Vector2d<float> readVector2d(const std::string& str);

			OBJFace readFaces(const std::string& str);

			Polygon::PolygonObject* toPolygonObject();


private:
	std::string name;
	std::vector< OBJFace > faces;
	std::vector< std::string > materials;
	OBJMTLLib mtlLib;
	std::vector< Math::Vector3d<float> > positions;
	std::vector< Math::Vector3d<float> > normals;
	std::vector< Math::Vector3d<float> > texCoords;
};

struct OBJFile
{
	OBJFile()
	{}

	OBJFile(const std::string& comment, std::vector<OBJGroup>& groups) :
		comment(comment),
		groups(groups)
	{}

	std::string getComment() const { return comment; }

	std::vector<OBJGroup> getGroups() const { return groups; }

	bool read(const File& filename);

	bool read(std::istream& stream);

	bool write(const std::string& path, const std::string& filename, const Polygon::PolygonObject& mesh);

	bool write(std::ostream& stream, const Polygon::PolygonObject& mesh);

private:
	std::string comment;
	std::vector<OBJGroup> groups;
	std::string materialName;
};

	}
}

#endif