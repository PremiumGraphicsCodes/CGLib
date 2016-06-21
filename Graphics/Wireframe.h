#ifndef __CRYSTAL_GRAPHICS_WIREFRAME_H__
#define __CRYSTAL_GRAPHICS_WIREFRAME_H__

namespace Crystal {
	namespace Graphics {

template<typename T>
class Wireframe final
{
public:
	Wireframe() = default;

	~Wireframe() = default;

	void add(const Math::Triangle3d<T>& t) {
		lines.emplace_back( Math::Line3d<T>( t.getv0(), t.getv1() ) );
		lines.emplace_back( Math::Line3d<T>( t.getv1(), t.getv2() ) );
		lines.emplace_back( Math::Line3d<T>( t.getv2(), t.getv0() ) );
	}

	void add(const Math::Box3d<T>& box) {
		const auto minx = box.getMinX();
		const auto miny = box.getMinY();
		const auto minz = box.getMinZ();
		const auto maxx = box.getMaxX();
		const auto maxy = box.getMaxY();
		const auto maxz = box.getMaxZ();


		const std::vector<Math::Vector3d<float>> vs{
			Math::Vector3d<T>(minx, miny, minz),
			Math::Vector3d<T>(maxx, miny, minz),
			Math::Vector3d<T>(maxx, maxy, minz),
			Math::Vector3d<T>(minx, maxy, minz),
			Math::Vector3d<T>(minx, miny, maxz),
			Math::Vector3d<T>(maxx, miny, maxz),
			Math::Vector3d<T>(maxx, maxy, maxz),
			Math::Vector3d<T>(minx, maxy, maxz)
		};

		lines.emplace_back(Line3d<T>(vs[0], vs[1]));
		lines.emplace_back(Line3d<T>(vs[1], vs[2]));
		lines.emplace_back(Line3d<T>(vs[2], vs[3]));
		lines.emplace_back(Line3d<T>(vs[3], vs[0]));

		lines.emplace_back(Line3d<T>(vs[4], vs[5]));
		lines.emplace_back(Line3d<T>(vs[5], vs[6]));
		lines.emplace_back(Line3d<T>(vs[6], vs[7]));
		lines.emplace_back(Line3d<T>(vs[7], vs[0]));

		lines.emplace_back(Line3d<T>(vs[0], vs[4]));
		lines.emplace_back(Line3d<T>(vs[1], vs[5]));
		lines.emplace_back(Line3d<T>(vs[2], vs[6]));
		lines.emplace_back(Line3d<T>(vs[3], vs[7]));
	}

	std::vector< Math::Line3d<T>> getLines() const { return lines; }

private:
	std::vector< Math::Line3d<T>> lines;
};
	}
}

#endif