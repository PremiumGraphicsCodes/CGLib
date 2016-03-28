#include "GLee.h"

#include "ShaderObject.h"
//#include "TextureObject.h"

#include <cassert>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Shader;

namespace {
	std::string getShaderString() {
		const GLubyte* str = glGetString(GL_RENDERER);
		const GLubyte* vendor = glGetString(GL_VENDOR);
		const GLubyte* glVersion = glGetString(GL_VERSION);
		const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
		std::stringstream stream;
		stream << str;
		stream << vendor;
		stream << glVersion;
		stream << glslVersion;
		return stream.str();
	}
}


std::string Util::getStr(const Crystal::File& file)
{
	std::ifstream stream(file.getFullPath());
	if (stream.fail()) {
		assert(false);
		return "";
	}
	std::istreambuf_iterator<char> it(stream);
	std::istreambuf_iterator<char> last;
	return std::string(it, last);
}


ShaderUnit::ShaderUnit(void) :
	id( -1 )
{
}

ShaderUnit::~ShaderUnit(void)
{
	clear();
}

void ShaderUnit::clear()
{
	if( id != -1 ) {
		glDeleteShader( id );
	}
}

bool ShaderUnit::compile( const std::string& source, const ShaderUnit::Stage stage )
{
	clear();
	if( stage == ShaderUnit::Stage::VERTEX ) {
		id = glCreateShader( GL_VERTEX_SHADER );
	}
	else if( stage == ShaderUnit::Stage::FRAGMENT ) {
		id = glCreateShader( GL_FRAGMENT_SHADER );
	}
	else if( stage == ShaderUnit::Stage::GEOMETRY ) {
		id = glCreateShader( GL_GEOMETRY_SHADER_ARB );
	}
	else {
		assert( false );
		return false;
	}
	const GLchar *strPtr[1];
	strPtr[0] = source.c_str();
	glShaderSource( id, 1, strPtr, NULL );

	glCompileShader( id );

	GLint success;
	glGetShaderiv( id, GL_COMPILE_STATUS, &success);
	GLchar infoLog[2048];
	glGetShaderInfoLog( id, 2048, NULL, infoLog );
	log += infoLog;
	//assert( success != 0 );
	//return ( success != 0 );

	if( success == 0 ) {
		return false;
	}

	if( glGetError() != GL_NO_ERROR ) {
		return false;
	}
	return true;
}

bool ShaderUnit::compile(const Crystal::File& file, const ShaderUnit::Stage stage)
{
	return compile( Util::getStr(file), stage );
}


ShaderObject::ShaderObject(void) :
	id( -1 )
{
}

ShaderObject::ShaderObject(const Crystal::File& vFile, const Crystal::File& fFile) :
	id(-1)
{
	assert(glGetError() == GL_NO_ERROR);
	build(vFile, fFile);
}


ShaderObject::~ShaderObject(void)
{
	clear();
}

void ShaderObject::clear()
{
	glUseProgram( 0 );
	if( id != -1 ) {
		glDeleteProgram( id );
	}
}

bool ShaderObject::link( const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader )
{
	clear();

	assert( glGetError() == GL_NO_ERROR );
	
	id = glCreateProgram();
	glAttachShader( id, vertexShader.getID() );
	glAttachShader( id, fragmentShader.getID() );
	
	GLint success;
	glLinkProgram( id );
	glGetProgramiv( id, GL_LINK_STATUS, &success );

	GLchar infoLog[2048];
	glGetProgramInfoLog( id, 2048, NULL, infoLog );
	log += infoLog;

	if (success == 0) {
		return false;
	}

	assert( glGetError() == GL_NO_ERROR );

	return true;
}

bool ShaderObject::link( const ShaderUnit& vertexShader, const ShaderUnit& fragmentShader, const ShaderUnit& geometryShader )
{
	clear();

	assert( glGetError() == GL_NO_ERROR );
	
	id = glCreateProgram();
	glAttachShader( id, vertexShader.getID() );
	glAttachShader( id, fragmentShader.getID() );
	glAttachShader( id, geometryShader.getID() );
	
	GLint success;
	glLinkProgram( id );
	glGetProgramiv( id, GL_LINK_STATUS, &success );

	GLchar infoLog[2048];
	glGetProgramInfoLog( id, 2048, NULL, infoLog );
	log += infoLog;

	if (success == 0) {
		return false;
	}

	assert( glGetError() == GL_NO_ERROR );

	return true;
}

bool ShaderObject::build(const std::string& vSource, const std::string& fSource)
{
	ShaderUnit vShader;
	ShaderUnit fShader;
	
	assert(glGetError() == GL_NO_ERROR);

	if (!vShader.compile(vSource, ShaderUnit::Stage::VERTEX)) {
		log += vShader.getLog();
		return false;
	}
	assert(glGetError() == GL_NO_ERROR);

	if (!fShader.compile(fSource, ShaderUnit::Stage::FRAGMENT)) {
		log += fShader.getLog();
		return false;
	}
	assert(glGetError() == GL_NO_ERROR);

	if (!link(vShader, fShader)) {
		return false;
	}

	return true;
	//positionLocation = glGetUniformLocation( shader.getId(), "position" );
}


bool ShaderObject::build(const std::string& vSource, const std::string& gSource, const std::string& fSource)
{
	ShaderUnit vShader;
	ShaderUnit gShader;
	ShaderUnit fShader;
	if (!vShader.compile(vSource, ShaderUnit::Stage::VERTEX)) {
		log += vShader.getLog();
		return false;
	}
	if (!gShader.compile(gSource, ShaderUnit::Stage::GEOMETRY)) {
		log += gShader.getLog();
		return false;
	}
	if (!fShader.compile(fSource, ShaderUnit::Stage::FRAGMENT)) {
		log += fShader.getLog();
		return false;
	}
	if (!link(vShader, fShader, gShader)) {
		return false;
	}

	return true;
	//positionLocation = glGetUniformLocation( shader.getId(), "position" );
}

void ShaderObject::findUniformLocation(const std::string& str)
{
	const auto location = glGetUniformLocation(id, str.c_str());
	assert(location != -1);
	uniformMap[str] = location;
}


void ShaderObject::findAttribLocation(const std::string& str)
{
	const auto location = glGetAttribLocation(id, str.c_str());
	assert(location != -1);
	attribMap[str] = location;
}
