#ifndef __CRYSTAL_IO_STL_FILE_H__
#define __CRYSTAL_IO_STL_FILE_H__

#include "../Math/Vector3d.h"
#include "../Graphics/Surface.h"

#include <fstream>

#include <vector>

namespace Crystal {
	namespace IO {

struct STLCell
{
public:
	STLCell()
	{}

	STLCell(const std::vector< Math::Vector3d<float> >& positions, const Math::Vector3d<float>& normal) :
		positions(positions),
		normal(normal)
	{}

	STLCell(const Graphics::Face<float>& face) {
		const auto edges = face.getEdges();
		assert(edges.size() == 3);
		for (const auto& e : edges) {
			positions.push_back( e.getStartPosition() );
		}
	}

	std::vector< Math::Vector3d<float> > getPositions() const { return positions; }

	void setPositions(const std::vector< Math::Vector3d<float> >& positions) { this->positions = positions; }

	void addPosition(const Math::Vector3d<float>& pos) { this->positions.push_back(pos); }

	void setNormal(const Math::Vector3d<float>& normal) { this->normal = normal; }

	Math::Vector3d<float> getNormal() const { return normal; }

	bool operator==(const STLCell& rhs) const {
		return
			positions == rhs.positions &&
			normal == rhs.normal;
	}

	const Graphics::Face<float> toFace() const {
		Graphics::Vertex<float> v0(positions[0]);
		Graphics::Vertex<float> v1(positions[1]);
		Graphics::Vertex<float> v2(positions[2]);
		Graphics::HalfEdge<float> e0(v0, v1);
		Graphics::HalfEdge<float> e1(v1, v2);
		Graphics::HalfEdge<float> e2(v2, v0);
		return Graphics::Face<float>({ e0, e1, e2 });
	}

private:
	std::vector< Math::Vector3d<float> > positions;
	Math::Vector3d<float> normal;
};

typedef std::vector< STLCell > STLCellVector;

class STLFile {
public:
	STLFile()
	{}

	STLFile(const STLCellVector& cells, const std::string title) :
		 cells( cells ),
		title( title )
	{

	}

	STLFile(const Graphics::Surface<float>& surface)
	{
		const auto faces = surface.getFaces();
		for (const auto& f : faces) {
			const STLCell c(f);
			cells.push_back(c);
		}
	}

	void setTitle(const std::string& title) { this->title = title; }

	std::string getTitle() const { return title; }

	void setCells(const std::vector< STLCell >& cells) { this->cells = cells; }

	std::vector< STLCell > getCells() const { return cells; }

	bool operator==(const STLFile& rhs) const {
		return
			title == rhs.title &&
			cells == rhs.cells;
	}

	Graphics::Surface<float> toSurface() const {
		Graphics::Surface<float> s;
		for (const auto& c : cells) {
			const auto& positions = c.getPositions();
			const auto& v0 = positions[0];
			const auto& v1 = positions[1];
			const auto& v2 = positions[2];
			s.add(Math::Triangle<float>(v0, v1, v2));
		}
		return s;
	}

private:
	STLCellVector cells;
	std::string title;

};

class STLFileReader
{
public:
	bool read(const std::string& filename);

	bool readASCII(const std::string& filename);

	bool readASCII(std::istream& stream);

	bool readBinary(const std::string& filename);

	bool readBinary(std::istream& stream);

	STLFile getFile() const { return file; }

private:
	STLFile file;

};

class STLFileWriter
{
public:
	STLFileWriter(const STLFile& file) :
		file(file)
	{}

	bool writeASCII(const std::string& filename);

	bool writeASCII(std::ostream& stream);

	bool writeBinary(std::ostream& stream);

	bool writeBinary(const std::string& filename);

private:
	STLFile file;
};
	}
}

#endif