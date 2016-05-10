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
	namespace Graphics {
		class VisualPolygon;
	}
	namespace IO {

		/*
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
*/
/*
class OBJMaterialCollection
{
public:
	void add(const std::string& str, const OBJ& face) {
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
*/
class OBJFile
{
public:
	OBJFile()
	{}

	void add(const Polygon::PolygonObject& polygon);

	std::string getComment() const { return comment; }

	std::vector< unsigned int > getFaceCounts() { return faceCounts; }

	void setFaceCounts(const std::vector< unsigned int >& counts) { faceCounts = counts; }

	bool read(const File& filename);

	bool read(std::istream& stream);

	bool write(const std::string& path, const std::string& filename, const Polygon::PolygonObject& mesh);

	bool write(std::ostream& stream, const Polygon::PolygonObject& mesh);

	void setPositions(const std::vector< Math::Vector3d<float> >& positions) { this->positions = positions; }

	std::vector< Math::Vector3d<float> > getPositions() const { return positions; }

	void setNormals(const std::vector< Math::Vector3d<float> >& normals) { this->normals = normals; }

	std::vector< Math::Vector3d<float> > getNormals() const { return normals; }

	void setTexCoords(const std::vector< Math::Vector3d<float> >& texCoords) { this->texCoords = texCoords; }

	std::vector< Math::Vector3d<float> > getTexCoords() const { return texCoords; }

	Polygon::PolygonObject* toPolygonObject();

	std::vector< std::pair< std::string, unsigned int > > getGroups() const { return groups; }

	std::vector< std::string > getMaterialFiles() const { return mtllibs; }

	std::vector< std::pair< std::string, unsigned int > > getMaterials() const { return useMtlNames; }

	Graphics::VisualPolygon load(const IO::File& file);

	//OBJMaterialCollection getMaterials() const { return materialMap; }

	//std::vector<OBJFace> getFaces(const std::string& str) 

private:
	std::string comment;

	std::vector< Math::Vector3d<float> > positions;
	std::vector< Math::Vector3d<float> > normals;
	std::vector< Math::Vector3d<float> > texCoords;

	std::vector< unsigned int > faceCounts;

	Math::Vector3d<float> readVertices(const std::string& str);

	Math::Vector3d<float> readVector3d(const std::string& str);

	//unsigned int readFaces(const std::string& str);

	std::vector< std::pair< std::string, unsigned int > > groups;
	std::vector< std::string > mtllibs;
	std::vector< std::pair< std::string, unsigned int> > useMtlNames;
	//OBJMaterialCollection materialMap;

};

	}
}

#endif