#ifndef __CRYSTAL_IO_OBJ_FILE_H__
#define __CRYSTAL_IO_OBJ_FILE_H__

#include "../Math/Vector3d.h"

#include "../Graphics/Buffer3d.h"
#include "../Polygon/PolygonObject.h"

#include "../IO/MTLFile.h"
#include "../IO/File.h"

#include "OBJVertex.h"

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

struct OBJFace
{
	OBJFace()
	{}

	OBJFace(const std::vector<OBJVertex>& vertices) :
		vertices(vertices)
	{}

	bool operator==(const OBJFace& rhs) const {
		return vertices == rhs.vertices;
	}

	std::vector<OBJVertex> getVertices() const { return vertices; }

	std::string usemtlname;

private:
	std::vector<OBJVertex> vertices;
};


class OBJFile
{
public:
	OBJFile()
	{}

	void add(const Polygon::PolygonObject& polygon);

	void setFaces(const std::vector<OBJFace>& faces) { this->faces = faces; }

	std::vector<OBJFace> getFaces() const { return faces; }

	std::string getComment() const { return comment; }

	bool read(const File& filename);

	bool read(std::istream& stream);

	bool write(const std::string& path, const std::string& filename, const Polygon::PolygonObject& mesh);

	bool write(std::ostream& stream, const Polygon::PolygonObject& mesh);

	void setPositions(const std::vector< Math::Vector3d<float> >& positions) { this->positions = positions; }

	std::vector< Math::Vector3d<float> > getPositions() const { return positions; }

	void setNormals(const std::vector< Math::Vector3d<float> >& normals) { this->normals = normals; }

	std::vector< Math::Vector3d<float> > getNormals() const { return this->normals; }

	void setTexCoords(const std::vector< Math::Vector3d<float> >& texCoords) { this->texCoords = texCoords; }

	std::vector< Math::Vector3d<float> > getTexCoords() const { return this->texCoords; }

	Polygon::PolygonObject* toPolygonObject();


private:
	std::string comment;
	std::string materialName;

	std::vector< Math::Vector3d<float> > positions;
	std::vector< Math::Vector3d<float> > normals;
	std::vector< Math::Vector3d<float> > texCoords;
	std::vector<OBJFace> faces;

	Math::Vector3d<float> readVertices(const std::string& str);

	Math::Vector3d<float> readVector3d(const std::string& str);

	OBJFace readFaces(const std::string& str);

};

	}
}

#endif