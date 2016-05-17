#ifndef __CRYSTAL_SHADER_SHADER_OBJECT_H__
#define __CRYSTAL_SHADER_SHADER_OBJECT_H__


#include "GLee.h"

#include <vector>
#include <map>
#include <string>

#include "../Math/Vector3d.h"

#include "../IO/File.h"

#include <string>

namespace Crystal {
	namespace Shader {

		class Util {
		public:
			static std::string getStr(const IO::File& file);
		};

class ShaderUnit
{
public:
	ShaderUnit(void);
	
	~ShaderUnit(void);

	enum class Stage {
		VERTEX,
		FRAGMENT,
		GEOMETRY,
	};

	bool compile( const std::string& source, const ShaderUnit::Stage stage );

	bool compile( const IO::File& file, const ShaderUnit::Stage stage);

	//bool dump(const std::string& filename);

	void clear();

	unsigned int getID() const { return id; }

	std::string getLog() const { return log; }

private:

	unsigned int id;

	std::string log;
};

class ShaderObject
{
public:
	ShaderObject(void);

	ShaderObject(const IO::File& vFile, const IO::File& fFile);

	~ShaderObject(void);

	void clear();

	bool link( const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader );

	bool link( const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader, const ShaderUnit& geometryShader );

	bool build(const std::string& vSource, const std::string& fSource);

	bool build(const std::string& vSource, const std::string& gSource, const std::string& fSource);

	bool build(const IO::File& vFile, const IO::File& fFile) {
		return build(Util::getStr(vFile), Util::getStr(fFile));
	}

	bool build(const IO::File& vFile, const IO::File& gFile, const IO::File& fFile) {
		return build(Util::getStr(vFile), Util::getStr(gFile), Util::getStr(fFile));
	}

	void findUniformLocation(const std::string& str);

	void findAttribLocation(const std::string& str);

	std::string getLog() const { return log; }

	unsigned int getId() const { return id; }

	unsigned int getUniformLocation(const std::string& str) { return uniformMap[str]; }

	unsigned int getAttribLocation(const std::string& str) { return attribMap[str]; }

public:
	unsigned int id;
private:
	std::string log;
	std::map< std::string, unsigned int > uniformMap;
	std::map< std::string, unsigned int > attribMap;


};


	}
}

#endif