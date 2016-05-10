#ifndef __CRYSTAL_IO_OBJ_FILE_H__
#define __CRYSTAL_IO_OBJ_FILE_H__

#include "../Math/Vector3d.h"

#include "../Graphics/Buffer3d.h"
#include "../Polygon/PolygonObject.h"

#include "../IO/MTLFile.h"
#include "../IO/File.h"

#include <fstream>
#include <string>
#include <vector>

namespace Crystal {
	namespace IO {

struct OBJVertexIndex
{
	OBJVertexIndex() :
		positionIndex(-1),
		normalIndex(-1),
		texIndex(-1)
	{}


	OBJVertexIndex(const int positionIndex, const int normalIndex = -1, const int texIndex = -1) :
		positionIndex(positionIndex),
		normalIndex(normalIndex),
		texIndex(texIndex)
	{}

	bool hasNormal() const {
		return this->normalIndex != -1;
	}

	bool hasTex() const {
		return this->texIndex != -1;
	}

	bool operator==(const OBJVertexIndex& rhs) const {
		return
			(this->positionIndex == rhs.positionIndex) &&
			(this->normalIndex == rhs.normalIndex) &&
			(this->texIndex == rhs.texIndex);
	}


	int positionIndex;
	int normalIndex;
	int texIndex;
};


class OBJVertexCollection
{
public:
	Polygon::VertexCollection toVertices() const;

	std::vector< Math::Vector3d<float> > positions;
	std::vector< Math::Vector3d<float> > normals;
	std::vector< Math::Vector3d<float> > texCoords;

};

struct OBJFace
{
	OBJFace()
	{}

	OBJFace(const std::vector<OBJVertexIndex>& vertices) :
		vertices(vertices)
	{}

	bool operator==(const OBJFace& rhs) const {
		return vertices == rhs.vertices;
	}

	std::vector<OBJVertexIndex> getVertices() const { return vertices; }

private:
	std::vector<OBJVertexIndex> vertices;
};


class OBJMaterialCollection
{
public:
	void add(const std::string& str, const OBJFace& face) {
		map.insert(std::make_pair(str, face));
	}

	std::vector<OBJFace> getFaces(const std::string& name) const{
		std::vector<OBJFace> faces;
		for (auto iter = map.lower_bound(name); iter != map.upper_bound(name); ++iter) {
			faces.push_back(iter->second);
		}
		return faces;
	}

	std::vector<std::string> getNames() const {
		std::vector<std::string> strs;
		for (auto m : map) {
			strs.push_back(m.first);
		}
		std::unique(strs.begin(), strs.end());
		return strs;
	}

private:
	std::multimap<std::string, OBJFace> map;
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

	void setPositions(const std::vector< Math::Vector3d<float> >& positions) { vertices.positions = positions; }

	std::vector< Math::Vector3d<float> > getPositions() const { return vertices.positions; }

	void setNormals(const std::vector< Math::Vector3d<float> >& normals) { vertices.normals = normals; }

	std::vector< Math::Vector3d<float> > getNormals() const { return vertices.normals; }

	void setTexCoords(const std::vector< Math::Vector3d<float> >& texCoords) { vertices.texCoords = texCoords; }

	std::vector< Math::Vector3d<float> > getTexCoords() const { return vertices.texCoords; }

	Polygon::PolygonObject* toPolygonObject();

	std::multimap<std::string, OBJFace> getGroups() const { return groupMap; }

	std::vector<std::string> getMTLLibs() const { return mtllibs; }

	OBJMaterialCollection getMaterials() const { return materialMap; }

	//std::vector<OBJFace> getFaces(const std::string& str) 

private:
	std::string comment;

	OBJVertexCollection vertices;

	std::vector<OBJFace> faces;

	Math::Vector3d<float> readVertices(const std::string& str);

	Math::Vector3d<float> readVector3d(const std::string& str);

	OBJFace readFaces(const std::string& str);

	std::multimap<std::string, OBJFace> groupMap;
	std::vector<std::string> mtllibs;
	OBJMaterialCollection materialMap;

};

	}
}

#endif