#ifndef __CRYSTAL_IO_OBJ_FILE_H__
#define __CRYSTAL_IO_OBJ_FILE_H__

#include "../Math/Vector3d.h"

#include "../Graphics/Buffer3d.h"
#include "../Polygon/PolygonObject.h"

#include "../IO/MTLFile.h"

#include <fstream>
#include <string>
#include <vector>

namespace Crystal {
	namespace IO {

struct OBJVertex
{
	OBJVertex() :
		positionIndex(-1),
		normalIndex(-1),
		texIndex(-1)
	{}


	OBJVertex(const int positionIndex, const int normalIndex = -1, const int texIndex = -1) :
		positionIndex(positionIndex),
		normalIndex(normalIndex),
		texIndex(texIndex)
	{}

	int positionIndex;
	int normalIndex;
	int texIndex;

	bool operator==(const OBJVertex& rhs) const {
		return
			this->positionIndex == rhs.positionIndex &&
			this->normalIndex == rhs.normalIndex &&
			this->texIndex == rhs.texIndex;
	}
};

struct OBJFace
{
	OBJFace()
	{}

	OBJFace(const std::vector<OBJVertex>& vertices) :
		vertices( vertices )
	{}

	bool operator==(const OBJFace& rhs) const {
		return
			vertices == rhs.vertices;
	}

	std::vector<OBJVertex> getVertices() const { return vertices; }

	std::string usemtlname;

private:
	std::vector<OBJVertex> vertices;
};


struct OBJMTLLib {
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

	OBJGroup()
	{}

	OBJGroup( const std::string& name ) :
		name( name )
	{}

	OBJGroup( const std::string& name, const std::vector<OBJFace>& faces) :
		name( name ),
		faces( faces )
	{}

	void add(const Polygon::PolygonObject& mesh);

	bool operator==(const OBJGroup& rhs) const {
		return
			name == rhs.name &&
			faces == rhs.faces &&
			materials == rhs.materials;
	}

	std::string getName() const { return name; }

	void setFaces(const std::vector< OBJFace>& faces) { this->faces = faces; }

	std::vector< OBJFace > getFaces() const { return faces; }


	void setPositions(const std::vector< Math::Vector3d<float> >& positions) { this->positionBuffer = positions; }

	std::vector< Math::Vector3d<float> > getPositions() const { return positionBuffer; }

	void setNormals(const std::vector< Math::Vector3d<float> >& normals) { this->normalBuffer = normals; }

	std::vector< Math::Vector3d<float> > getNormals() const { return this->normalBuffer; }

	void setMtlLib(const OBJMTLLib& lib) { this->mtlLib = lib; }

	void setTexCoords(const std::vector< Math::Vector3d<float> >& texCoords) { this->texCoordBuffer = texCoords; }

	std::vector< Math::Vector3d<float> > getTexCoords() const { return this->texCoordBuffer; }

	void setMaterials(const std::vector<std::string>& m) { this->materials = m; }

	Math::Vector3d<float> readVertices(const std::string& str);

	Math::Vector3d<float> readVector3d(const std::string& str);

	//Math::Vector2d<float> readVector2d(const std::string& str);

	OBJFace readFaces(const std::string& str);

	Polygon::PolygonObject* createPolygon();


private:
	std::string name;
	std::vector< OBJFace > faces;
	std::vector< std::string > materials;
	OBJMTLLib mtlLib;
	std::vector< Math::Vector3d<float> > positionBuffer;
	std::vector< Math::Vector3d<float> > normalBuffer;
	std::vector< Math::Vector3d<float> > texCoordBuffer;
};

struct OBJFile {
	bool isValid() const {
		return true;	//@TODO.
	}

	void setComment(const std::string& comment) { this->comment = comment; }

	std::string getComment() const { return comment; }

	void setGroups(const std::vector<OBJGroup>& groups) { this->groups = groups; }

	std::vector<OBJGroup> getGroups() const { return groups; }

	std::string getMaterialName() const { return materialName; }

private:
	std::string comment;
	std::vector<OBJGroup> groups;
	std::string materialName;

};

class OBJFileWriter {
public:
	bool write(const std::string& path, const std::string& filename, const Polygon::PolygonObject& mesh);

	bool write(std::ostream& stream, const Polygon::PolygonObject& mesh);

	/*
	std::ostream& operator<<(::std::ostream& os)
	{
		write(os);
		return os;
	}
	*/

	std::vector< std::string > getStrs() const { return strs; }

private:
	std::vector< std::string > strs;
};

class OBJFileReader {
public:
	OBJFileReader()
	{}

	OBJFileReader(std::istream& stream) {
		read(stream);
	}

	OBJFile read(const std::string& path, const std::string& filename);

	OBJFile read(std::istream& stream);
};

	}
}

#endif